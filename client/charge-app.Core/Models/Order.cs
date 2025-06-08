using Newtonsoft.Json;

namespace charge_app.Core.Models;

public class Order
{

    public uint Id { get; set; }
    public uint Uid { get; set; }
    public long Start { get; set; }
    public long End { get; set; }
    public float Cost { get; set; }
    public ChargingPile.ChargingPileType Type { get; set; }

    [JsonIgnore] public string TextType => Type == ChargingPile.ChargingPileType.Fast ? "快充" : "慢充";
    [JsonIgnore] public char Symbol => RandomIcon();

    [JsonIgnore] public string SymbolName => "User";

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