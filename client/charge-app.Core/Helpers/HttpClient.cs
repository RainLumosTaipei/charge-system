namespace charge_app.Core.Helpers;
using System.Net.Http;
using System.Text.Json;
using System.Threading.Tasks;

public class HttpClient
{


    public async Task GetDataAsync()
    {
        try
        {
            using var client = new HttpClient();
            var response = await client.GetAsync("https://api.example.com/data");

            // 检查HTTP状态码
            response.EnsureSuccessStatusCode();

            // 读取响应内容
            var json = await response.Content.ReadAsStringAsync();

            // 解析JSON（假设返回User对象数组）
            var users = JsonSerializer.Deserialize<User[]>(json);

            Console.WriteLine($"获取到 {users.Length} 个用户");
        }
        catch (HttpRequestException ex)
        {
            Console.WriteLine($"HTTP请求错误: {ex.Message}");
        }
        catch (JsonException ex)
        {
            Console.WriteLine($"JSON解析错误: {ex.Message}");
        }
    }
}