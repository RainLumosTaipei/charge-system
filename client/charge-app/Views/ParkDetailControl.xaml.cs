using charge_app.Core.Models;
using charge_app.Core.Reqs;
using charge_app.ViewModels;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.Windows.AppNotifications;
using Microsoft.Windows.AppNotifications.Builder;

namespace charge_app.Views;

public sealed partial class ParkDetailControl : UserControl
{
    public ChargingPile? ListDetailsMenuItem
    {
        get => GetValue(ListDetailsMenuItemProperty) as ChargingPile;
        set => SetValue(ListDetailsMenuItemProperty, value);
    }

    public ChargePileViewModel ViewModel
    {
        get;
    }

    public static readonly DependencyProperty ListDetailsMenuItemProperty =
        DependencyProperty.Register(nameof(ListDetailsMenuItem), typeof(ChargingPile), typeof(ParkDetailControl),
            new PropertyMetadata(null, OnListDetailsMenuItemPropertyChanged));

    public ParkDetailControl()
    {
        InitializeComponent();
        ViewModel = App.GetService<ChargePileViewModel>();
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
        var dialog = new ChargePileDialog();
        dialog.XamlRoot = this.XamlRoot;
        await dialog.ShowAsync();
    }

    private async void UpdatePileState(object sender, RoutedEventArgs e)
    {
        var toggleSwitch = sender as ToggleSwitch;
        var pile = toggleSwitch.Tag as ChargingPile;
        if(pile == null) return;
        var isEnabled = toggleSwitch.IsOn;
        var res= await ViewModel.UpdatePileState(new UpdatePileStateReq(pile.Id, isEnabled));
        if (res)
        {
            var notification = new AppNotificationBuilder()
                .AddText("修改成功")
                .BuildNotification();

            AppNotificationManager.Default.Show(notification);
        }
        else
        {
            var notification = new AppNotificationBuilder()
                .AddText("修改失败")
                .BuildNotification();

            AppNotificationManager.Default.Show(notification);
        }
    }
}
