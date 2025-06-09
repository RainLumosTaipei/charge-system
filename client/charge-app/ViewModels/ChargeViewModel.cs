using charge_app.Contracts.ViewModels;
using charge_app.Core.Contracts.Services;
using charge_app.Core.Models;
using charge_app.Core.Reqs;
using charge_app.Core.Res;
using CommunityToolkit.Mvvm.ComponentModel;

namespace charge_app.ViewModels;

public class ChargeViewModel : ObservableRecipient, INavigationAware
{
    public IUserService UserService { get; }

    public ChargeReq? Req
    {
        get;
        set;
    }

    public ChargeViewModel(IUserService userService)
    {
        UserService = userService;
        Req = new ChargeReq();
    }
    public async void OnNavigatedTo(object parameter)
    {
    }

    public void OnNavigatedFrom()
    {
    }

    public async Task<ChargeRes> Charge()
    {
        Req.Uid = UserDesc.Guid;
        var res = await UserService.Charge(Req);
        return res;
    }
}