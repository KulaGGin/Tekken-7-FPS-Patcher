using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FpsPatcher.Patcher.Mods.DllMod;
using FpsPatcher.ViewModels.Commands;
using Microsoft.Win32;
using Patcher.Mods.Ini_Mod;


namespace FpsPatcher.ViewModels {
    public class PatchFpsViewModel : BaseViewModel {
        public readonly string DialogStartLocation = AppDomain.CurrentDomain.BaseDirectory;
        private bool _oneFrameThreadLag = true;
        private ActionCommand _patchCommand;

        private readonly ROneFrameThreadLagMod _rOneFrameThreadLagMod = new ROneFrameThreadLagMod();
        private readonly DllMod _dllMod = new DllMod();


        public PatchFpsViewModel() {
            string steamPath = GetSteamPath();

            if(steamPath != "") {
                string tekkenShippingExePath = steamPath + "\\steamapps\\common\\TEKKEN 7\\TekkenGame\\Binaries\\Win64";

                if(Directory.Exists(tekkenShippingExePath)) {
                    DialogStartLocation = tekkenShippingExePath;
                }
            }
        }

        public int FpsLimit { get; set; } = 120;

        public bool OneFrameThreadLag {
            get {
                return _oneFrameThreadLag;
            }
            set { 
                _oneFrameThreadLag = value; 
                OnPropertyChanged();
            }
        }

        
        public ActionCommand PatchCommand {
            get { return _patchCommand ??= new ActionCommand(PatchAction); }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="parameter"></param>
        public void PatchAction(object parameter) {
            _rOneFrameThreadLagMod.ApplyMod(Convert.ToInt32(OneFrameThreadLag));
            _dllMod.ApplyMod();
        }

        static string GetSteamPath() {
            string steamPath;

            using(RegistryKey view = RegistryKey.OpenBaseKey(RegistryHive.LocalMachine, System.Environment.Is64BitOperatingSystem ? RegistryView.Registry32 : RegistryView.Default)) {
                using RegistryKey steam = view.OpenSubKey(@"SOFTWARE\Valve\Steam", false);
                steamPath = steam?.GetValue("InstallPath", "") as string;
            }

            return steamPath;
        }
    }
}