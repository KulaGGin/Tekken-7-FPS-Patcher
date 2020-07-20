using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FpsPatcher.Patcher.Mods.DllMod;
using FpsPatcher.ViewModels.Commands;
using Patcher.Mods.Ini_Mod;


namespace FpsPatcher.ViewModels {
    public class PatchFpsViewModel : BaseViewModel {
        private bool _oneFrameThreadLag = true;
        private ActionCommand _patchCommand;

        private readonly ROneFrameThreadLagMod _rOneFrameThreadLagMod = new ROneFrameThreadLagMod();
        private readonly DllMod _dllMod = new DllMod();


        public PatchFpsViewModel() {
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
    }
}