using TransportationLab2.Cargo.Unit;

namespace TransportationLab2.Client;

public class Client(
    string name,
    string surname,
    City.City city)
    : IClient
{
    private ClientState _state = ClientState.CreatedOrder;

    public string Name { get; } = name;
    public string Surname { get; } = surname;
    public City.City City { get; } = city;
    public ICargo? Order { get; set; }

    public void GetOrder()
    {
        _state = ClientState.ReceivedOrder;
        Order = null;
    }
}