namespace charge_app.Core.Helpers;

public static class TimeHelper
{
    public static string ConvertTime(long time)
    {
        var dateTime = DateTimeOffset.FromUnixTimeSeconds(time);
        return dateTime.ToLocalTime().ToString("yyyy-MM-dd HH:mm:ss");
    }
}