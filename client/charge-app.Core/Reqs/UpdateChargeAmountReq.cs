namespace charge_app.Core.Reqs;

public class UpdateChargeAmountReq
{
    public uint QueueId { get; set; }
    public double Amount { get; set; }
}