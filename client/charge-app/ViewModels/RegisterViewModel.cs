using charge_app.Core.Contracts.Services;

namespace charge_app.ViewModels;

public class RegisterViewModel
{
    private readonly IUserService _userService;

    public RegisterViewModel(IUserService userService)
    {
        _userService = userService;
    }

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


    public async Task<bool> RegisterAsync()
    {
        return await _userService.Register(Username, Password);
    }
}