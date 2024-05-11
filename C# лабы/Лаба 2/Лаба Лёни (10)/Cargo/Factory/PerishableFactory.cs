using TransportationLab2.Cargo.Unit;

namespace TransportationLab2.Cargo.Factory;

public class PerishableFactory(string name, int cost,  int id) : ICargoFactory
{
    public ICargo CreateCargo()
    {
        Perishable perishableCargo = new Perishable(name, cost, id);
        return perishableCargo;
    }
}