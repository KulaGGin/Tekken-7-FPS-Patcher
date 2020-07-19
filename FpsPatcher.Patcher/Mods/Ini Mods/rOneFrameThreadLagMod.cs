using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FpsPatcher.Managers;
using FpsPatcher.Patcher.Mods.Ini_Mods;

namespace Patcher.Mods.Ini_Mod {
    public class ROneFrameThreadLagMod : EngineIniMod {

        private IniFileManager engineIniFileManager;
        private string section = "SystemSettings";
        private string key = "r.OneFrameThreadLag";


        public ROneFrameThreadLagMod() {
            engineIniFileManager = new IniFileManager(EngineIniPath);
        }

        public void ApplyMod(int oneFrameThreadLag) {
            SetROneFrameThreadLag(oneFrameThreadLag);
        }

        private void SetROneFrameThreadLag(int value) {
            engineIniFileManager.WriteValue(section, key, value.ToString());
        }

        #region Overrides of Mod

        public override void ApplyMod() {
        }

        public override void CancelMod() {
        }

        #endregion

    }
}
