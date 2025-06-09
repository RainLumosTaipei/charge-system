using charge_app.Contracts.ViewModels;
using charge_app.Core.Contracts.Services;
using charge_app.Core.Reqs;
using CommunityToolkit.Mvvm.ComponentModel;

namespace charge_app.ViewModels;

public class UpdateChargeTypeViewModel : ObservableRecipient, INavigationAware
{
    public IUserService UserService { get; }

    public UpdateChargeTypeViewModel(IUserService userService)
    {
        UserService = userService;
        Req = new UpdateChargeTypeReq();
    }
    public async void OnNavigatedTo(object parameter)
    {
    }

    public void OnNavigatedFrom()
    {
    }

    public UpdateChargeTypeReq Req { get; }

    public async Task<bool> UpdateType()
    {
        return await UserService.UpdateChargeType(Req);
    }
}