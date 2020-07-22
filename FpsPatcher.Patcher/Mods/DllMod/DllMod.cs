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


namespace FPSPatcher.Patcher.Mods.DLLMod {
    public class DLLMod : Mod {
        private const string _fpsPatcherDLLName = "FPSPatcher.Internal.dll";
        private readonly string _fpsPatcherDLLPath = AppDomain.CurrentDomain.BaseDirectory + "\\" + "FPSPatcher.Internal.dll";

        #region Overrides of Mod

        public override void ApplyMod() {
        }

        public override void CancelMod() {
        }

        #endregion

        public bool ApplyMod(string tekkenShippingExePath, int fpsLimit) {
            InitializeMaxFPSFile(tekkenShippingExePath, fpsLimit);

            CopyInternalDLL(tekkenShippingExePath);

            InjectInternalDLL(tekkenShippingExePath);

            return true;
        }

        private void CopyInternalDLL(string tekkenShippingExePath) {
            string tekkenShippingFolder = Path.GetDirectoryName(tekkenShippingExePath);

            if(!File.Exists(_fpsPatcherDLLPath)) {
                throw new FileNotFoundException("Can't find" + _fpsPatcherDLLName + ".");
            }

            File.Copy(_fpsPatcherDLLPath, tekkenShippingFolder + "\\" + _fpsPatcherDLLName, true);
        }

        private void InitializeMaxFPSFile(string tekkenShippingExePath, int fpsLimit) {
            string tekkenShippingFolder = Path.GetDirectoryName(tekkenShippingExePath);

            string maxFPSIniFilePath = tekkenShippingFolder + "\\maxFPS.ini";

            IniFileManager iniFileManager = new IniFileManager(maxFPSIniFilePath);
            iniFileManager.WriteValue("maxFPS", "maxFPS", fpsLimit.ToString());
        }

        private bool InjectInternalDLL(string tekkenShippingExePath) {
            // todo align by 10000 only if we're going to write it
            // todo create backup of the original tekkenShippingExe file
            // todo write that we're done with the patching
            // todo dynamically find out the name of the first exported function and import it
            var tekkenShippingExeFile = new {
                                                fullPath = tekkenShippingExePath,
                                                fileName = Path.GetFileNameWithoutExtension(tekkenShippingExePath),
                                                directory = Path.GetDirectoryName(tekkenShippingExePath),
                                                extension = Path.GetExtension(tekkenShippingExePath)
                                            };

            // load the target file
            List<byte> tekkenExeBytes = File.ReadAllBytes(tekkenShippingExeFile.fullPath).ToList();

            // open the file in PeFile
            PeFile tekkenExePeFile = new PeFile(tekkenExeBytes.ToArray());

            // See if dll is already injected
            bool isDLLInjected = (tekkenExePeFile.ImportedFunctions ?? throw new InvalidOperationException("Imported functions array is null")).ToList().Any(function => function.DLL == _fpsPatcherDLLName);

            // Return because dll is already injected and doesn't need to be injected again.
            if(isDLLInjected)
                return true;

            // If dll isn't injected, inject it
            // align the file by 10000 because of a bug in PeNet
            int neededForAlignment = 0x10000 - tekkenExeBytes.Count % 0x10000;
            tekkenExeBytes.AddRange(Enumerable.Repeat<byte>(0x00, neededForAlignment));
            // reopen the Pe file
            tekkenExePeFile = new PeFile(tekkenExeBytes.ToArray());

            //add our new import to the exe (in memory)
            tekkenExePeFile.AddImport(_fpsPatcherDLLName, "?FPSPatchInternal@@YAKPEAUHINSTANCE__@@@Z");

            //Backup original executable in case of crashes.
            File.Copy(tekkenShippingExeFile.fullPath, tekkenShippingExeFile.directory + tekkenShippingExeFile.directory + "_backup" + tekkenShippingExeFile.extension);

            //write changes to disk
            File.WriteAllBytes(tekkenShippingExePath, tekkenExePeFile.RawFile.ToArray());

            return true;
        }
    }
}
