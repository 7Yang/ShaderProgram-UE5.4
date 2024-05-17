// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShaderProgramModule.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "ShaderCore.h"
#include "RHIBufferTests.h"
#include "RHITextureTests.h"
#include "RHIDrawTests.h"
#include "RHIReadbackTests.h"
#include "RHIReservedResourceTests.h"

#define LOCTEXT_NAMESPACE "ShaderProgramModule"

static bool RunTests_RenderThread(FRHICommandListImmediate& RHICmdList)
{
	bool bResult = true;

	// ------------------------------------------------
	// Reserved resources
	// ------------------------------------------------
	{
		RUN_TEST(FRHIReservedResourceTests::Test_ReservedResource_CommitBuffer(RHICmdList));
		RUN_TEST(FRHIReservedResourceTests::Test_ReservedResource_DecommitBuffer(RHICmdList));
		RUN_TEST(FRHIReservedResourceTests::Test_ReservedResource_CreateBuffer(RHICmdList));
		RUN_TEST(FRHIReservedResourceTests::Test_ReservedResource_CreateTexture(RHICmdList));
		RUN_TEST(FRHIReservedResourceTests::Test_ReservedResource_CreateVolumeTexture(RHICmdList));
	}

	// ------------------------------------------------
	// Drawing
	// ------------------------------------------------
	{
		RUN_TEST(FRHIDrawTests::Test_DrawBaseVertexAndInstanceDirect(RHICmdList));
		RUN_TEST(FRHIDrawTests::Test_DrawBaseVertexAndInstanceIndirect(RHICmdList));
		RUN_TEST(FRHIDrawTests::Test_MultiDrawIndirect(RHICmdList));
	}

	// ------------------------------------------------
	// RHI Formats
	// ------------------------------------------------
	{
		RUN_TEST(FRHITextureTests::Test_RHIFormats(RHICmdList));
	}

	// ------------------------------------------------
	// RHIClearUAVUint / RHIClearUAVFloat tests
	// ------------------------------------------------
	{
		// Vertex/Structured Buffer
		RUN_TEST(FRHIBufferTests::Test_RHIClearUAVUint_VertexBuffer(RHICmdList));
		RUN_TEST(FRHIBufferTests::Test_RHIClearUAVFloat_VertexBuffer(RHICmdList));

		RUN_TEST(FRHIBufferTests::Test_RHIClearUAVUint_StructuredBuffer(RHICmdList));
		RUN_TEST(FRHIBufferTests::Test_RHIClearUAVFloat_StructuredBuffer(RHICmdList));

		// Texture2D/3D
		RUN_TEST(FRHITextureTests::Test_RHIClearUAV_Texture2D(RHICmdList));
		RUN_TEST(FRHITextureTests::Test_RHIClearUAV_Texture3D(RHICmdList));
	}

	// ------------------------------------------------
	// Texture Operations
	// ------------------------------------------------
	{
		RUN_TEST(FRHITextureTests::Test_RHICopyTexture(RHICmdList));
		RUN_TEST(FRHITextureTests::Test_UpdateTexture(RHICmdList));
		RUN_TEST(FRHITextureTests::Test_MultipleLockTexture2D(RHICmdList));
	}

	// ------------------------------------------------
	// Readback
	// ------------------------------------------------
	{
		RUN_TEST(FRHIReadbackTests::Test_BufferReadback(RHICmdList));
		RUN_TEST(FRHIReadbackTests::Test_TextureReadback(RHICmdList));
	}

	// ------------------------------------------------
	// Buffer Operations
	// ------------------------------------------------
	{
		RUN_TEST(FRHIBufferTests::Test_RHICreateBuffer_Parallel(RHICmdList));
	}

	// ------------------------------------------------
	// RT Operations
	// ------------------------------------------------
	{
		RUN_TEST(FRHITextureTests::Test_ClearRenderTargets(RHICmdList));
	}

	// @todo - add more tests
	return bResult;
}

void FShaderProgramModule::StartupModule()
{
    FString GameSourceDirectory = FPaths::GameSourceDir();
	FString ShaderProgramDir    = FPaths::Combine(GameSourceDirectory, TEXT("HLSLShaders"));
	AddShaderSourceDirectoryMapping(TEXT("/HLSLShaders"), ShaderProgramDir);

    FWorldDelegates::OnPIEStarted.AddRaw(this, &FShaderProgramModule::OnPIEStarted);
}

void FShaderProgramModule::OnPIEStarted(UGameInstance* GameInstance)
{
    RunAllTests();
}

void FShaderProgramModule::RunAllTests()
{
    if (RunOnRenderThreadSynchronous(RunTests_RenderThread))
	{
		UE_LOG(LogRHIUnitTestCommandlet, Display, TEXT("RHI unit tests completed. All tests passed."));
	}
	else
	{
		UE_LOG(LogRHIUnitTestCommandlet, Error, TEXT("RHI unit tests completed. At least one test failed."));
	}
}

void FShaderProgramModule::ShutdownModule()
{
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_PRIMARY_GAME_MODULE(FShaderProgramModule, ShaderProgramModule, "ShaderProgramModule")
