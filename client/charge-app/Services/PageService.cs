using charge_app.Contracts.Services;
using charge_app.ViewModels;
using charge_app.Views;

using CommunityToolkit.Mvvm.ComponentModel;

using Microsoft.UI.Xaml.Controls;

namespace charge_app.Services;

public class PageService : IPageService
{
    private readonly Dictionary<string, Type> _pages = new();

    public PageService()
    {
        Configure<MainViewModel, MainPage>();
        Configure<UserViewModel, UserPage>();
        Configure<ParkViewModel, ParkPage>();
        Configure<OrderViewModel, OrderPage>();
        Configure<SettingsViewModel, SettingsPage>();
        Configure<OperationViewModel, OperationPage>();
        Configure<ChargeViewModel, ChargePage>();
        Configure<UpdateChargeAmountViewModel, UpdateChargeAmountPage>();
        Configure<UpdateChargeTimeViewModel, UpdateChargeTimePage>();
    }

    public Type GetPageType(string key)
    {
        Type? pageType;
        lock (_pages)
        {
            if (!_pages.TryGetValue(key, out pageType))
            {
                throw new ArgumentException($"Page not found: {key}. Did you forget to call PageService.Configure?");
            }
        }

        return pageType;
    }

    private void Configure<VM, V>()
        where VM : ObservableObject
        where V : Page
    {
        lock (_pages)
        {
            var key = typeof(VM).FullName!;
            if (_pages.ContainsKey(key))
            {
                throw new ArgumentException($"The key {key} is already configured in PageService");
            }

            var type = typeof(V);
            if (_pages.ContainsValue(type))
            {
                throw new ArgumentException($"This type is already configured with key {_pages.First(p => p.Value == type).Key}");
            }

            _pages.Add(key, type);
        }
    }
}
