using System.ComponentModel;
using System.Runtime.CompilerServices;
using charge_app.Core.Contracts.Services;

namespace charge_app.ViewModels;

public class LoginViewModel : INotifyPropertyChanged
{
    private readonly IUserService _userService;

    public LoginViewModel(IUserService userService)
    {
        _userService = userService;
    }


    private string _username;
    private string _password;
    public bool HasError { get; set; }
    public string ErrorMessage { get; set; }


    public string Username
    {
        get => _username;
        set
        {
            if (_username != value)
            {
                _username = value;
                OnPropertyChanged();
            }
        }
    }

    public string Password
    {
        get => _password;
        set
        {
            if (_password != value)
            {
                _password = value;
                OnPropertyChanged();
            }
        }
    }

    // 实现 INotifyPropertyChanged
    public event PropertyChangedEventHandler PropertyChanged;

    protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }

    public async Task<bool> LoginAsync()
    {
        return await _userService.Login(_username, _password);
    }
}