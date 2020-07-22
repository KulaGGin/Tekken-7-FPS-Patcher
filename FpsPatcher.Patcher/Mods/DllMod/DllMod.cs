using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FPSPatcher.Managers;
using Microsoft.Win32;
using Patcher.Mods;
using PeNet;


namespace FPSPatcher.Patcher.Mods.DllMod {
    public class DllMod : Mod {
        private const string _fpsPatcherDllName = "FPSPatcher.Internal.dll";
        private readonly string _fpsPatcherDllPath = AppDomain.CurrentDomain.BaseDirectory + "\\" + "FPSPatcher.Internal.dll";

        #region Overrides of Mod

        public override void ApplyMod() {
        }

        public override void CancelMod() {
        }

        #endregion

        public void ApplyMod(string tekkenShippingExePath, int fpsLimit) {
            string tekkenShippingFolder = Path.GetDirectoryName(tekkenShippingExePath);
            string maxFPSIniFilePath = tekkenShippingFolder + "\\maxFPS.ini";

            IniFileManager iniFileManager = new IniFileManager(maxFPSIniFilePath);

            iniFileManager.WriteValue("maxFPS", "maxFPS", fpsLimit.ToString());

            if (!File.Exists(_fpsPatcherDllPath)) {
                throw new Exception("Can't find" + _fpsPatcherDllName + ".");
            }

            File.Copy(_fpsPatcherDllPath, tekkenShippingFolder + "\\" + _fpsPatcherDllName, true);

            // todo align by 10000 only if we're going to write it
            // todo create backup of the original tekkenShippingExe file
            // load the target file and change size so it's aligned by 0x10000
            List<byte> tekkenExeBytes = File.ReadAllBytes(tekkenShippingExePath).ToList();
            int neededForAlignment = 0x10000 - tekkenExeBytes.Count % 0x10000;
            tekkenExeBytes.AddRange(Enumerable.Repeat<byte>(0x00, neededForAlignment));
            // open the file in PeFile
            PeFile tekkenExePeFile = new PeFile(tekkenExeBytes.ToArray());

            bool isDllInjected = (tekkenExePeFile.ImportedFunctions ?? throw new InvalidOperationException("Imported functions array is null")).ToList().Any(function => function.DLL == _fpsPatcherDllName);

            if (isDllInjected)
                return;

            //add our new import to the exe (in memory)
            tekkenExePeFile.AddImport(_fpsPatcherDllName, "?FPSPatchInternal@@YAKPEAUHINSTANCE__@@@Z");
            //write changes to disk
            File.WriteAllBytes(tekkenShippingExePath, tekkenExePeFile.RawFile.ToArray());
            // todo write that we're done with the patching
        }
    }
}
