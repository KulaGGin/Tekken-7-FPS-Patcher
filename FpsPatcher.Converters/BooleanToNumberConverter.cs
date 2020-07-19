using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;

namespace FpsPatcher.Converters {
    public class BooleanToNumberConverter : IValueConverter {

        #region Implementation of IValueConverter

        public object Convert(object value, Type targetType, object parameter, CultureInfo culture) {
            bool booleanValue = (bool)value;
            return System.Convert.ToInt32(booleanValue);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture) {
            int intValue;
            int.TryParse((string)value, out intValue);
            return System.Convert.ToBoolean(intValue);
            
        }

        #endregion

    }
}
