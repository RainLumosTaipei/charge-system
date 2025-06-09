using System.ComponentModel;
using System.Runtime.CompilerServices;
using charge_app.Core.Helpers;
using Newtonsoft.Json;

namespace charge_app.Core.Models;

public class UserDesc  : INotifyPropertyChanged
{
    public static uint Guid
    {
        get;
        set;
    } = 0;

    public static uint GQueueId
    {
        get;
        set;
    } = 0;

    public uint Id { get; set; }
    public string Name { get; set; }

    public User.UserType Type { get; set; }

    private Order[] _orders;
    public Order[] Orders
    {
        get => _orders;
        set
        {
            if (_orders != value)
            {
                _orders = value;
                OnPropertyChanged();
            }
        }
    }

    public UserDesc(User u, Order[] o)
    {
        Id = u.Id;
        Name = u.Name;
        Type = u.Type;
        Orders = o;
    }

    public event PropertyChangedEventHandler? PropertyChanged;

    protected virtual void OnPropertyChanged([CallerMemberName] string? propertyName = null)
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }


    [JsonIgnore] public string TextId => $"uid: {Id}";
    [JsonIgnore] public string TextType => Type == User.UserType.User ? "用户" : "管理员";

    [JsonIgnore] public char Symbol => '\uEA8C';

    [JsonIgnore] public string SymbolName => "Order";

    private static bool _isAdmin;

    public static bool IsAdmin
    {
        get => _isAdmin;
        set
        {
            if (_isAdmin != value)
            {
                _isAdmin = value;
                OnStaticPropertyChanged();
            }
        }
    }

    private static bool _isUser;

    public static bool IsUser
    {
        get => _isUser;
        set
        {
            if (_isUser != value)
            {
                _isUser = value;
                OnStaticPropertyChanged();
            }
        }
    }

    public static event PropertyChangedEventHandler StaticPropertyChanged;

    private static void OnStaticPropertyChanged([CallerMemberName] string propertyName = null)
    {
        StaticPropertyChanged?.Invoke(null, new PropertyChangedEventArgs(propertyName));
    }


}