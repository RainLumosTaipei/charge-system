using charge_app.Core.Contracts.Services;
using charge_app.Core.Reqs;
using charge_app.Core.Res;

namespace charge_app.ViewModels;

public class LoginViewModel
{
    private readonly IUserService _userService;

    public LoginViewModel(IUserService userService)
    {
        _userService = userService;
    }


    public string? Username
    {
        get;
        set;
    }

    public string? Password
    {
        get;
        set;
    }


    public async Task<LoginRes> LoginAsync()
    {
        var req = new LoginReq(Username, Password);
        var res =  await _userService.Login(req);
        return res;
    }
}