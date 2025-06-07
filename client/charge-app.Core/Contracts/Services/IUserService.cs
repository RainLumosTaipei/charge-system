using charge_app.Core.Models;

namespace charge_app.Core.Contracts.Services;

public interface IUserService
{
    public Task<IEnumerable<User>> GetUsers();
}