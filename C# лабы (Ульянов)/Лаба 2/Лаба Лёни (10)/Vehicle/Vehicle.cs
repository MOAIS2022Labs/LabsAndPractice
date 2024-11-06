using TransportationLab2.Cargo.Unit;
using TransportationLab2.Client;
using Timer = System.Windows.Forms.Timer;

namespace TransportationLab2.Vehicle;

public class Vehicle(
    string carBrand,
    int id)
    : IVehicle
{
    private event Action? _notifyClient; // Event, на который подписывается клиент.

    // При срабатывании данного события клиент получит заказ, а после чего
    // отпишется от уведомлений по заказу.
    private Thread? _thread; // Поток, который реализует доставку с помощью нескольких грузовиков
    private object _lock = new object();
    private Timer _timer = new Timer();

    private bool _waitForOrder = true;
    public Queue<IClient>? Clients { get; set; }
    public string CarBrand { get; } = carBrand;
    public int Id { get; } = id;
    public City.City TargetCity { get; set; }
    public KeyValuePair<ICargo, IClient> order { get; set; }

    private event Action NotifyClient
    {
        add { _notifyClient += value; }
        remove { _notifyClient -= value; }
    }

    private void DriveToClient()
    {
    }

    private void CheckForOrders(List<IClient> clientsOrderList)
    {
        if (_waitForOrder)
            return;
        try
        {
            _timer.Stop();
            if (clientsOrderList.Count != 0)
                GetRandomOrder(clientsOrderList);
        }
        finally
        {
            _timer.Start();
        }
    }

    private void VehicleLogic()
    {
        /*// Установка стартовых координат
        SetStartCoord();

        // Отображение
        Draw();*/
        Thread.Sleep(20);
    }

    public void GetRandomOrder(List<IClient> clientsOrderList)
    {
        var index = new Random().Next(0, clientsOrderList.Count);
        Clients?.Enqueue(clientsOrderList[index]);
        clientsOrderList.RemoveAt(index);
    }

    public void Start()
    {
        _thread = new Thread(VehicleLogic);
        _thread.Start();
    }

    public void AddOrder(IClient client)
    {
        lock (_lock)
        {
            Clients?.Enqueue(client);
            NotifyClient += client.GetOrder;
        }
    }

    public void Deliver()
    {
        _notifyClient?.Invoke();
    }

    public void CompleteOrder()
    {
        lock (_lock)
        {
            var client = Clients?.Dequeue();
            if (client != null)
                NotifyClient -= client.GetOrder;
        }
    }
}