using charge_app.ViewModels;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;

namespace charge_app.Views;

public sealed partial class MainPage : Page
{
    public MainViewModel ViewModel
    {
        get;
    }

    // private WindowManager LoginWnd = WindowManager.Get(new LoginWindow());
    // private WindowManager RegisterWnd = WindowManager.Get(new RegisterWindow());

    public MainPage()
    {
        ViewModel = App.GetService<MainViewModel>();
        InitializeComponent();
        // LoginWnd.IsAlwaysOnTop = true;
        // LoginWnd.IsResizable = false;
        // RegisterWnd.IsAlwaysOnTop = true;
        // LoginWnd.IsResizable = false;
    }

    private void Login(object sender, RoutedEventArgs e)
    {
        var loginWindow = new LoginWindow();
        loginWindow.Show();
    }

    private void Register(object sender, RoutedEventArgs e)
    {
        var registerWindow = new RegisterWindow();
        registerWindow.Show();
    }
}
