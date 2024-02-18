#pragma once
#include<ranges>
#include"../sdk/sdk.h"
#include"../../includes/minhook/include/MinHook.h"
#include"../../includes/kiero/kiero.h"
static uint64_t* Method = nullptr;

namespace Hook
{
	class Manager
	{
	public:
		__inline bool make_hook(uint16_t nIndex, LPVOID nDetour, LPVOID* nOriginal)
		{
			LPVOID nTarget = (LPVOID)Method[nIndex];
			if (MH_CreateHook(nTarget, nDetour, nOriginal) != MH_OK)
				return false;
			return true;
		}
	};
	class Function
	{
	private:
		void* pOriginal = nullptr;
	public:
		__inline bool Initialize(void* pTarget, void* pDetour) {
			return (MH_CreateHook(pTarget, pDetour, &pOriginal) == MH_OK);
		}
	public:
		template<typename Fn>
		inline Fn Original() const { return reinterpret_cast<Fn>(pOriginal); }
	};

	class Table {
	private:
		unsigned int** pBase = 0u;
		unsigned int pSize = 0u;
		std::unique_ptr<void* []> pOriginals = {};
	public:
		__inline bool Initialize(const void* pTable) {
			pBase = (unsigned int**)(pTable);
			while (reinterpret_cast<unsigned int*>(pBase)[pSize])
				pSize += 1u;
			pOriginals = std::make_unique<void* []>(pSize);
			return (pBase && pSize);
		}
		__inline bool Hook(void* pDetour, const unsigned int pIndex) {
			if (pBase && pSize)
				return (MH_CreateHook((*reinterpret_cast<void***>(pBase))[pIndex], pDetour, &pOriginals[pIndex]) == MH_OK);
			return false;
		}
	public:
		template<typename Fn>
		__inline Fn Original(const unsigned int pIndex) const {
			return reinterpret_cast<Fn>(pOriginals[pIndex]);
		}
	};
}
