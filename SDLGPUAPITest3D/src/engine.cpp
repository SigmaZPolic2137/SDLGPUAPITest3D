#include "engine.h"

// TBU (updated⚠️)

/*

SDL_GPUShader * LoadShader(SDL_GPUDevice * GPUDevice, const std::string & ShaderFileName) {
	SDL_GPUShaderStage ShaderStage;
	if (ShaderFileName.find(".vert") != std::string::npos) ShaderStage = SDL_GPU_SHADERSTAGE_VERTEX;
	else if (ShaderFileName.find(".frag") != std::string::npos) ShaderStage = SDL_GPU_SHADERSTAGE_FRAGMENT;
	else {
		SDL_Log("Failed to deduce shader stage from file %s!", ShaderFileName.c_str());
		return nullptr;
	}

	std::filesystem::path FullPath = std::filesystem::path(SDL_GetBasePath()) / "Shaders";
	SDL_GPUShaderFormat ShaderFormat = SDL_GPU_SHADERFORMAT_INVALID;
	const char * EntryPoint = "";

	SDL_GPUShaderFormat GPUShaderFormats = SDL_GetGPUShaderFormats(GPUDevice);
	if (GPUShaderFormats & SDL_GPU_SHADERFORMAT_SPIRV) {
		FullPath /= ShaderFileName + ".spv";
		ShaderFormat = SDL_GPU_SHADERFORMAT_SPIRV;
		EntryPoint = "main";
	} else if (GPUShaderFormats & SDL_GPU_SHADERFORMAT_DXIL) {
		FullPath /= ShaderFileName + ".dxil";
		ShaderFormat = SDL_GPU_SHADERFORMAT_DXIL;
		EntryPoint = "main";
	} else if (GPUShaderFormats & SDL_GPU_SHADERFORMAT_MSL) {
		FullPath /= ShaderFileName + ".msl";
		ShaderFormat = SDL_GPU_SHADERFORMAT_MSL;
		EntryPoint = "main0";
	} else {
		SDL_Log("Failed to find a supported shader format for %s driver!", SDL_GetGPUDeviceDriver(GPUDevice));
		return nullptr;
	}

	size_t FileSize = 0;
	void * Code = SDL_LoadFile(FullPath.string().c_str(), &FileSize);
	if (!Code) {
		SDL_Log("Failed to load shader file!: %s", SDL_GetError());
		return nullptr;
	}

	SDL_GPUShaderCreateInfo ShaderInfo = SDL_GPUShaderCreateInfo {
		.code_size = FileSize,
		.code = static_cast <Uint8 *> (Code),
		.entrypoint = EntryPoint,
		.format = ShaderFormat,
		.stage = ShaderStage,
		.num_uniform_buffers = (ShaderStage == SDL_GPU_SHADERSTAGE_VERTEX) ? 1u : 0u,
	};

	SDL_GPUShader * Shader = SDL_CreateGPUShader(GPUDevice, &ShaderInfo);
	if (!Shader) {
		SDL_Log("Failed to create shader from file %s!: %s", FullPath.string().c_str(), SDL_GetError());
		SDL_free(Code);
		return nullptr;
	}

	SDL_free(Code);

	return Shader;
}

bool CreatePipeline(AppState * State) {
	SDL_GPUShader * VertexShader = LoadShader(State -> GPUDevice, "OnlyPosition.vert");
	if (!VertexShader) {
		SDL_Log("Failed to create vertex shader!");
		return false;
	}

	SDL_GPUShader * FragmentShader = LoadShader(State -> GPUDevice, "SolidColor.frag");
	if (!FragmentShader) {
		SDL_Log("Failed to create fragment shader!");
		return false;
	}

	std::array VertexBufferDescriptions {
		SDL_GPUVertexBufferDescription {
			.slot = 0,
			.pitch = sizeof(Vertex),
			.input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX,
			.instance_step_rate = 0,
	},
	};

	std::array VertexAttributes {
		SDL_GPUVertexAttribute {
			.location = 0,
			.buffer_slot = 0,
			.format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
			.offset = 0,
	},
	};

	std::array ColorTargetDescriptions {
		SDL_GPUColorTargetDescription {
			.format = SDL_GetGPUSwapchainTextureFormat(State -> GPUDevice, State -> Window),
	},
	};

	SDL_GPUGraphicsPipelineCreateInfo PipelineCreateInfo = SDL_GPUGraphicsPipelineCreateInfo {
		.vertex_shader = VertexShader,
		.fragment_shader = FragmentShader,

		.vertex_input_state = SDL_GPUVertexInputState {
			.vertex_buffer_descriptions = VertexBufferDescriptions.data(),
			.num_vertex_buffers = static_cast <Uint32> (VertexBufferDescriptions.size()),
			.vertex_attributes = VertexAttributes.data(),
			.num_vertex_attributes = static_cast <Uint32> (VertexAttributes.size()),
	},

	.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,

	.rasterizer_state = SDL_GPURasterizerState {
		.fill_mode = SDL_GPU_FILLMODE_FILL,
		.cull_mode = SDL_GPU_CULLMODE_BACK,
		.front_face = SDL_GPU_FRONTFACE_COUNTER_CLOCKWISE,
	},

	.target_info = SDL_GPUGraphicsPipelineTargetInfo {
		.color_target_descriptions = ColorTargetDescriptions.data(),
		.num_color_targets = static_cast <Uint32> (ColorTargetDescriptions.size()),
	},
	};

	State -> Pipeline = SDL_CreateGPUGraphicsPipeline(State -> GPUDevice, &PipelineCreateInfo);

	SDL_ReleaseGPUShader(State -> GPUDevice, VertexShader);
	SDL_ReleaseGPUShader(State -> GPUDevice, FragmentShader);

	if (!State -> Pipeline) {
		SDL_Log("Failed to create graphics pipeline!: %s", SDL_GetError());
		return false;
	}

	return true;
}

bool CreateVertexBuffer(AppState * State, std::span <Vertex> Vertices) {
	State -> VerticesCount = static_cast <Uint32> (Vertices.size());
	Uint32 VerticesSize = State -> VerticesCount * sizeof(Vertex);

	SDL_GPUBufferCreateInfo VertexBufferCreateInfo = SDL_GPUBufferCreateInfo {
		.usage = SDL_GPU_BUFFERUSAGE_VERTEX,
		.size = VerticesSize,
	};

	State -> VertexBuffer = SDL_CreateGPUBuffer(State -> GPUDevice, &VertexBufferCreateInfo);
	if (!State -> VertexBuffer) {
		SDL_Log("Failed to create vertex buffer!: %s", SDL_GetError());
		return false;
	}

	SDL_GPUTransferBufferCreateInfo TransferBufferCreateInfo = SDL_GPUTransferBufferCreateInfo {
		.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
		.size = VerticesSize,
	};

	SDL_GPUTransferBuffer * TransferBuffer = SDL_CreateGPUTransferBuffer(State -> GPUDevice, &TransferBufferCreateInfo);
	if (!TransferBuffer) {
		SDL_Log("Failed to create transfer buffer!: %s", SDL_GetError());
		return false;
	}

	Vertex * TransferData = static_cast <Vertex *> (SDL_MapGPUTransferBuffer(State -> GPUDevice, TransferBuffer, false));
	if (!TransferData) {
		SDL_Log("Failed to map transfer buffer!: %s", SDL_GetError());
		SDL_ReleaseGPUTransferBuffer(State -> GPUDevice, TransferBuffer);
		return false;
	}

	SDL_memcpy(TransferData, Vertices.data(), VerticesSize);
	SDL_UnmapGPUTransferBuffer(State -> GPUDevice, TransferBuffer);

	SDL_GPUCommandBuffer * UploadCommandBuffer = SDL_AcquireGPUCommandBuffer(State -> GPUDevice);
	if (!UploadCommandBuffer) {
		SDL_Log("Failed to acquire GPU command buffer!: %s", SDL_GetError());
		SDL_ReleaseGPUTransferBuffer(State -> GPUDevice, TransferBuffer);
		return false;
	}

	SDL_GPUCopyPass * CopyPass = SDL_BeginGPUCopyPass(UploadCommandBuffer);

	SDL_GPUTransferBufferLocation BufferLocation = SDL_GPUTransferBufferLocation {
		.transfer_buffer = TransferBuffer,
		.offset = 0,
	};

	SDL_GPUBufferRegion BufferRegion = SDL_GPUBufferRegion {
		.buffer = State -> VertexBuffer,
		.offset = 0,
		.size = VerticesSize,
	};

	SDL_UploadToGPUBuffer(CopyPass, &BufferLocation, &BufferRegion, false);
	SDL_EndGPUCopyPass(CopyPass);

	if (!SDL_SubmitGPUCommandBuffer(UploadCommandBuffer)) {
		SDL_Log("Failed to submit GPU command buffer!: %s", SDL_GetError());
		SDL_ReleaseGPUTransferBuffer(State -> GPUDevice, TransferBuffer);
		return false;
	}

	SDL_ReleaseGPUTransferBuffer(State -> GPUDevice, TransferBuffer);

	return true;
}

*/
