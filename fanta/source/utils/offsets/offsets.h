#pragma once
#include<cstdint>
#include"../scanner/scanner.h"
#include <stdio.h>

class CUtilOffsets
{
public:
	uintptr_t client_dll = 0x00;
	uintptr_t engine_dll = 0x00;
public:
	uintptr_t local_player = 0x00;
	uintptr_t cl_entitylist = 0x00;
	uintptr_t m_dwGlowObjectManager = 0x00;
	uintptr_t m_dwViewAngles = 0x00;
public:
	__inline bool Initialize()
	{
		this->client_dll = (uintptr_t)GetModuleHandleA("client.dll");
		this->engine_dll = (uintptr_t)GetModuleHandleA("engine.dll");

		this->local_player = 0xC49670;
		this->cl_entitylist = 0xC575F4;
		
		this->m_dwGlowObjectManager = 0xBE1890;
		this->m_dwViewAngles = 0x46A5DC;

		return true;
	}
}; CUtilOffsets pUtilOffsets;
