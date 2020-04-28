using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Patcher.Injections {
    internal abstract class CodeCaveInjection {

        public CodeCaveInjection() {
            
        }


        public int InjectionInstructionsLength { get; protected set; }
        public IntPtr InjectionAddress { get; protected set; }
        public IntPtr CodeCaveAddress { get; protected set; }
        public byte[] InjectionMachineCode { get; protected set; }
        public byte[] OriginalMachineCode { get; protected set; }

        public abstract void Inject();
        public abstract void CancelInjection();

        protected List<byte> AppendTrampoline(ICollection<byte> machineCode, IntPtr jumpSource, IntPtr jumpDestination) {
            var machineCodeList = machineCode.ToList();

            machineCodeList.AddRange(new byte[] { 0xE9 }); // jmp
            int jumpBackOffset = (int)jumpDestination - ((int)jumpSource + 5);
            machineCodeList.AddRange(BitConverter.GetBytes(jumpBackOffset));

            return machineCodeList;
        }
    }
}
