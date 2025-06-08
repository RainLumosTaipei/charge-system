using charge_app.Core.Helpers;
using Newtonsoft.Json;

namespace charge_app.Core.Models;

public class Vehicle
{
    public ChargingPile.ChargingPileType Type { get; set; }
    public uint QueueId { get; set; }
    public double ReqPower { get; set; }
    public double ChargeTime { get; set; }
    public long Start { get; set; }
    public long End { get; set; }
    public double ElecFee { get; set; }
    public double ServFee { get; set; }
    public double TotalFee { get; set; }

    [JsonIgnore] public string TextType => Type == ChargingPile.ChargingPileType.Fast ? "快充" : "慢充";
    [JsonIgnore] public string TextElecFee => $"{ElecFee:F2}元";
    [JsonIgnore] public string TextServFee => $"{ServFee:F2}元";
    [JsonIgnore] public string TextTotalFee => $"{TotalFee:F2}元";
    [JsonIgnore] public string TextChargeTime => $"{ChargeTime:F2}小时";
    [JsonIgnore] public string TextReqPower => $"{ReqPower:F2}度";
    [JsonIgnore] public string TextStart => TimeHelper.ConvertTime(Start);
    [JsonIgnore] public string TextEnd => TimeHelper.ConvertTime(End);


}