namespace charge_app.Core.Reqs;

public class RegisterReq
{
    public string name { get; set; }
    public string password { get; set; }

    public override string ToString() =>
        $"name={name}&password={password}";

    public RegisterReq(string name, string password)
    {
        this.name = name;
        this.password = password;
    }
}