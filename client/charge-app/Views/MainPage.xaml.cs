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

    private async void Login(object sender, RoutedEventArgs e)
    {
        var dialog = new LoginDialog();
        dialog.XamlRoot = this.Content.XamlRoot;
        await dialog.ShowAsync();
    }

    private async void Register(object sender, RoutedEventArgs e)
    {
        var dialog = new RegisterDialog();
        dialog.XamlRoot = this.Content.XamlRoot;
        await dialog.ShowAsync();
    }
}
