using System.Collections.ObjectModel;

using charge_app.Contracts.ViewModels;
using charge_app.Core.Contracts.Services;
using charge_app.Core.Models;

using CommunityToolkit.Mvvm.ComponentModel;

namespace charge_app.ViewModels;

public partial class UserViewModel : ObservableRecipient, INavigationAware
{
    // get data
    private readonly ISampleDataService _sampleDataService;

    [ObservableProperty]
    private SampleOrder? selected;

    // data list to update to UI
    public ObservableCollection<SampleOrder> SampleItems { get; private set; } = new ObservableCollection<SampleOrder>();

    // get data at ctor
    public UserViewModel(ISampleDataService sampleDataService)
    {
        _sampleDataService = sampleDataService;
    }

    // navigate to get data, using async way
    public async void OnNavigatedTo(object parameter)
    {
        SampleItems.Clear();

        // need to get real data
        var data = await _sampleDataService.GetListDetailsDataAsync();

        foreach (var item in data)
        {
            SampleItems.Add(item);
        }
    }

    public void OnNavigatedFrom()
    {
    }

    public void EnsureItemSelected()
    {
        Selected ??= SampleItems.First();
    }
}
