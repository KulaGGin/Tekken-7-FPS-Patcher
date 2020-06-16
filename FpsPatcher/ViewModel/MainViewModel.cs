using System.Collections.ObjectModel;
using System.Threading.Tasks;


namespace FpsPatcher.UI.ViewModel {
    public class MainViewModel : ViewModelBase {

        public int FpsLimit { get; set; } = 120;
        public bool OneFrameThreadLag { get; set; } = true;
        public bool FinishCurrentFrame { get; set; } = false;

        public MainViewModel() {
            
        }
    }
}
