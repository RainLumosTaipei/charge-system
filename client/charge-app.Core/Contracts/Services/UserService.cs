using charge_app.Core.Helpers;
using charge_app.Core.Models;

namespace charge_app.Core.Contracts.Services;

public class UserService : IUserService
{

    public async Task<IEnumerable<User>> GetUsers()
    {
        try
        {
            var json = await HttpHelper.GetAsync("/user/all");
            var users = await JsonHelper.ToObjectAsync<User[]>(json);
            return users; // 返回IEnumerable<User>
        }
        catch (Exception ex)
        {
            Console.WriteLine($"can't get users: {ex.Message}");
            return Enumerable.Empty<User>();
        }
    }

    public async Task<bool> Register(string name, string password)
    {
        try
        {
            var json = await HttpHelper.GetAsync(
                "/CreateNewAccount?name=" + name + "&password=" + password);
            var u = await JsonHelper.ToObjectAsync<bool>(json);
            return u; // 返回IEnumerable<User>
        }
        catch (Exception ex)
        {
            Console.WriteLine($"can't get users: {ex.Message}");
            return false;
        }
    }

    public async Task<bool> Login(string name, string password)
    {
        try
        {
            var json = await HttpHelper.GetAsync(
                "/Login?name=" + name + "&password=" + password);
            var u = await JsonHelper.ToObjectAsync<bool>(json);
            return u; // 返回IEnumerable<User>
        }
        catch (Exception ex)
        {
            Console.WriteLine($"can't get users: {ex.Message}");
            return false;
        }
    }
}