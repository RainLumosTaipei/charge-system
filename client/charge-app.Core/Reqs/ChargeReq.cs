namespace charge_app.Core.Reqs;
using charge_app.Core.Models;

public class ChargeReq
{
    public uint Uid { get; set; }
    public double Amount { get; set; }
    public ChargingPile.ChargingPileType Type { get; set; }
}