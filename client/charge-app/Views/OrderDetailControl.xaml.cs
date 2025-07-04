﻿using charge_app.Core.Models;

using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;

namespace charge_app.Views;

public sealed partial class OrderDetailControl : UserControl
{
    public Order? ListDetailsMenuItem
    {
        get => GetValue(ListDetailsMenuItemProperty) as Order;
        set => SetValue(ListDetailsMenuItemProperty, value);
    }

    public static readonly DependencyProperty ListDetailsMenuItemProperty =
        DependencyProperty.Register(nameof(ListDetailsMenuItem), typeof(Order), typeof(OrderDetailControl),
            new PropertyMetadata(null, OnListDetailsMenuItemPropertyChanged));

    public OrderDetailControl()
    {
        InitializeComponent();
    }

    private static void OnListDetailsMenuItemPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
    {
        if (d is OrderDetailControl control)
        {
            control.ForegroundElement.ChangeView(0, 0, 1);
        }
    }
}
