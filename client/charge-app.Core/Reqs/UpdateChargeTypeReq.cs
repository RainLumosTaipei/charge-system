using charge_app.Core.Models;

namespace charge_app.Core.Reqs;

public class UpdateChargeTypeReq
{
    public uint QueueId { get; set; }
    public ChargingPile.ChargingPileType Type { get; set; }
}