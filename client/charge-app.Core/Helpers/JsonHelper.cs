using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace charge_app.Core.Helpers;

// json serialize
public static class JsonHelper
{
    private static JsonSerializerSettings settings = new JsonSerializerSettings
    {
        // first letter lowercase
        ContractResolver = new CamelCasePropertyNamesContractResolver()
    };
    // parse string to object
    public static async Task<T> ToObjectAsync<T>(string value)
    {
        return await Task.Run<T>(() =>
        {
            return JsonConvert.DeserializeObject<T>(value, settings);
        });
    }

    // serialize object to string
    public static async Task<string> StringifyAsync(object value)
    {
        return await Task.Run<string>(() =>
        {
            return JsonConvert.SerializeObject(value, settings);
        });
    }
}
