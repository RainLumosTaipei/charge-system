﻿using charge_app.Core.Models;

namespace charge_app.Core.Contracts.Services;

// Remove this class once your pages/features are using your data.
public interface ISampleDataService
{
    // async get data
    Task<IEnumerable<SampleOrder>> GetListDetailsDataAsync();
}
