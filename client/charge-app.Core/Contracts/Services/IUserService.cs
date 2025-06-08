using charge_app.Core.Models;
using charge_app.Core.Reqs;
using charge_app.Core.Res;

namespace charge_app.Core.Contracts.Services;

public interface IUserService
{
    public Task<IEnumerable<User>> GetUsers();

    public Task<bool> Register(RegisterReq req);
    public Task<bool> Login(LoginReq req);

    public Task<ChargeRes> Charge(ChargeReq req);

    public Task<bool> UpdateCharge(UpdateChargeReq req);
}