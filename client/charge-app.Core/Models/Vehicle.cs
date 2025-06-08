namespace charge_app.Core.Models;

public class Vehicle
{
    public ChargingPile.ChargingPileType Mode { get; set; }
    public string QueueNum { get; set; }
    public double ReqPower { get; set; }
    public double ChargeTime { get; set; }
    public ulong  Start { get; set; }
    public ulong End { get; set; }
    public double ElecFee { get; set; }
    public double ServFee { get; set; }
    public double TotalFee { get; set; }
}