using charge_app.Core.Contracts.Services;

namespace charge_app.ViewModels;

public class RegisterViewModel
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

    public RegisterViewModel(IUserService userService)
    {
        _userService = userService;
    }

    public async Task<bool> RegisterAsync()
    {
        return await _userService.Register(Username, Password);
    }
}