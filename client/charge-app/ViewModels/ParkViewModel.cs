using System.Collections.ObjectModel;

using charge_app.Contracts.ViewModels;
using charge_app.Core.Contracts.Services;
using charge_app.Core.Models;

using CommunityToolkit.Mvvm.ComponentModel;

namespace charge_app.ViewModels;

public partial class ParkViewModel : ObservableRecipient, INavigationAware
{
    private readonly IChargingPileService _chargingPileService;

    [ObservableProperty]
    private ChargingPile? selected;

    public ObservableCollection<ChargingPile> PileItems { get; private set; } = new ObservableCollection<ChargingPile>();

    public ParkViewModel(IChargingPileService chargingPileService)
    {
        _chargingPileService = chargingPileService;
    }

    public async void OnNavigatedTo(object parameter)
    {
        PileItems.Clear();
        var piles = await _chargingPileService.GetPiles();

        foreach (var item in piles)
        {
            PileItems.Add(item);
        }
    }

    public void OnNavigatedFrom()
    {
    }

    public void EnsureItemSelected()
    {
        Selected ??= PileItems.FirstOrDefault();
    }
}
