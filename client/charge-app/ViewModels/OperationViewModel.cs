using System.Collections.ObjectModel;
using System.Windows.Input;

using charge_app.Contracts.Services;
using charge_app.Contracts.ViewModels;
using charge_app.Core.Contracts.Services;
using charge_app.Core.Models;

using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;

namespace charge_app.ViewModels;

public partial class OperationViewModel : ObservableRecipient, INavigationAware
{
    private readonly INavigationService _navigationService;
    private readonly IOperationService _opService;

    public ObservableCollection<Operation> Source { get; } = new ();

    public OperationViewModel(INavigationService navigationService, IOperationService opService)
    {
        _navigationService = navigationService;
        _opService = opService;
    }

    public async void OnNavigatedTo(object parameter)
    {
        Source.Clear();

        var data = await _opService.GetOperations();
        foreach (var item in data)
        {
            Source.Add(item);
        }
    }

    public void OnNavigatedFrom()
    {
    }

    [RelayCommand]
    private void OnItemClick(Operation? clickedItem)
    {
        if (clickedItem != null)
        {
            _navigationService.SetListDataItemForNextConnectedAnimation(clickedItem);
            _navigationService.NavigateTo(clickedItem.PageKey);
        }
    }
}
