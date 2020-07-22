#pragma once

#include "MatchEndInjection.h"
#include "MatchExitInjection.h"
#include "MatchStartInjection.h"
#include "Mods/Mod.h"
#include "SimpleSelectFixInjection.h"

namespace FpsPatcher {
    class FpsMod final : Mod {
    public:
        explicit FpsMod(MemoryCommando::MemoryCommando& memoryCommando);

        void ApplyMod() override;
        void CancelMod() override;

        template<typename Classname>
        static void Append(std::vector<Classname>& vectorToAppendTo, const std::vector<Classname>& vectorToAppend);
    protected:
        MemoryCommando::MemoryCommando& _memoryCommando;
        uintptr_t _inGameFPSVariable;
        size_t _maxFps;
        MatchStartInjection _matchStartInjection;
        SimpleSelectFixInjection _simpleSelectFixInjection;
        MatchEndInjection _matchEndInjection;
        MatchExitInjection _matchExitInjection;

        static uintptr_t GetInGameMaxFpsVariableAddress(MemoryCommando::MemoryCommando& memoryCommando);
    private:
        size_t InitializeMaxFps() const;
    };

    template <typename Classname>
    void FpsMod::Append(std::vector<Classname>& vectorToAppendTo, const std::vector<Classname>& vectorToAppend) {
        vectorToAppendTo.insert(vectorToAppendTo.end(), vectorToAppend.begin(), vectorToAppend.end());
    }
}

