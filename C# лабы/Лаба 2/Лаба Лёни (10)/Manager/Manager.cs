using TransportationLab2.Cargo;
using TransportationLab2.Client;
using TransportationLab2.Vehicle;

namespace TransportationLab2.Manager;

public class Manager
{
    private List<IClient> _clients = new();
    private List<IVehicle> _vehicles = new();
    private Dictionary<City.City, int>? _roads;
    private Warehouse _warehouse;
    private List<Thread>? _threads;
    private Thread? _mainThread;
    private object _lock = new();
    private object _moveLock = new();

    private void CreateRoads()
    {
        _roads = new Dictionary<City.City, int>
        {
            [City.City.Vlg] = 968,
            [City.City.Spb] = 635,
            [City.City.Kzn] = 819,
            [City.City.Smr] = 1065
        };
    }

    private void CreateClients()
    {
        Client.Client client = new("Иванов", "Иван", City.City.Kzn);
        _clients.Add(client);
        client = new("Андреев", "Андрей", City.City.Spb);
        _clients.Add(client);
        client = new("Фролова", "Ольга", City.City.Smr);
        _clients.Add(client);
        client = new("Александрова", "Александра", City.City.Vlg);
        _clients.Add(client);
    }

    public Manager()
    {
        CreateRoads();
        CreateClients();
        _warehouse = new();
        _threads = new();
        //_mainThread = new(/*задача*/);
    }

    public void CreateVehicle()
    {
        if (_vehicles.Count == 4)
            throw new ManagerException("Truck limit succeeded (4 vehicles)");
        string[] brands = { "Toyota", "Volvo", "Renault", "MAN" };
        int brandId = new Random().Next(0, brands.Length);
        Vehicle.Vehicle truck = new(brands[brandId], _vehicles.Count + 1);
        _vehicles.Add(truck);
    }

    public void RestockWarehouse()
    {
        _warehouse.FillWarehouse();
    }

    public void AssignOrder()
    {
        lock (_lock)
        {
            if (_warehouse.Items.Count == 0)
                throw new ManagerException("Warehouse is empty and needs restock");
            int itemChoice = new Random().Next(0, _warehouse.Items.Count);
            int clientChoice = new Random().Next(0, _clients.Count);
            _clients[clientChoice].Order = _warehouse.Items[itemChoice];
            int truckChoice = new Random().Next(0, _vehicles.Count);
            _vehicles[truckChoice].Clients?.Enqueue(_clients[clientChoice]);
            _vehicles[truckChoice].TargetCity = _clients[clientChoice].City;
        }
    }
}