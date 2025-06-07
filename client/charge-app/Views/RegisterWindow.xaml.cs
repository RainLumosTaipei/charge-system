using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Navigation;
using Windows.Foundation;
using Windows.Foundation.Collections;
using charge_app.ViewModels;
using Microsoft.Windows.AppNotifications;
using Microsoft.Windows.AppNotifications.Builder;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace charge_app.Views;
/// <summary>
/// An empty page that can be used on its own or navigated to within a Frame.
/// </summary>
public sealed partial class RegisterWindow : Window
{
    private RegisterViewModel ViewModel
    {
        get;
    }

    public RegisterWindow()
    {
        this.InitializeComponent();
        ViewModel= App.GetService<RegisterViewModel>();
        AppWindow.Title = "注册";
        AppWindow.Resize(new Windows.Graphics.SizeInt32(600, 800));
        AppWindow.Move(new Windows.Graphics.PointInt32(800, 400));
    }

    private async void Register(object sender, RoutedEventArgs e)
    {
        bool res = await ViewModel.RegisterAsync();

        if (res)
        {
            AppNotification notification = new AppNotificationBuilder()
                .AddText("注册成功")
                .AddText("Explore interactive samples and discover the power of modern Windows UI.")
                .BuildNotification();

            AppNotificationManager.Default.Show(notification);
            Close();
        }
        else
        {
            AppNotification notification = new AppNotificationBuilder()
                .AddText("注册失败")
                .AddText("Explore interactive samples and discover the power of modern Windows UI.")
                .BuildNotification();

            AppNotificationManager.Default.Show(notification);
        }
    }

    private void Cancel(object sender, RoutedEventArgs e)
    {
        Close();
    }
}
