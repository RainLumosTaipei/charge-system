using charge_app.Core.Models;

namespace charge_app.Core.Res;

public class RegisterRes
{
    public int Id { get; set; }
    public User.UserType Type { get; set; }
}