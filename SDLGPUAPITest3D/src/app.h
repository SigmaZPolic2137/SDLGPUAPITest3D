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
	bool VSync = true;
	bool ShowFPS = false;

	double FPSTimer = 0.0;
	int FPSFrameCount = 0;

	Uint64 StartTime = 0;
	Uint64 LastTime = 0;

	double DeltaTime = 0.0;
	double ElapsedTime = 0.0;

	bool Debug = false;

	SDL_GPUGraphicsPipeline * Pipeline = nullptr;
	Uint32 VerticesCount = 0;
	SDL_GPUBuffer * VertexBuffer = nullptr;
};

bool SetFullScreen(AppState * State, bool Enabled);
bool SetVSync(AppState * State, bool Enabled);
bool SetShowFPS(AppState * State, bool Enabled);
