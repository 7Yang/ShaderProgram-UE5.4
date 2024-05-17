// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

#include "Tests/RHIUnitTests.h"

class FShaderProgramModule : public IRHITestModule
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual void RunAllTests() override;

protected:
    void OnPIEStarted(UGameInstance* GameInstance);
};
