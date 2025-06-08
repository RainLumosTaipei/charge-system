using charge_app.Core.Helpers;
using Newtonsoft.Json;

namespace charge_app.Core.Models;

public class UserDesc
{
    public static uint Guid { get; set; }
    public uint Id { get; set; }
    public string Name { get; set; }

    public User.UserType Type { get; set; }

    public Order[] Orders { get; set; }

    public UserDesc(User u, Order[] o)
    {
        Id = u.Id;
        Name = u.Name;
        Type = u.Type;
        Orders = o;
    }


    [JsonIgnore] public string TextId => $"uid: {Id}";

    [JsonIgnore] public char Symbol => IconHelper.RandomIcon();

    [JsonIgnore] public string SymbolName => "Order";


}