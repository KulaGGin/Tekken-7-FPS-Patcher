using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Patcher.Mods {
    abstract public class Mod {
        private bool _enabled;

        public abstract void ApplyMod();
        public abstract void CancelMod();

        public Mod() {
            _enabled = false;
        }

        public void SwitchMod() {
            if(_enabled) {
                _enabled = false;
                CancelMod();
            }
            else {
                _enabled = true;
                ApplyMod();
            }
        }
    }
}
