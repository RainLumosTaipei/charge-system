using charge_app.Core.Models;

namespace charge_app.Core.Contracts.Services;

public interface IOrderService
{
    public Task<IEnumerable<Order>> GetOrdersById(uint id);
}