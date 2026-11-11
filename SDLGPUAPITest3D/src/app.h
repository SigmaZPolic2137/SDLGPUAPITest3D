#pragma once

#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>

struct AppState {
	const char * AppName = "SDLGPU";

	SDL_Window * Window = nullptr;
	SDL_GPUDevice * GPUDevice = nullptr;

	int WindowWidth = 800;
	int WindowHeight = 600;

	bool FullScreen = false;
	bool VSync = false;
	bool ShowFPS = false;

	Uint64 LastTime = 0;
	double DeltaTime = 0;
	double ElapsedTime = 0;

	bool Debug = false;

	SDL_GPUGraphicsPipeline * Pipeline = nullptr;
	Uint32 VerticesCount = 0;
	SDL_GPUBuffer * VertexBuffer = nullptr;
};

bool IsFullScreen(SDL_Window *);
bool ToggleFullScreen(SDL_Window *, bool *);
bool SetVSyncSettings(AppState *);
