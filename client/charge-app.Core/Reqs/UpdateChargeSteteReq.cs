namespace charge_app.Core.Reqs;

public class UpdateChargeSteteReq
{
    public int QueueId { get; set; }
    public bool IsCharging { get; set; }
}