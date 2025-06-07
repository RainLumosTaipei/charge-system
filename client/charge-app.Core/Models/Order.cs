namespace charge_app.Core.Models;

public class Order
{
    public enum ChargingType
    {
        Slow = 0,
        Fast = 1,
    }
    public uint Id { get; set; }
    public uint Uid { get; set; }
    public long Start { get; set; }
    public long End { get; set; }
    public float Cost { get; set; }
    public ChargingType Type { get; set; }
}