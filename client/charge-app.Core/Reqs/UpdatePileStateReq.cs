namespace charge_app.Core.Reqs;

public class UpdatePileStateReq
{
    public uint Id { get; set; }
    public uint State { get; set; }

    public override string ToString() => $"id={Id}&state={State}";

    public UpdatePileStateReq(uint id, bool state)
    {
        State = state ? 1u : 0u;
        Id = id;
    }
}