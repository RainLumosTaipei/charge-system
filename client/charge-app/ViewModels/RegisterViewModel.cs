using charge_app.Core.Contracts.Services;
using charge_app.Core.Reqs;

namespace charge_app.ViewModels;

public class RegisterViewModel
{
    private readonly IUserService _userService;

    public RegisterViewModel(IUserService userService)
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


    public async Task<int> RegisterAsync()
    {
        var req = new RegisterReq(Username, Password);
        var res =  await _userService.Register(req);
        return res.Id;
    }
}