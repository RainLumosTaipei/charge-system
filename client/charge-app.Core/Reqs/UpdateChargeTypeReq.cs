using charge_app.Core.Models;

namespace charge_app.Core.Reqs;

public class UpdateChargeTypeReq
{
    public int QueueId { get; set; }
    public ChargingPile.ChargingPileType Type { get; set; }
}