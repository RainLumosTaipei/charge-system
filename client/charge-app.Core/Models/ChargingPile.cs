using charge_app.Core.Helpers;
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
    public Vehicle[] Queue { get; set; }


    [JsonIgnore] public string TextType => Type == ChargingPileType.Fast ? "快充桩" : "慢充桩";
    [JsonIgnore] public string TextPower => $"{Power} 度/小时";
    [JsonIgnore] public string TextId => $"充电桩 {Id}";
    [JsonIgnore] public string TextTotalTime => $"{TotalTime:F2} 小时";
    [JsonIgnore] public string TextTotalPower => $"{ToTalPower:F2} 度";
    [JsonIgnore] public string TextIsFaulty => IsFaulty ? "故障" : "正常";
    [JsonIgnore] public char Symbol  => IconHelper.RandomIcon();
    [JsonIgnore] public string SymbolName  => "ChargingPile";

}