using charge_app.Contracts.Services;
using charge_app.Contracts.ViewModels;
using charge_app.Core.Contracts.Services;
using charge_app.Core.Models;
using charge_app.Core.Reqs;
using CommunityToolkit.Mvvm.ComponentModel;
using Microsoft.UI.Xaml.Navigation;

namespace charge_app.ViewModels;

public class UpdateChargeAmountViewModel : ObservableRecipient, INavigationAware
{
    public IUserService UserService { get; }

    public UpdateChargeAmountViewModel(IUserService userService)
    {
        UserService = userService;
        Req = new UpdateChargeAmountReq();
    }
    public async void OnNavigatedTo(object parameter)
    {
    }

    public void OnNavigatedFrom()
    {
    }

    public UpdateChargeAmountReq Req { get; }

    public async Task<bool> UpdateChargeAmount()
    {
        Req.QueueId = UserDesc.GQueueId;
        return await UserService.UpdateChargeAmount(Req);
    }
}