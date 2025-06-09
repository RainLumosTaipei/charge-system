using charge_app.Core.Models;

namespace charge_app.Core.Contracts.Services;

public interface IOperationService
{
    public Task<IEnumerable<Operation>> GetOperations();
}