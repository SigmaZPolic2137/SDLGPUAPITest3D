#define SDL_MAIN_USE_CALLBACKS

#include "app.h"
#include "engine.h"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_hints.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h> // VCIC-Excluded: Required for SDL3 callbacks.
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>

SDL_AppResult SDL_AppInit(void ** App, int ArgumentCount, char * ArgumentValues[]) {
	AppState * State = new AppState;
	*App = State;

	SDL_WindowFlags WindowFlags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;

	State -> Window = SDL_CreateWindow(State -> AppName, State -> WindowWidth, State -> WindowHeight, WindowFlags);
	if (!State -> Window) {
		SDL_Log("Failed to create a window!: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	SDL_GPUShaderFormat ShaderFormat = SDL_GPU_SHADERFORMAT_DXIL;

	State -> GPUDevice = SDL_CreateGPUDevice(ShaderFormat, State -> Debug, NULL);
	if (!State -> GPUDevice) {
		SDL_Log("Failed to create GPU device!: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	SDL_Log("GPU device created using %s driver.", SDL_GetGPUDeviceDriver(State -> GPUDevice));

	if (!SDL_ClaimWindowForGPUDevice(State -> GPUDevice, State -> Window)) {
		SDL_Log("Failed to claim window for GPU device!: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	SetFullScreen(State, State -> FullScreen);
	SetVSync(State, State -> VSync);
	SetShowFPS(State, State -> ShowFPS);

	/*

	if (!CreatePipeline(State)) return SDL_APP_FAILURE;

	std::array Vertices {
		Vertex {-1.0f, -1.0f, 0.0f},
		Vertex {1.0f, -1.0f, 0.0f},
		Vertex {0.0f, 1.0f, 0.0f},
	};

	if (!CreateVertexBuffer(State, Vertices)) return SDL_APP_FAILURE;

	*/

	SDL_ShowWindow(State -> Window);

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void * App, SDL_Event * Event) {
	AppState * State = static_cast <AppState *> (App);

	if (Event -> type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;
	if (Event -> type == SDL_EVENT_WINDOW_RESIZED) SDL_GetWindowSize(State -> Window, &State -> WindowWidth, &State -> WindowHeight);

	if (Event -> type == SDL_EVENT_WINDOW_ENTER_FULLSCREEN) State -> FullScreen = true;
	if (Event -> type == SDL_EVENT_WINDOW_LEAVE_FULLSCREEN) State -> FullScreen = false;

	if (Event -> type == SDL_EVENT_KEY_DOWN) {
		SDL_Keycode KeyCode = Event -> key.key;

		if (KeyCode == SDLK_ESCAPE) return SDL_APP_SUCCESS;

		if (KeyCode == SDLK_F9) SetShowFPS(State, !State -> ShowFPS);
		if (KeyCode == SDLK_F10) SetVSync(State, !State -> VSync);
		if (KeyCode == SDLK_F11) SetFullScreen(State, !State -> FullScreen);
	}

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void * App) {
	AppState * State = static_cast <AppState *> (App);

	Uint64 CurrentTime = SDL_GetTicksNS();

	if (State -> LastTime == 0) {
		State -> StartTime = CurrentTime;
		State -> LastTime = CurrentTime;
	}

	State -> ElapsedTime = static_cast <double> (CurrentTime - State -> StartTime) / 1000000000.0;
	State -> DeltaTime = static_cast <double> (CurrentTime - State -> LastTime) / 1000000000.0;
	State -> LastTime = CurrentTime;

	if (State -> ShowFPS && !State -> FullScreen) {
		State -> FPSTimer += State -> DeltaTime;
		State -> FPSFrameCount++;

		if (State -> FPSTimer >= 0.15) {
			double AverageFPS = static_cast <double> (State -> FPSFrameCount) / State -> FPSTimer;

			char Title[128];
			SDL_snprintf(Title, sizeof(Title), "%s - %d FPS", State -> AppName, static_cast <int> (AverageFPS));

			if (!SDL_SetWindowTitle(State -> Window, Title)) {
				SDL_Log("Failed to set window title!: %s", SDL_GetError());
			}

			State -> FPSTimer = 0.0;
			State -> FPSFrameCount = 0;
		}
	}

	// TODO: Refactor rendering to engine.cpp as modular for diffirent gpu pipelines

	SDL_GPUCommandBuffer * CommandBuffer = SDL_AcquireGPUCommandBuffer(State -> GPUDevice);
	if (!CommandBuffer) {
		SDL_Log("Failed to acquire GPU command buffer!: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	SDL_GPUTexture * SwapchainTexture = nullptr;
	if (!SDL_WaitAndAcquireGPUSwapchainTexture(CommandBuffer, State -> Window, &SwapchainTexture, NULL, NULL)) {
		SDL_Log("Failed to acquire GPU swapchain texture!: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (SwapchainTexture) {
		SDL_GPUColorTargetInfo ColorTargetInfo = {
			.texture = SwapchainTexture,
			.clear_color = SDL_FColor(0.0f, 0.0f, 0.0f, SDL_ALPHA_OPAQUE_FLOAT),
			.load_op = SDL_GPU_LOADOP_CLEAR,
			.store_op = SDL_GPU_STOREOP_STORE,
		};

		SDL_GPURenderPass * RenderPass = SDL_BeginGPURenderPass(CommandBuffer, &ColorTargetInfo, 1, NULL);

		/*

		SDL_BindGPUGraphicsPipeline(RenderPass, State -> Pipeline);

		FrameUniforms UniformData {};
		UniformData.ElapsedTime = static_cast <float> (State -> ElapsedTime);

		std::array VertexBuffers {
			SDL_GPUBufferBinding {
				.buffer = State -> VertexBuffer,
				.offset = 0,
		},
		};

		SDL_PushGPUVertexUniformData(CommandBuffer, 0, &UniformData, static_cast <Uint32> (sizeof(UniformData)));
		SDL_BindGPUVertexBuffers(RenderPass, 0, VertexBuffers.data(), static_cast <Uint32> (VertexBuffers.size()));

		SDL_DrawGPUPrimitives(RenderPass, State -> VerticesCount, 1, 0, 0);

		*/

		SDL_EndGPURenderPass(RenderPass);
	} else {
		SDL_Log("Swapchain texture not acquired.");
	}

	if (!SDL_SubmitGPUCommandBuffer(CommandBuffer)) {
		SDL_Log("Failed to submit GPU command buffer!: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void * App, SDL_AppResult Result) {
	AppState * State = static_cast <AppState *> (App);

	if (State) {
		if (State -> Window) SDL_HideWindow(State -> Window);

		if (State -> Pipeline) SDL_ReleaseGPUGraphicsPipeline(State -> GPUDevice, State -> Pipeline);
		if (State -> VertexBuffer) SDL_ReleaseGPUBuffer(State -> GPUDevice, State -> VertexBuffer);

		if (State -> Window) SDL_ReleaseWindowFromGPUDevice(State -> GPUDevice, State -> Window);
		if (State -> GPUDevice) SDL_DestroyGPUDevice(State -> GPUDevice);
		if (State -> Window) SDL_DestroyWindow(State -> Window);

		delete State;
	}

	switch (Result) {
		case SDL_APP_SUCCESS: SDL_Log("Application quit successfully."); break;
		case SDL_APP_FAILURE: SDL_Log("Application quit with an error."); break;
		default: SDL_Log("Application quit with an unexpected result.");
	}
}
