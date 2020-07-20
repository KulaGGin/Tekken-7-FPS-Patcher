using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Win32;
using Patcher.Mods;


namespace FpsPatcher.Patcher.Mods.DllMod {
    public class DllMod : Mod {
        private readonly string _dialogStartLocation = AppDomain.CurrentDomain.BaseDirectory;

        public DllMod() {
            string steamPath = GetSteamPath();

            if (steamPath != "") {
                string tekkenShippingExePath = steamPath + "\\steamapps\\common\\TEKKEN 7\\TekkenGame\\Binaries\\Win64";

                if (Directory.Exists(tekkenShippingExePath)) {
                    _dialogStartLocation = tekkenShippingExePath;
                }
            }
        }

        #region Overrides of Mod

        public override void ApplyMod() {

            throw new NotImplementedException();
        }

        public override void CancelMod() {
            throw new NotImplementedException();
        }

        #endregion

        static string GetSteamPath() {
            string steamPath;

            using(RegistryKey view = RegistryKey.OpenBaseKey(RegistryHive.LocalMachine, System.Environment.Is64BitOperatingSystem ? RegistryView.Registry32 : RegistryView.Default)) {
                using(RegistryKey steam = view.OpenSubKey(@"SOFTWARE\Valve\Steam", false)) {
                    // actually accessing Wow6432Node 
                    steamPath = steam?.GetValue("InstallPath", "") as string;
                }
            }

            return steamPath;
        }
    }
}
