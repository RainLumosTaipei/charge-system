using charge_app.Core.Contracts.Services;
using charge_app.Core.Models;
using charge_app.Core.Reqs;

namespace charge_app.ViewModels;

public class ChargePileViewModel
{
    private IChargingPileService _chargePileService;
    public UpdatePileParameterReq Req { get; set; }
    public async Task<bool> UpdatePileParameter(ChargingPile pile)
    {
        Req.Id = pile.Id;
        return await _chargePileService.UpdatePileParameter(Req);
    }

    public ChargePileViewModel(IChargingPileService chargePileService)
    {
        _chargePileService = chargePileService;
        Req = new UpdatePileParameterReq();
    }
}