#include "app.h"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>

bool SetFullScreen(AppState * State, bool Enabled) {
	if (!SDL_SetWindowFullscreen(State -> Window, Enabled)) {
		SDL_Log("Failed to toggle window fullscreen mode!: %s", SDL_GetError());
		return false;
	}

	State -> FullScreen = Enabled;

	return true;
}

bool SetVSync(AppState * State, bool Enabled) {
	SDL_GPUPresentMode TargetMode = SDL_GPU_PRESENTMODE_VSYNC;

	if (!Enabled) {
		if (SDL_WindowSupportsGPUPresentMode(State -> GPUDevice, State -> Window, SDL_GPU_PRESENTMODE_IMMEDIATE)) TargetMode = SDL_GPU_PRESENTMODE_IMMEDIATE;
		else {
			SDL_Log("Immediate present mode is not supported.");
			State -> VSync = true;
			return true;
		}
	}

	if (!SDL_SetGPUSwapchainParameters(State -> GPUDevice, State -> Window, SDL_GPU_SWAPCHAINCOMPOSITION_SDR, TargetMode)) {
		SDL_Log("Failed to set swapchain parameters!: %s", SDL_GetError());
		return false;
	}

	State -> VSync = (TargetMode == SDL_GPU_PRESENTMODE_VSYNC);

	return true;
}

bool SetShowFPS(AppState * State, bool Enabled) {
	State -> ShowFPS = Enabled;

	if (!Enabled) {
		State -> FPSTimer = 0.0;
		State -> FPSFrameCount = 0;

		if (!SDL_SetWindowTitle(State -> Window, State -> AppName)) {
			SDL_Log("Failed to set window title!: %s", SDL_GetError());
			return false;
		}
	} else {
		char Title[256];
		SDL_snprintf(Title, sizeof(Title), "%s - 67 FPS", State -> AppName);

		if (!SDL_SetWindowTitle(State -> Window, Title)) {
			SDL_Log("Failed to set window title!: %s", SDL_GetError());
			return false;
		}
	}

	return true;
}