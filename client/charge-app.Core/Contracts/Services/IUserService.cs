using charge_app.Core.Models;

namespace charge_app.Core.Contracts.Services;

public interface IUserService
{
    public Task<IEnumerable<User>> GetUsers();

    public Task<bool> Register(string name, string password);
    public Task<bool> Login(string name, string password);
}