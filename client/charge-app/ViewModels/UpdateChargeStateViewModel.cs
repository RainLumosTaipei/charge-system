using charge_app.Contracts.ViewModels;
using charge_app.Core.Contracts.Services;
using charge_app.Core.Models;
using charge_app.Core.Reqs;
using CommunityToolkit.Mvvm.ComponentModel;

namespace charge_app.ViewModels;

public class UpdateChargeStateViewModel : ObservableRecipient, INavigationAware
{
    public IUserService UserService { get; }

    public UpdateChargeStateViewModel(IUserService userService)
    {
        UserService = userService;
        Req = new UpdateChargeStateReq();
    }
    public async void OnNavigatedTo(object parameter)
    {
    }

    public void OnNavigatedFrom()
    {
    }

    public UpdateChargeStateReq Req { get; }

    public async Task<bool> UpdateState(bool state)
    {
        Req.QueueId = UserDesc.GQueueId;
        Req.IsCharging = state;
        return await UserService.UpdateChargeState(Req);
    }
}