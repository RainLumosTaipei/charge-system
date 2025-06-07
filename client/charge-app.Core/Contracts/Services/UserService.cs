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
}