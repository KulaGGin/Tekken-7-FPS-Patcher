using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Patcher.Mods.FPS_Mod;


namespace Patcher.Mods {
    class FpsMod : Mod {

        public FpsMod(MatchStartInjection matchStartInjection, MatchExitInjection matchExitInjection, MatchEndInjection matchEndInjection) {
            MatchStartInjection = matchStartInjection;
            MatchExitInjection = matchExitInjection;
            MatchEndInjection = matchEndInjection;
        }

        private MatchStartInjection MatchStartInjection { get; }
        private MatchExitInjection MatchExitInjection { get; }
        private MatchEndInjection MatchEndInjection { get; }

        #region Overrides of Mod

        public override void ApplyMod() {

        }


        public override void CancelMod() {
        }

        #endregion

    }
}
