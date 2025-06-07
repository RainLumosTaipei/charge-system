using charge_app.Core.Contracts.Services;

namespace charge_app.ViewModels;

public class RegisterViewModel
{
    private readonly IUserService _userService;

    public RegisterViewModel(IUserService userService)
    {
        _userService = userService;
    }
}