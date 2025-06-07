
using charge_app.Core.Contracts.Services;

namespace charge_app.ViewModels;

public class LoginViewModel
{
    public string Username
    {
        get;
        set;
    }

    public string Password
    {
        get;
        set;
    }

    private readonly IUserService _userService;

    public LoginViewModel(IUserService userService)
    {
        _userService = userService;
    }

    public async Task<bool> LoginAsync()
    {
        return await _userService.Login(Username, Password);
    }
}