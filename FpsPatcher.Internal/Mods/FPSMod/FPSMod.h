#pragma once

#include "MatchEndInjection.h"
#include "MatchExitInjection.h"
#include "MatchStartInjection.h"
#include "Mods/Mod.h"
#include "SimpleSelectFixInjection.h"

namespace FPSPatcher {
    class FPSMod final : Mod {
    public:
        explicit FPSMod(MemoryCommando::MemoryCommando& memoryCommando, HMODULE moduleHandle);

        void ApplyMod() override;
        void CancelMod() override;

        template<typename Classname>
        static void Append(std::vector<Classname>& vectorToAppendTo, const std::vector<Classname>& vectorToAppend);
    protected:
        MemoryCommando::MemoryCommando& _memoryCommando;
        HMODULE _moduleHandle;
        uintptr_t _inGameFPSVariable;
        size_t _maxFPS;
        MatchStartInjection _matchStartInjection;
        SimpleSelectFixInjection _simpleSelectFixInjection;
        MatchEndInjection _matchEndInjection;
        MatchExitInjection _matchExitInjection;

        uintptr_t GetInGameMaxFPSVariableAddress(MemoryCommando::MemoryCommando& memoryCommando) const;
    private:
        size_t InitializeMaxFPS() const;
    };

    template <typename Classname>
    void FPSMod::Append(std::vector<Classname>& vectorToAppendTo, const std::vector<Classname>& vectorToAppend) {
        vectorToAppendTo.insert(vectorToAppendTo.end(), vectorToAppend.begin(), vectorToAppend.end());
    }
}

