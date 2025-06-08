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


    public async Task<bool> RegisterAsync()
    {
        var req = new RegisterReq(Username, Password);
        return await _userService.Register(req);
    }
}