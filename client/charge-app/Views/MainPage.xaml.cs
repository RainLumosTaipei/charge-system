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

    public MainPage()
    {
        ViewModel = App.GetService<MainViewModel>();
        InitializeComponent();
    }

    private void Login(object sender, RoutedEventArgs e)
    {
        var wnd = new LoginWindow();
        wnd.Activate();
    }

    private void Register(object sender, RoutedEventArgs e)
    {
        var wnd = new RegisterWindow();
        wnd.Activate();
    }
}
