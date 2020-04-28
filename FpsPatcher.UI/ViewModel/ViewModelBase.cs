using System.ComponentModel;
using System.Runtime.CompilerServices;
using FpsPatcher.UI.Annotations;
using System.Linq;


namespace FpsPatcher.UI.ViewModel {
    public class ViewModelBase : INotifyPropertyChanged {

        public ViewModelBase() {
            NotifyPropertyChanged = NotifyPropertyChangedNull;
        }

        protected delegate void NotifyPropertyChangedDelegate(params string[] propertyNames);

        protected NotifyPropertyChangedDelegate NotifyPropertyChanged;
        protected event PropertyChangedEventHandler _PropertyChanged;


        public event PropertyChangedEventHandler PropertyChanged {
            add {
                _PropertyChanged += value;
                NotifyPropertyChanged = NotifyPropertyChangedProper;
            }
            remove {
                _PropertyChanged -= value;
                if (_PropertyChanged == null) {
                    NotifyPropertyChanged = NotifyPropertyChangedNull;
                }
            }
        }


        protected void NotifyPropertyChangedProper(params string[] propertyNames) {
            foreach(string propertyName in propertyNames) {
                _PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }


        protected void NotifyPropertyChangedNull(params string[] propertyNames) {
        }
    }
}