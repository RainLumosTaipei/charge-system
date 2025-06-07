using charge_app.Core.Models;

public interface IChargingPileService
{
    public Task<IEnumerable<ChargingPile>> GetPiles();
}