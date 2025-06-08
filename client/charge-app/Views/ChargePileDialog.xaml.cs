
using charge_app.Core.Models;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using charge_app.ViewModels;
using Microsoft.Windows.AppNotifications;
using Microsoft.Windows.AppNotifications.Builder;


namespace charge_app.Views;
/// <summary>
/// An empty window that can be used on its own or navigated to within a Frame.
/// </summary>
public sealed partial class ChargePileDialog : ContentDialog
{
    public ChargePileViewModel ViewModel
    {
        get;
    }

    public ChargingPile Pile
    {
        get;
    }

    public ChargePileDialog(ChargingPile pile)
    {
        InitializeComponent();
        ViewModel = App.GetService<ChargePileViewModel>();
        Pile = pile;
    }

    private async void UpdatePileParameter(object sender, RoutedEventArgs e)
    {
        var res = await ViewModel.UpdatePileParameter(Pile);
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
        Hide();
    }
}
