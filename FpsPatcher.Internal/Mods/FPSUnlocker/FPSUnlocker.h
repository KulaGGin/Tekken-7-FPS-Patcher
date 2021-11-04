#pragma once
#include <memory>
#include <Windows.h>
#include "Mods/Mod.h"
#include "Mods/ObjectProxy.h"
#include "MinHook.h"

using FightStartLoadingScreenFunctionPointer_t = void(__fastcall*)(__int64 a1, char a2); // void __fastcall sub_14544E8D0(__int64 a1, char a2)
using FightStartFunctionPointer_t = __int64(__fastcall*)(unsigned __int8 a1); // __int64 __fastcall sub_144E4F470(unsigned __int8 a1)
using FightExitFunctionPointer_t = void(__fastcall*)(__int64* a1); // void __fastcall sub_14505EDF0(__int64 *a1)
using FightEndFunctionPointer_t = char(__fastcall*)(char a1); //char __fastcall sub_140297F80(char a1)

namespace FPSPatcher {
    class FPSUnlocker : public Mod {
    public:
        inline static std::shared_ptr<FPSUnlocker> Instance{};

        FPSUnlocker();
        virtual ~FPSUnlocker();
        void    enableUnlockedFPSMod();
        void    disableUnlockedFPSMod();
        void    removeUnlockedFPSMod();

        virtual void ApplyMod() override;
        virtual void CancelMod() override;

        void createHooks();
        void enableHooks();
        void disableHooks();
        void removeHooks();

        void initializeGameFPSVar();
        void initializeTargetFunctionPointers();

        void setMaxFPSLimit(int fps) const;

        static void __fastcall fightStartLoadingScreenFunction_SetCustomMaxFPSLimitDetour(__int64 argument1, char argument2);
        static __int64 __fastcall fightStartFunction_SetCustomMaxFPSLimitDetour(unsigned char a1);
        //char __fastcall sub_140297F80(char a1)
        static char __fastcall fightEndFunction_SetMaxFPSLimit60Detour(char a1);
        static void __fastcall fightExitFunction_SetMaxFPSLimit60Detour(long long* a1);

        int wantedMaximumFPS{};
        ObjectProxy<float> currentMaxFPSLimitGameVariable;

        FightStartLoadingScreenFunctionPointer_t targetFightStartLoadingScreenFunctionPointer; /*= reinterpret_cast<FightStartLoadingScreenFunctionPointer_t>(0x14042EF20);*/
        FightStartLoadingScreenFunctionPointer_t originalFightStartLoadingScreenFunctionPointer{};

        FightStartFunctionPointer_t targetFightStartFunctionPointer; /*= reinterpret_cast<FightStartFunctionPointer_t>(0x140255570);*/
        FightStartFunctionPointer_t originalFightStartFunctionPointer;

        FightEndFunctionPointer_t targetFightEndFunctionPointer; /*= reinterpret_cast<FightEndFunctionPointer_t>(0x1402B0710);*/
        FightEndFunctionPointer_t originalFightEndFunctionPointer{};

        FightExitFunctionPointer_t targetFightExitFunctionPointer; /*= reinterpret_cast<FightExitFunctionPointer_t>(0x14025F6B0);*/
        FightExitFunctionPointer_t originalFightExitFunctionPointer{};
    private:
        size_t GetWantedMaxFPS() const;
    };
}


