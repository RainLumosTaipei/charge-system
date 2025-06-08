

using charge_app.Core.Models;
using charge_app.ViewModels;
using Microsoft.UI.Xaml;

using Microsoft.Windows.AppNotifications;
using Microsoft.Windows.AppNotifications.Builder;


namespace charge_app.Views;

public sealed partial class LoginWindow : Window
{
    private LoginViewModel ViewModel
    {
        get;
    }

    public LoginWindow()
    {
        InitializeComponent();
        ViewModel= App.GetService<LoginViewModel>();


        AppWindow.Title = "登录";
        AppWindow.Resize(new Windows.Graphics.SizeInt32(600, 800));
        AppWindow.Move(new Windows.Graphics.PointInt32(800, 400));

        AppWindow.TitleBar.BackgroundColor = Microsoft.UI.Colors.Black;
        AppWindow.TitleBar.ForegroundColor = Microsoft.UI.Colors.White;
        AppWindow.TitleBar.ButtonBackgroundColor = Microsoft.UI.Colors.Black;
        AppWindow.TitleBar.ButtonForegroundColor = Microsoft.UI.Colors.White;
        AppWindow.TitleBar.ButtonHoverBackgroundColor = Microsoft.UI.Colors.DarkGray;
        AppWindow.TitleBar.ButtonHoverForegroundColor = Microsoft.UI.Colors.White;
        AppWindow.TitleBar.ButtonPressedBackgroundColor = Microsoft.UI.Colors.Gray;
        AppWindow.TitleBar.ButtonPressedForegroundColor = Microsoft.UI.Colors.White;
    }

    // 处理登录逻辑
    private async void Login(object sender, RoutedEventArgs e)
    {
        int res = await ViewModel.LoginAsync();

        if (res != -1)
        {
            UserDesc.Guid = (uint)res;
            var notification = new AppNotificationBuilder()
                .AddText("登录成功")
                .AddText("欢迎，" + ViewModel.Username)
                .BuildNotification();

            AppNotificationManager.Default.Show(notification);
            Close();
        }
        else
        {
            var notification = new AppNotificationBuilder()
                .AddText("登录失败")
                .AddText("用户名或密码有误")
                .BuildNotification();

            AppNotificationManager.Default.Show(notification);
        }
    }

    private void Cancel(object sender, RoutedEventArgs e)
    {
        Close();
    }
}
