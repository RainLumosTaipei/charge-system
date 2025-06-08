using Newtonsoft.Json;

namespace charge_app.Core.Models;

public class UserDesc
{
    public static uint Guid { get; set; }
    public uint Id { get; set; }
    public string Name { get; set; }

    public User.UserType Type { get; set; }

    public Order[] Orders { get; set; }
    public uint CarId { get; set; }


    [JsonIgnore]
    public string TextId { get => $"uid: {Id}"; }
    [JsonIgnore]
    public char Symbol { get => RandomIcon(); }
    [JsonIgnore]
    public string SymbolName { get => "User"; }

    public UserDesc(User u, Order[] o)
    {
        Id = u.Id;
        Name = u.Name;
        Type = u.Type;
        CarId = u.CarId;
        Orders = o;
    }

    private static readonly Random _random = new Random();
    private static readonly char[] _icons = new[]
    {
        '\uE716',
        '\uEE57',
        '\uEC87',
        '\uEC3B',
        '\uE862',
    };

    private char RandomIcon()
    {
        int index = _random.Next(0, _icons.Length);
        return _icons[index];
    }
}