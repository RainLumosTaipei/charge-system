using Newtonsoft.Json;

namespace charge_app.Core.Models;

public class User
{
    public enum UserType
    {
        Admin = 0,
        User = 1,
    }

    public uint Id { get; set; }
    public string Name { get; set; }
    public string Password { get; set; }
    public UserType Type { get; set; }

}