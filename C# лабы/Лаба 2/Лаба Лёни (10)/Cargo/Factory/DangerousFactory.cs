using TransportationLab2.Cargo.Unit;

namespace TransportationLab2.Cargo.Factory;

public class DangerousFactory(string name, int cost, int id) : ICargoFactory
{
    public ICargo CreateCargo()
    {
        Dangerous dangerousCargo = new Dangerous(name, cost, id);
        return dangerousCargo;
    }
}