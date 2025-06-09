using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using charge_app.Core.Helpers;
using Newtonsoft.Json;

namespace charge_app.Core.Models;

public class ChargingPile : INotifyPropertyChanged
{
    public enum ChargingPileType
    {
        Slow = 0,
        Fast = 1
    }


    public uint Id
    {
        get;
        set;
    }

    public double Power { get; set; }
    public ChargingPileType Type { get; set; }

    public bool IsFaulty
    {
        get;
        set;
    }


    public int Count { get; set; }
    public double TotalTime { get; set; }
    public double ToTalPower { get; set; }

    private ObservableCollection<Vehicle> _vehicles;
    public ObservableCollection<Vehicle> Queue
    {
        get => _vehicles;
        set
        {
            if (_vehicles != value)
            {
                _vehicles = value;
                OnPropertyChanged();
            }
        }
    }

    public event PropertyChangedEventHandler PropertyChanged;

    public virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }


    [JsonIgnore] public string TextType => Type == ChargingPileType.Fast ? "快充桩" : "慢充桩";
    [JsonIgnore] public string TextPower => $"{Power} 度/小时";
    [JsonIgnore] public string TextId => $"充电桩 {Id}";
    [JsonIgnore] public string TextTotalTime => $"{TotalTime:F2} 小时";
    [JsonIgnore] public string TextTotalPower => $"{ToTalPower:F2} 度";
    [JsonIgnore] public string TextIsFaulty => !IsFaulty ? "故障" : "正常";
    [JsonIgnore] public char Symbol  => '\uEC3B';
    [JsonIgnore] public string SymbolName  => "ChargingPile";

}