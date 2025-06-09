using charge_app.Contracts.ViewModels;
using charge_app.Core.Contracts.Services;
using CommunityToolkit.Mvvm.ComponentModel;

namespace charge_app.ViewModels;

public class UpdateChargeTimeViewModel : ObservableRecipient, INavigationAware
{
    public IUserService UserService { get; }

    public UpdateChargeTimeViewModel(IUserService userService)
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