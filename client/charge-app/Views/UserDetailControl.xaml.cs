using charge_app.Core.Models;

using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;

namespace charge_app.Views;

public sealed partial class UserDetailControl : UserControl
{
    // data
    public SampleOrder? ListDetailsMenuItem
    {
        get => GetValue(ListDetailsMenuItemProperty) as SampleOrder;
        set => SetValue(ListDetailsMenuItemProperty, value);
    }

    public static readonly DependencyProperty ListDetailsMenuItemProperty =
        DependencyProperty.Register("ListDetailsMenuItem", typeof(SampleOrder), typeof(UserDetailControl),
            new PropertyMetadata(null, OnListDetailsMenuItemPropertyChanged));

    public UserDetailControl()
    {
        InitializeComponent();
    }

    private static void OnListDetailsMenuItemPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
    {
        if (d is UserDetailControl control)
        {
            control.ForegroundElement.ChangeView(0, 0, 1);
        }
    }
}
