namespace charge_app.Core.Models;

public class Operation
{
    public int Id { get; set; }
    public string ImagePath {get; set;}
    public string ImageName => "Icon";
    public string Title
    {
        get;
        set;
    }
    public string Description
    {
        get;
        set;
    }
    public string PageKey { get; set; }

    public Operation(string title, string description, string pageKey,
        string imagePath="/Assets/icon/VariableSizedWrapGrid.png")
    {
        Title = title;
        Description = description;
        ImagePath = imagePath;
        PageKey = pageKey;
        Id = Gid++;
    }

    public static int Gid = 0;

}