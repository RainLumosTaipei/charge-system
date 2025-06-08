using Newtonsoft.Json;

namespace charge_app.Core.Models;

public class ChargingPile
{
    public enum ChargingPileType
    {
        Slow = 0,
        Fast = 1
    }

    public uint Id { get; set; }
    public double Power { get; set; }
    public ChargingPileType Type { get; set; }
    public bool IsFaulty { get; set; }
    public int Count { get; set; }
    public double TotalTime { get; set; }
    public double ToTalPower { get; set; }

    [JsonIgnore] public string TextType => Type == ChargingPileType.Fast ? "快充" : "慢充";
    [JsonIgnore] public string TextIsFaulty => IsFaulty == true ? "故障" : "正常";
    [JsonIgnore] public char Symbol  => RandomIcon();
    [JsonIgnore] public string SymbolName  => "User";

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