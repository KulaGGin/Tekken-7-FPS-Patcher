using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FPSPatcher.Patcher.Mods.DLLMod;
using FPSPatcher.ViewModels.Commands;
using Microsoft.Win32;
using Patcher.Mods.Ini_Mod;


namespace FPSPatcher.ViewModels {
    public class PatchFPSViewModel : BaseViewModel {
        public string _openFileDialogStartDirectory = AppDomain.CurrentDomain.BaseDirectory;
        private bool _oneFrameThreadLag = true;
        private ActionCommand _patchCommand;

        private readonly ROneFrameThreadLagMod _rOneFrameThreadLagMod = new ROneFrameThreadLagMod();
        private readonly DLLMod _dllMod = new DLLMod();


        public PatchFPSViewModel() {
            string steamPath = GetSteamPath();

            if(steamPath != "") {
                string tekkenShippingExePath = steamPath + "\\steamapps\\common\\TEKKEN 7\\TekkenGame\\Binaries\\Win64";

                if(Directory.Exists(tekkenShippingExePath)) {
                    this._openFileDialogStartDirectory = tekkenShippingExePath;
                }
            }
        }

        public int FPSLimit { get; set; } = 120;

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
        /// <param name="tekkenShippingExePath"></param>
        public void PatchAction(object tekkenShippingExePath) {

            _rOneFrameThreadLagMod.ApplyMod(Convert.ToInt32(OneFrameThreadLag));
            _dllMod.ApplyMod(tekkenShippingExePath as string, FPSLimit);
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