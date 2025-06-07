namespace charge_app.Contracts.Services;

public interface IActivationService
{
    Task ActivateAsync(object activationArgs);
}
