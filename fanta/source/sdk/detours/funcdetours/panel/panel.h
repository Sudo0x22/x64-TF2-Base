#pragma once
#include"../input/input.h"
#include "../../../../features/vars/vars.h"

namespace Hooks
{
	namespace VGuiPanel
	{
		inline Hook::Table Table;
		namespace PaintTraverse
		{
			using Fn = void(__fastcall*)(void*, void*, unsigned int, bool, bool);
			constexpr uint32_t pIndex = 41u;
			void __fastcall Detour(void* ecx, void* edx, unsigned int panel, bool force_rep, bool allow_force)
			{
				if (pHl2Interfaces.EngineClient->IsTakingScreenshot() && vars::misc::clean_screenshot) {
					return Table.Original<Fn>(pIndex)(ecx, edx, panel, force_rep, allow_force);
				}
				Table.Original<Fn>(pIndex)(ecx, edx, panel, force_rep, allow_force);
			}
		}

		void Initialize()
		{
			Table.Initialize(pHl2Interfaces.VGuiPanel);
			Table.Hook(&PaintTraverse::Detour, PaintTraverse::pIndex);
		}
	}
}
