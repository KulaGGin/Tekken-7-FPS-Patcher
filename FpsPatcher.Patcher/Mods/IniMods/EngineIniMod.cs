using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Patcher.Mods;


namespace FPSPatcher.Patcher.Mods.IniMods {
    public abstract class EngineIniMod : Mod {

        protected readonly string _engineIniPath = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData) + "\\TekkenGame\\Saved\\Config\\WindowsNoEditor\\Engine.ini";


    }
}
