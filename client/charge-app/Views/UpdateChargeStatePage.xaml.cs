
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Navigation;
using charge_app.Contracts.Services;
using charge_app.Core.Models;
using charge_app.Core.Reqs;
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
public sealed partial class UpdateChargeStatePage : Page
{
    public UpdateChargeStateViewModel? ViewModel
    {
        get;
        private set;
    }

    public UpdateChargeStatePage()
    {
        InitializeComponent();
        ViewModel = App.GetService<UpdateChargeStateViewModel>();
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

    private async void UpdateState(object sender, RoutedEventArgs e)
    {
        var toggleSwitch = sender as ToggleSwitch;
        if (toggleSwitch == null) return;
        var isEnabled = toggleSwitch.IsOn;
        if(ViewModel == null) return;

        var res= await ViewModel.UpdateState(isEnabled);
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
