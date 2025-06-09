using charge_app.Contracts.Services;
using charge_app.Contracts.ViewModels;
using charge_app.Core.Contracts.Services;
using CommunityToolkit.Mvvm.ComponentModel;
using Microsoft.UI.Xaml.Navigation;

namespace charge_app.ViewModels;

public class UpdateChargeAmountViewModel : ObservableRecipient, INavigationAware
{
    public IUserService UserService { get; }

    public UpdateChargeAmountViewModel(IUserService userService)
    {
        UserService = userService;
    }
    public async void OnNavigatedTo(object parameter)
    {
    }

    public void OnNavigatedFrom()
    {
    }
}