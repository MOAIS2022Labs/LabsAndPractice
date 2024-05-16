using TransportationLab2.Cargo.Unit;

namespace TransportationLab2.Cargo.Factory;

public interface ICargoFactory
{
    ICargo CreateCargo();
}