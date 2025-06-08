namespace charge_app.Core.Helpers;

public static class IconHelper
{
    private static readonly Random Random = new ();
    private static readonly char[] Icons =
    {
        '\uE716',
        '\uEE57',
        '\uEC87',
        '\uEC3B',
        '\uE862',
    };

    public static char RandomIcon()
    {
        var index = Random.Next(0, Icons.Length);
        return Icons[index];
    }
}