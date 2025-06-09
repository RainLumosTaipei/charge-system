
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Navigation;
using charge_app.Contracts.Services;
using charge_app.Core.Models;
using charge_app.ViewModels;
using Microsoft.UI.Xaml;
using Microsoft.Windows.AppNotifications;
using Microsoft.Windows.AppNotifications.Builder;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace charge_app.Views;
/// <summary>
/// An empty page that can be used on its own or navigated to within a Frame.
/// </summary>
public sealed partial class UpdateChargeTypePage : Page
{
    public UpdateChargeTypePage()
    {
        InitializeComponent();
        ViewModel = App.GetService<UpdateChargeTypeViewModel>();
    }

    public UpdateChargeTypeViewModel ViewModel
    {
        get;
    }

    protected override void OnNavigatedTo(NavigationEventArgs e)
    {
        base.OnNavigatedTo(e);
    }

    protected override void OnNavigatingFrom(NavigatingCancelEventArgs e)
    {
        base.OnNavigatingFrom(e);
        if (e.NavigationMode == NavigationMode.Back)
        {
            var navigationService = App.GetService<INavigationService>();
        }
    }

    private async void FastType(object sender, RoutedEventArgs e)
    {
        ViewModel.Req.Type = ChargingPile.ChargingPileType.Fast;
        DropDownButton.Content = "快充";
        var res = await ViewModel.UpdateType();
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

    private async void SlowType(object sender, RoutedEventArgs e)
    {
        ViewModel.Req.Type = ChargingPile.ChargingPileType.Slow;
        DropDownButton.Content = "慢充";

        var res = await ViewModel.UpdateType();
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
