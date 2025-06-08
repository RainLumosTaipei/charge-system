using charge_app.Core.Helpers;
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

    [JsonIgnore] public string TextType => Type == ChargingPile.ChargingPileType.Fast ? "快充型" : "慢充型";
    [JsonIgnore] public string TextStart => TimeHelper.ConvertTime(Start);
    [JsonIgnore] public string TextEnd => TimeHelper.ConvertTime(End);
    [JsonIgnore] public string TextCost => $"{Cost:F2} 元";
    [JsonIgnore] public string TextId => $"订单号 {Id}";
    [JsonIgnore] public char Symbol => IconHelper.RandomIcon();
    [JsonIgnore] public string SymbolName => "Order";


}