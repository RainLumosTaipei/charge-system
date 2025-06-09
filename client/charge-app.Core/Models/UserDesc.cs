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

    public static bool GIsCharging
    {
        get;
        set;
    } = false;

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


    public static bool IsAdmin
    {
        get;
        set;

    } = false;

    public static bool IsUser
    {
        get;
        set;
    } = true;
}