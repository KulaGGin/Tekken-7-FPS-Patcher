using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FpsPatcher.Managers;
using FpsPatcher.Patcher.Mods.IniMods;

namespace Patcher.Mods.Ini_Mod {
    public class ROneFrameThreadLagMod : EngineIniMod {

        private readonly IniFileManager _engineIniFileManager;
        private const string _section = "SystemSettings";
        private const string _key = "r.OneFrameThreadLag";

        public ROneFrameThreadLagMod() {
            _engineIniFileManager = new IniFileManager(_engineIniPath);
        }

        public void ApplyMod(int oneFrameThreadLag) {
            SetROneFrameThreadLag(oneFrameThreadLag);
        }

        private void SetROneFrameThreadLag(int value) {
            _engineIniFileManager.WriteValue(_section, _key, value.ToString());
        }

        #region Overrides of Mod

        public override void ApplyMod() {
        }

        public override void CancelMod() {
        }

        #endregion

    }
}
