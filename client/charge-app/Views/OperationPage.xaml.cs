using charge_app.ViewModels;

using Microsoft.UI.Xaml.Controls;

namespace charge_app.Views;

public sealed partial class OperationPage : Page
{
    public OperationViewModel ViewModel
    {
        get;
    }

    public OperationPage()
    {
        ViewModel = App.GetService<OperationViewModel>();
        InitializeComponent();
    }
}
