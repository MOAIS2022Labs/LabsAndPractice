using TransportationLab2.Cargo.Unit;

namespace TransportationLab2.Client;

public interface IClient
{
    string Name { get; }
    string Surname { get; }
    City.City City { get; }
    ICargo? Order { get; set; }
    void GetOrder();
}