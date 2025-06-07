using charge_app.Core.Models;

using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;

namespace charge_app.Views;

public sealed partial class UserDetailControl : UserControl
{

    public static readonly DependencyProperty ListDetailsMenuItemProperty =
        DependencyProperty.Register("ListDetailsMenuItem", typeof(UserDesc), typeof(UserDetailControl),
            new PropertyMetadata(null, OnListDetailsMenuItemPropertyChanged));

    // data
    public UserDesc? ListDetailsMenuItem
    {
        get => GetValue(ListDetailsMenuItemProperty) as UserDesc;
        set => SetValue(ListDetailsMenuItemProperty, value);
    }

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
