#pragma once
#include"../../../interfaces/interfaces.h"
#include"../../../../hooking/hooking.h"

namespace Hooks
{
	namespace ClMain
	{
		inline Hook::Function Func;
		namespace Whitelist {
			using Fn = void(__fastcall*)(void*, void*);
			void __fastcall Detour(void* rbx, void* rdx) {
				Func.Original<Fn>()(rbx, rdx);
			}
		}
		namespace ReadPacket {
			using Fn = void(__fastcall*)(void*, void*);
			void __fastcall Detour(void* rbx, void* rdx) {
				Func.Original<Fn>()(rbx, rdx);
			}
		}
		void Initialize()
		{
			const Whitelist::Fn lpWhiteList = reinterpret_cast<Whitelist::Fn>(0x00);
			const ReadPacket::Fn lpReadPacket = reinterpret_cast<ReadPacket::Fn>(0x00);

			if (lpWhiteList)
				Func.Initialize(lpWhiteList, &Whitelist::Detour);

			if (lpReadPacket)
				Func.Initialize(lpReadPacket, &ReadPacket::Detour);
		}
	}
}
