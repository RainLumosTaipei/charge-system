using charge_app.Contracts.ViewModels;
using charge_app.Core.Contracts.Services;
using charge_app.Core.Models;

using CommunityToolkit.Mvvm.ComponentModel;

namespace charge_app.ViewModels;

public partial class OperationDetailViewModel : ObservableRecipient, INavigationAware
{
    private readonly IOperationService _sampleDataService;

    [ObservableProperty]
    private Operation? item;

    public OperationDetailViewModel(IOperationService sampleDataService)
    {
        _sampleDataService = sampleDataService;
    }

    public async void OnNavigatedTo(object parameter)
    {
        // if (parameter is long orderID)
        // {
        //     var data = await _sampleDataService.GetContentGridDataAsync();
        //     //Item = data.First(i => i.OrderID == orderID);
        // }
    }

    public void OnNavigatedFrom()
    {
    }
}
