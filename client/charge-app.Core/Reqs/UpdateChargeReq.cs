namespace charge_app.Core.Reqs;

public class UpdateChargeReq
{
    public uint QueueId { get; set; }
    public double ChargeTime { get; set; }
}