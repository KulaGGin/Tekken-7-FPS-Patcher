using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FpsPatcher.ViewModels.Commands;
using Patcher.Mods.Ini_Mod;


namespace FpsPatcher.ViewModels {
    public class PatchFpsViewModel : BaseViewModel {
        private bool _oneFrameThreadLag = true;
        private ActionCommand patchCommand;

        private ROneFrameThreadLagMod rOneFrameThreadLagMod = new ROneFrameThreadLagMod();

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
            get { return patchCommand ?? (patchCommand = new ActionCommand(PatchAction)); }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="parameter"></param>
        public void PatchAction(object parameter) {
            rOneFrameThreadLagMod.ApplyMod(Convert.ToInt32(OneFrameThreadLag));

        }
    }
}