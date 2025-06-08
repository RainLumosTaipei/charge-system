using charge_app.Core.Helpers;
using charge_app.Core.Models;
using charge_app.Core.Reqs;
using charge_app.Core.Res;

namespace charge_app.Core.Contracts.Services;

public class UserService : IUserService
{

    public async Task<IEnumerable<User>> GetUsers()
    {
        try
        {
            var json = await HttpHelper.GetAsync("/user/all");
            var users = await JsonHelper.ToObjectAsync<User[]>(json);
            return users;
        }
        catch (Exception ex)
        {
            Console.WriteLine($"can't get users: {ex.Message}");
            return Enumerable.Empty<User>();
        }
    }

    public async Task<RegisterRes> Register(RegisterReq req)
    {
        try
        {
            var json = await HttpHelper.GetAsync(
                "/user/register?" + req);
            return await JsonHelper.ToObjectAsync<RegisterRes>(json);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"can't get users: {ex.Message}");
            return null;
        }
    }

    public async Task<LoginRes> Login(LoginReq req)
    {
        try
        {
            var json = await HttpHelper.GetAsync(
                "/user/login?" + req);
            return await JsonHelper.ToObjectAsync<LoginRes>(json);

        }
        catch (Exception ex)
        {
            Console.WriteLine($"can't get users: {ex.Message}");
            return null;
        }
    }

    public async Task<ChargeRes> Charge(ChargeReq req)
    {
        try
        {
            var json = await HttpHelper.PostAsync(
                "/user/charge", req);
            var res = await JsonHelper.ToObjectAsync<ChargeRes>(json);
            return res;
        }
        catch (Exception ex)
        {
            Console.WriteLine($"can't get users: {ex.Message}");
            return null;
        }
    }

    public async Task<bool> UpdateCharge(UpdateChargeReq req)
    {
        try
        {
            var json = await HttpHelper.PostAsync(
                "/user/charge/update", req);
            var res = await JsonHelper.ToObjectAsync<UpdateChargeRes>(json);
            return res.Return;
        }
        catch (Exception ex)
        {
            Console.WriteLine($"can't get users: {ex.Message}");
            return false;
        }
    }
}