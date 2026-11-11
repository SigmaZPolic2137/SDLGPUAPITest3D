#include "app.h"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_video.h>

bool IsFullScreen(SDL_Window * Window) {
	SDL_WindowFlags Flags = SDL_GetWindowFlags(Window);
	return Flags & SDL_WINDOW_FULLSCREEN;
}


bool ToggleFullScreen(SDL_Window * Window, bool * NewFullScreenState) {
	bool CurrentFullScreenState = IsFullScreen(Window);

	if (!SDL_SetWindowFullscreen(Window, !CurrentFullScreenState)) {
		SDL_Log("Failed to toggle window fullscreen mode!: %s", SDL_GetError());
		return false;
	}

	if (NewFullScreenState) *NewFullScreenState = !CurrentFullScreenState;

	return true;
}

bool SetVSyncSettings(AppState * State) {
	SDL_GPUPresentMode TargetMode = SDL_GPU_PRESENTMODE_VSYNC;

	if (!State -> VSync && SDL_WindowSupportsGPUPresentMode(State -> GPUDevice, State -> Window, SDL_GPU_PRESENTMODE_IMMEDIATE)) TargetMode = SDL_GPU_PRESENTMODE_IMMEDIATE;
	if (!SDL_SetGPUSwapchainParameters(State -> GPUDevice, State -> Window, SDL_GPU_SWAPCHAINCOMPOSITION_SDR, TargetMode)) {
		SDL_Log("Failed to set swapchain parameters!: %s", SDL_GetError());
		return false;
	}

	return true;
}
