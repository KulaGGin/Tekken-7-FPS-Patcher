using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Patcher.Injections;


namespace Patcher.Mods.FPS_Mod {
    class MatchExitInjection : IAoBInjection {

        #region Implementation of IAoBInjection

        public string InjectionAoB { get; }

        #endregion

    }
}
