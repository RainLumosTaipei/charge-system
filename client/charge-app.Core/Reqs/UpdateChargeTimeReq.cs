namespace charge_app.Core.Reqs;

public class UpdateChargeTimeReq
{
    public uint QueueId { get; set; }
    public double ChargeTime { get; set; }
}