using charge_app.Core.Models;

using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;

namespace charge_app.Views;

public sealed partial class ParkDetailControl : UserControl
{
    public ChargingPile? ListDetailsMenuItem
    {
        get => GetValue(ListDetailsMenuItemProperty) as ChargingPile;
        set => SetValue(ListDetailsMenuItemProperty, value);
    }

    public static readonly DependencyProperty ListDetailsMenuItemProperty =
        DependencyProperty.Register(nameof(ListDetailsMenuItem), typeof(ChargingPile), typeof(ParkDetailControl),
            new PropertyMetadata(null, OnListDetailsMenuItemPropertyChanged));

    public ParkDetailControl()
    {
        InitializeComponent();
    }

    private static void OnListDetailsMenuItemPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
    {
        if (d is ParkDetailControl control)
        {
            control.ForegroundElement.ChangeView(0, 0, 1);
        }
    }

    private async void UpdatePileParameter(object sender, RoutedEventArgs e)
    {
        var button = sender as Button;
        var pile = button.Tag as ChargingPile;
        var dialog = new ChargePileDialog(pile);
        dialog.XamlRoot = this.XamlRoot;
        await dialog.ShowAsync();
    }
}
