using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Patcher.Mods;


namespace FpsPatcher.Patcher.Mods.Ini_Mods {
    abstract public class EngineIniMod : Mod {

        protected string EngineIniPath = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData) + "\\TekkenGame\\Saved\\Config\\WindowsNoEditor\\Engine.ini";


    }
}
