using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;


namespace FPSPatcher.Managers {
    /// <summary>
    /// Create a New INI file to store or load data
    /// </summary>
    public class IniFileManager {
        public string Path;

        [DllImport("kernel32")]
        private static extern long WritePrivateProfileString(string section,
                                                             string key, string val, string filePath);
        [DllImport("kernel32")]
        private static extern int GetPrivateProfileString(string section,
                                                          string key, string def, StringBuilder retVal,
                                                          int size, string filePath);


        /// INIFile Constructor.
        /// <PARAM name="iniPath"></PARAM>
        public IniFileManager(string iniPath) {
            Path = iniPath;
        }

        /// Write Data to the INI File
        /// <PARAM name="Section">Section name</PARAM>
        /// <PARAM name="Key">Key Name</PARAM>
        /// <PARAM name="Value">Value Name</PARAM>
        public void WriteValue(string section, string key, string value) {
            WritePrivateProfileString(section, key, value, this.Path);
        }

        /// Read Data Value From the Ini File
        /// <PARAM name="Section">Section name</PARAM>
        /// <PARAM name="Key">Key Name</PARAM>
        /// <PARAM name="Value">Value Name</PARAM>
        /// <returns>Returns read string.</returns>
        public string ReadValue(string section, string key) {
            var retVal = new StringBuilder(255);
            GetPrivateProfileString(section, key, "", retVal, 255, Path);
            return retVal.ToString();
        }

        public void DeleteKey(string section, string key) {
            WriteValue(section, key, null);
        }

        public void DeleteSection(string section = null) {
            WriteValue(section, null, null);
        }

        public bool KeyExists(string section, string key) {
            return ReadValue(key, section).Length > 0;
        }
    }
}