using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Win32;
using Patcher.Mods;
using AsmResolver.X86;


namespace FpsPatcher.Patcher.Mods.DllMod {
    public class DllMod : Mod {
        private const string _fpsPatcherDllName = "FpsPatcher.Internal.dll";
        private readonly string _fpsPatcherDllPath = AppDomain.CurrentDomain.BaseDirectory + "\\" + "FpsPatcher.Internal.dll";
        public DllMod() {

        }

        #region Overrides of Mod

        public override void ApplyMod() {
        }

        public override void CancelMod() {
        }

        #endregion

        public void ApplyMod(string tekkenShippingExePath) {
            string tekkenShippingFolder = Path.GetDirectoryName(tekkenShippingExePath);

            if (!File.Exists(_fpsPatcherDllPath)) {
                throw new Exception("Can't find" + _fpsPatcherDllName + ".");
            }

            File.Copy(_fpsPatcherDllPath, tekkenShippingFolder + "\\" + _fpsPatcherDllName);

            var peFile = new Pe
            peFile.AddImport("_fpsPatcherDllName", "StartPage");

        }
    }
}
