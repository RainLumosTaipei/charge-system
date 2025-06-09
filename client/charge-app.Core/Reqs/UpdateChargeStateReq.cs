namespace charge_app.Core.Reqs;

public class UpdateChargeStateReq
{
    public uint QueueId { get; set; }
    public bool IsCharging { get; set; }
}