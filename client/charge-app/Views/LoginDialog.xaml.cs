
using charge_app.Core.Contracts.Services;
using charge_app.ViewModels;
using Microsoft.UI.Xaml.Controls;


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace charge_app.Views;
/// <summary>
/// An empty page that can be used on its own or navigated to within a Frame.
/// </summary>
public sealed partial class LoginDialog : ContentDialog
{

    private readonly LoginViewModel _viewModel;

    public LoginDialog()
    {
        this.InitializeComponent();
        _viewModel= App.GetService<LoginViewModel>();
        DataContext = _viewModel;
        Title = "用户登录";
        PrimaryButtonText = "登录";
        CloseButtonText = "取消";
    }

    // 处理登录逻辑
    private async void ContentDialog_PrimaryButtonClick(ContentDialog sender, ContentDialogButtonClickEventArgs args)
    {
        // 验证输入
        if (string.IsNullOrEmpty(_viewModel.Username) || string.IsNullOrEmpty(_viewModel.Password))
        {
            _viewModel.ErrorMessage = "用户名和密码不能为空";
            _viewModel.HasError = true;
            return;
        }

        // 调用 ViewModel 的登录方法（假设已定义）
        bool loginSuccess = await _viewModel.LoginAsync();

        if (loginSuccess)
        {
            // 登录成功，对话框会自动关闭
        }
        else
        {
            _viewModel.ErrorMessage = "登录失败，请检查用户名和密码";
            _viewModel.HasError = true;
        }
    }
}
