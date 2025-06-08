using System.Collections.ObjectModel;
using charge_app.Contracts.ViewModels;
using charge_app.Core.Contracts.Services;
using charge_app.Core.Models;
using CommunityToolkit.Mvvm.ComponentModel;

namespace charge_app.ViewModels;

public partial class OrderViewModel : ObservableRecipient, INavigationAware
{
    private readonly IOrderService _orderService;

    [ObservableProperty]
    private Order? selected;

    public ObservableCollection<Order> OrderItems { get; private set; } = new ();

    public OrderViewModel(IOrderService orderService)
    {
        _orderService = orderService;
    }

    public async void OnNavigatedTo(object parameter)
    {
        OrderItems.Clear();

        var orders = await _orderService.GetOrdersById(UserDesc.Guid);

        foreach (var item in orders)
        {
            OrderItems.Add(item);
        }
    }

    public void OnNavigatedFrom()
    {
    }

    public void EnsureItemSelected()
    {
        Selected ??= OrderItems.FirstOrDefault();
    }
}
