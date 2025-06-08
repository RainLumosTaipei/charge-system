using charge_app.Core.Helpers;
using charge_app.Core.Models;
using charge_app.Core.Reqs;
using charge_app.Core.Res;

namespace charge_app.Core.Contracts.Services;

public class ChargingPileService : IChargingPileService
{
    public async Task<IEnumerable<ChargingPile>> GetPiles()
    {
        try
        {
            var json = await HttpHelper.GetAsync("/pile/all");
            var piles = await JsonHelper.ToObjectAsync<ChargingPile[]>(json);
            return piles;
        }
        catch (Exception ex)
        {
            Console.WriteLine($"can't get users: {ex.Message}");
            return Enumerable.Empty<ChargingPile>();
        }
    }

    public async Task<bool> UpdatePileParameter(UpdatePileParameterReq req)
    {
        try
        {
            var json = await HttpHelper.PostAsync("/pile/update/cost", req);
            var res = await JsonHelper.ToObjectAsync<UpdatePileParameterRes>(json);
            return res.Return;
        }
        catch (Exception ex)
        {
            Console.WriteLine($"can't get users: {ex.Message}");
            return false;
        }
    }
}