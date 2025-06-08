namespace charge_app.Core.Reqs;
using charge_app.Core.Models;

public class ChargeReq
{
    public int RequestAmount { get; set; }
    public ChargingPile.ChargingPileType RequestMode { get; set; }
}