using charge_app.Core.Models;


namespace charge_app.Core.Contracts.Services;

public class OperationService : IOperationService
{
    private List<Operation> _ops;

    public OperationService()
    {
    }

    public async Task<IEnumerable<Operation>> GetOperations()
    {
        _ops ??= InitOperations();
        await Task.CompletedTask;
        return _ops;
    }

    private List<Operation> InitOperations()
    {
        var ops = new List<Operation>();
        ops.Add(new Operation("充电", "为您的设备新增充电请求",
            "charge_app.ViewModels.ChargeViewModel"));

        ops.Add(new Operation("充电时间", "修改您的充电请求时间",
            "charge_app.ViewModels.UpdateChargeTimeViewModel",
            "/Assets/icon/AnimationInterop.png"));

        ops.Add(new Operation("充电额度", "修改您的充电请求额度",
            "charge_app.ViewModels.UpdateChargeAmountViewModel",
            "/Assets/icon/AnnotatedScrollBar.png"));

        ops.Add(new Operation("充电类型", "修改您的充电请求类型",
            "charge_app.ViewModels.UpdateChargeTypeViewModel",
            "/Assets/icon/ScrollView.png"));

        ops.Add(new Operation("充电状态", "修改您的充电请求状态",
            "charge_app.ViewModels.UpdateChargeStateViewModel",
            "/Assets/icon/Canvas.png"));
        return ops;
    }
}