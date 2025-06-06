using System.ComponentModel;
using System.Runtime.CompilerServices;
using charge_app.Core.Contracts.Services;

namespace charge_app.ViewModels;

public class LoginViewModel
{
    private readonly IUserService _userService;

    public LoginViewModel(IUserService userService)
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


    public async Task<bool> LoginAsync()
    {
        return await _userService.Login(Username, Password);
    }
}