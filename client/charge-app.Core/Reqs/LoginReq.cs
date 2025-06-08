namespace charge_app.Core.Reqs;

public class LoginReq
{
    public string name { get; set; }
    public string password { get; set; }

    public override string ToString() =>
        $"name={name}&password={password}";

    public LoginReq(string name, string password)
    {
        this.name = name;
        this.password = password;
    }
}