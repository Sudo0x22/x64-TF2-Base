#pragma once
#include"menudetour/menudetour.h"
#include"funcdetours/funcdetours.h"
class Detours
{
public:
	__inline bool Initialize()
	{
		if (MH_Initialize() != MH_OK)
			return false;
		
		Hooks::EngineVGui::Initialize();
		Hooks::EngineClient::Initialize();

		if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
			return false;

		return true;
	}
}; Detours pDetours;
