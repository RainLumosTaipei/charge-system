using charge_app.ViewModels;

using CommunityToolkit.WinUI.UI.Controls;

using Microsoft.UI.Xaml.Controls;

namespace charge_app.Views;

public sealed partial class ParkPage : Page
{
    public ParkViewModel ViewModel
    {
        get;
    }

    public ParkPage()
    {
        ViewModel = App.GetService<ParkViewModel>();
        InitializeComponent();
    }

    private void OnViewStateChanged(object sender, ListDetailsViewState e)
    {
        if (e == ListDetailsViewState.Both)
        {
            ViewModel.EnsureItemSelected();
        }
    }
}
