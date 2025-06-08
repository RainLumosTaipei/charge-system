
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


    public ChargePileDialog()
    {
        InitializeComponent();
        ViewModel = App.GetService<ChargePileViewModel>();
    }

    private async void UpdatePileParameter(object sender, RoutedEventArgs e)
    {
        var res = await ViewModel.UpdatePileParameter();
        if (res)
        {
            var notification = new AppNotificationBuilder()
                .AddText("修改成功")
                .BuildNotification();

            AppNotificationManager.Default.Show(notification);
            Hide();
        }
        else
        {
            var notification = new AppNotificationBuilder()
                .AddText("修改失败")
                .BuildNotification();

            AppNotificationManager.Default.Show(notification);
        }

    }

    private void Cancel(object sender, RoutedEventArgs e)
    {
        Hide();
    }
}
