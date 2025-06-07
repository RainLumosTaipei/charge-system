
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Data;

namespace charge_app.Converters
{
    public class BoolToVisibilityConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            // 将布尔值转换为 Visibility
            bool boolValue = (value is bool) ? (bool)value : false;
            return boolValue ? Visibility.Visible : Visibility.Collapsed;
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            // 将 Visibility 转换回布尔值
            Visibility visibility = (Visibility)value;
            return visibility == Visibility.Visible;
        }
    }
}