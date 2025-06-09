
using charge_app.Contracts.Services;
using charge_app.Core.Models;
using charge_app.ViewModels;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Navigation;
using Microsoft.Windows.AppNotifications;
using Microsoft.Windows.AppNotifications.Builder;


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace charge_app.Views;
/// <summary>
/// An empty page that can be used on its own or navigated to within a Frame.
/// </summary>
public sealed partial class ChargePage : Page
{
    public ChargeViewModel ViewModel { get; }
    public ChargePage()
    {
        InitializeComponent();
        ViewModel = App.GetService<ChargeViewModel>();
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

    private async void Charge(object sender, RoutedEventArgs e)
    {
        var res = await ViewModel.Charge();
        if (res.Return)
        {
            UserDesc.GQueueId = res.QueneId;
            UserDesc.GIsCharging = true;
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

    private void FastType(object sender, RoutedEventArgs e)
    {
        ViewModel.Req.Type = ChargingPile.ChargingPileType.Fast;
        DropDownButton.Content = "快充";
    }

    private void SlowType(object sender, RoutedEventArgs e)
    {
        ViewModel.Req.Type = ChargingPile.ChargingPileType.Slow;
        DropDownButton.Content = "慢充";
    }
}
