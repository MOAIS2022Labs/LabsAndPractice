using TransportationLab2.Client;

namespace TransportationLab2.Vehicle;

public interface IVehicle
{
    string CarBrand { get; }
    int Id { get; }
    City.City TargetCity { get; set; }
    Queue<IClient>? Clients { get; set; }
    void AddOrder(IClient client); // Добавить клиента в список дел
    void Deliver(); // Доставка груза
    void CompleteOrder(); // Удаление обслуженного клиента
}