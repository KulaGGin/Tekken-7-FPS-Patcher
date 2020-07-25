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

        private void InjectInternalDLL(string tekkenShippingExePath) {

            var tekkenShippingExeFile = new {
                                                rawBytes = File.ReadAllBytes(tekkenShippingExePath).ToList(),
                                                fullPath = tekkenShippingExePath,
                                                fileName = Path.GetFileNameWithoutExtension(tekkenShippingExePath),
                                                directory = Path.GetDirectoryName(tekkenShippingExePath),
                                                extension = Path.GetExtension(tekkenShippingExePath)
                                            };

            // open the file in PeFile
            PeFile tekkenExePeFile = new PeFile(tekkenShippingExeFile.rawBytes.ToArray());

            // See if dll is already injected
            if (tekkenExePeFile.ImportedFunctions == null)
                throw new InvalidOperationException("Imported functions array is null");

            bool isDLLInjected = tekkenExePeFile.ImportedFunctions.ToList().Any(function => function.DLL == _fpsPatcherDLLName);

            // Return because dll is already injected and doesn't need to be injected again.
            if(isDLLInjected) return;

            // If dll isn't injected, inject it
            // align the file by 10000 because of a bug in PeNet
            int neededForAlignment = 0x10000 - tekkenShippingExeFile.rawBytes.Count % 0x10000;
            tekkenShippingExeFile.rawBytes.AddRange(Enumerable.Repeat<byte>(0x00, neededForAlignment));

            // reopen the Pe file
            tekkenExePeFile = new PeFile(tekkenShippingExeFile.rawBytes.ToArray());

            // determine first exported function from the dll
            PeFile dllPeFile = new PeFile(_fpsPatcherDLLPath);

            //add our new import to the exe (in memory)
            tekkenExePeFile.AddImport(_fpsPatcherDLLName, dllPeFile.ExportedFunctions?[0].Name ?? throw new InvalidOperationException("Can't access ExportedFunctions."));
            
            //Backup original executable in case of crashes.
            File.Copy(tekkenShippingExeFile.fullPath, tekkenShippingExeFile.directory + "\\" + tekkenShippingExeFile.fileName + "_backup" + tekkenShippingExeFile.extension, true);

            //write changes to disk
            File.WriteAllBytes(tekkenShippingExePath, tekkenExePeFile.RawFile.ToArray());
        }
    }
}
