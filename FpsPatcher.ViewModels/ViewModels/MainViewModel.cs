using System.Collections.ObjectModel;
using System.Threading.Tasks;


namespace FpsPatcher.ViewModels {
    public class MainViewModel : BaseViewModel {

        public int FpsLimit { get; set; } = 120;
        public bool OneFrameThreadLag { get; set; } = true;
        public bool FinishCurrentFrame { get; set; } = false;

        public MainViewModel() {
            
        }
    }
}
