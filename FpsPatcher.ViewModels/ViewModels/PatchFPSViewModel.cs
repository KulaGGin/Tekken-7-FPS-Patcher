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
        public string OpenFileDialogStartDirectory = AppDomain.CurrentDomain.BaseDirectory;
        private bool _oneFrameThreadLag = true;
        private ActionCommand _patchCommand;

        public event EventHandler<string> Message;

        private readonly ROneFrameThreadLagMod _rOneFrameThreadLagMod = new ROneFrameThreadLagMod();
        private readonly DLLMod _dllMod = new DLLMod();


        public PatchFPSViewModel() {
            string steamPath = GetSteamPath();

            if(steamPath != "") {
                string tekkenShippingExePath = steamPath + "\\steamapps\\common\\TEKKEN 7\\TekkenGame\\Binaries\\Win64";

                if(Directory.Exists(tekkenShippingExePath)) {
                    this.OpenFileDialogStartDirectory = tekkenShippingExePath;
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

            try {
                _dllMod.ApplyMod(tekkenShippingExePath as string, FPSLimit);
                RaiseMessageEvent("Done patching.");
            }
            catch (FileNotFoundException exception) {
                RaiseMessageEvent(exception.Message);
            }
            catch (IOException exception) {
                RaiseMessageEvent(exception.Message +
                                  "\nThe game is probably running and locks the file. Close game's process and try again.");
            }
        }

        static string GetSteamPath() {
            using RegistryKey view = RegistryKey.OpenBaseKey(RegistryHive.LocalMachine, System.Environment.Is64BitOperatingSystem ? RegistryView.Registry32 : RegistryView.Default);

            using RegistryKey steam = view.OpenSubKey(@"SOFTWARE\Valve\Steam", false);
            string steamPath = steam?.GetValue("InstallPath", "") as string;

            return steamPath;
        }

        protected virtual void RaiseMessageEvent(string e) {
            Message?.Invoke(this, e);
        }
    }
}