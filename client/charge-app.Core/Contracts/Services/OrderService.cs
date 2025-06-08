using charge_app.Core.Helpers;
using charge_app.Core.Models;

namespace charge_app.Core.Contracts.Services;

public class OrderService : IOrderService
{
    public async Task<IEnumerable<Order>> GetOrdersById(uint id)
    {
        try
        {
            var json = await HttpHelper.GetAsync("/order?id=" + id);
            var orders = await JsonHelper.ToObjectAsync<Order[]>(json);
            return orders;
        }
        catch (Exception ex)
        {
            Console.WriteLine($"can't get users: {ex.Message}");
            return Enumerable.Empty<Order>();
        }
    }

}