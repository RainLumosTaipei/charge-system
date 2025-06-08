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
using charge_app.Core.Models;
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

        AppWindow.Resize(new Windows.Graphics.SizeInt32(600, 600));
        AppWindow.Move(new Windows.Graphics.PointInt32(1200, 500));

        AppWindow.TitleBar.BackgroundColor = Microsoft.UI.Colors.Black;
        AppWindow.TitleBar.ForegroundColor = Microsoft.UI.Colors.White;
        AppWindow.TitleBar.ButtonBackgroundColor = Microsoft.UI.Colors.Black;
        AppWindow.TitleBar.ButtonForegroundColor = Microsoft.UI.Colors.White;
        AppWindow.TitleBar.ButtonHoverBackgroundColor = Microsoft.UI.Colors.DarkGray;
        AppWindow.TitleBar.ButtonHoverForegroundColor = Microsoft.UI.Colors.White;
        AppWindow.TitleBar.ButtonPressedBackgroundColor = Microsoft.UI.Colors.Gray;
        AppWindow.TitleBar.ButtonPressedForegroundColor = Microsoft.UI.Colors.White;
    }

    private async void Register(object sender, RoutedEventArgs e)
    {
        int res = await ViewModel.RegisterAsync();

        if (res != -1)
        {
            UserDesc.Guid = (uint)res;
            var notification = new AppNotificationBuilder()
                .AddText("注册成功")
                .AddText("欢迎，" + ViewModel.Username)
                .BuildNotification();

            AppNotificationManager.Default.Show(notification);
            Close();
        }
        else
        {

            var notification = new AppNotificationBuilder()
                .AddText("注册失败")
                .AddText("抱歉，我们的服务出现了问题")
                .BuildNotification();

            AppNotificationManager.Default.Show(notification);
        }
    }

    private void Cancel(object sender, RoutedEventArgs e)
    {
        Close();
    }
}
