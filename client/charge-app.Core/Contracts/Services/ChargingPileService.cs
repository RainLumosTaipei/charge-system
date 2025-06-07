using charge_app.Core.Helpers;
using charge_app.Core.Models;

namespace charge_app.Core.Contracts.Services;

public class ChargingPileService : IChargingPileService
{
    public async Task<IEnumerable<ChargingPile>> GetPiles()
    {
        try
        {
            var json = await HttpHelper.GetAsync("/pile/all");
            var piles = await JsonHelper.ToObjectAsync<ChargingPile[]>(json);
            return piles; // 返回IEnumerable<User>
        }
        catch (Exception ex)
        {
            Console.WriteLine($"can't get users: {ex.Message}");
            return Enumerable.Empty<ChargingPile>();
        }
    }
}