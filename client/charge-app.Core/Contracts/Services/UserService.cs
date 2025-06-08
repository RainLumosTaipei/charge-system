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

    public async Task<bool> Register(RegisterReq req)
    {
        try
        {
            var json = await HttpHelper.GetAsync(
                "/CreateNewAccount?" + req);
            var u = await JsonHelper.ToObjectAsync<RegisterRes>(json);
            return u.Return;
        }
        catch (Exception ex)
        {
            Console.WriteLine($"can't get users: {ex.Message}");
            return false;
        }
    }

    public async Task<bool> Login(LoginReq req)
    {
        try
        {
            var json = await HttpHelper.GetAsync(
                "/login?" + req);
            var u = await JsonHelper.ToObjectAsync<LoginRes>(json);
            return u.Return;
        }
        catch (Exception ex)
        {
            Console.WriteLine($"can't get users: {ex.Message}");
            return false;
        }
    }

    public async Task<ChargeRes> Charge(ChargeReq req)
    {
        try
        {
            var json = await HttpHelper.PostAsync(
                "/E_chargingRequest", req);
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
                "/Modify_Amount", req);
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