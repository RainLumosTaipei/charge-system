
using charge_app.Core.Models;
using charge_app.Core.Reqs;

namespace charge_app.Core.Contracts.Services;

public interface IChargingPileService
{
    public Task<IEnumerable<ChargingPile>> GetPiles();
    public Task<bool> UpdatePileParameter(UpdatePileParameterReq req);
}