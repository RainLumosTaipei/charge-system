using System.Collections.ObjectModel;

using charge_app.Contracts.ViewModels;
using charge_app.Core.Contracts.Services;
using charge_app.Core.Models;

using CommunityToolkit.Mvvm.ComponentModel;

namespace charge_app.ViewModels;

public partial class UserViewModel : ObservableRecipient, INavigationAware
{
    // get data
    private readonly IUserService _userService;
    private readonly IOrderService _orderService;

    [ObservableProperty]
    private UserDesc? selected;

    // data list to update to UI
    public ObservableCollection<UserDesc> UserItems { get; private set; } = new ObservableCollection<UserDesc>();

    // get data at ctor
    public UserViewModel(IUserService userService, IOrderService orderService)
    {
        _userService = userService;
        _orderService = orderService;
    }

    // navigate to get data, using async way
    public async void OnNavigatedTo(object parameter)
    {
        UserItems.Clear();

        // need to get real data
        var users = await _userService.GetUsers();

        foreach (var user in users)
        {
            var orders = await _orderService.GetOrdersById(user.Id);
            orders ??= Enumerable.Empty<Order>();
            UserItems.Add(new UserDesc(user, orders.ToArray()));
        }
    }

    public void OnNavigatedFrom()
    {
    }

    public void EnsureItemSelected()
    {
        Selected ??= UserItems.FirstOrDefault();
    }
}
