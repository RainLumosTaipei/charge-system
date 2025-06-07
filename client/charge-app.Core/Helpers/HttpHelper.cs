using System.Text;

namespace charge_app.Core.Helpers;
using System.Net.Http;
using System.Threading.Tasks;

public class HttpHelper
{
    private static string ServerIp = "http://127.0.0.1:8080";
    public static async Task<string> GetAsync(string url)
    {
        try
        {
            using var client = new HttpClient();
            var response = await client.GetAsync(ServerIp + url);

            // 检查HTTP状态码
            response.EnsureSuccessStatusCode();

            // 读取响应内容
            return await response.Content.ReadAsStringAsync();
        }
        catch (HttpRequestException ex)
        {
            Console.WriteLine($"HTTP err: {ex.Message}");
            throw;
        }
    }

    public static async Task<string> PostAsync(string url, object value)
    {
        try
        {
            using var client = new HttpClient();

            var json = await JsonHelper.StringifyAsync(value);
            var content = new StringContent(json, Encoding.UTF8, "application/json");

            var response = await client.PostAsync(ServerIp + url, content);
            response.EnsureSuccessStatusCode();

            return await response.Content.ReadAsStringAsync();
        }
        catch (HttpRequestException ex)
        {
            Console.WriteLine($"HTTP err: {ex.Message}");
            throw;
        }

    }
}