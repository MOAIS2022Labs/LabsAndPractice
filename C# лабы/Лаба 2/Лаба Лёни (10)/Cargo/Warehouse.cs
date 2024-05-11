using TransportationLab2.Cargo.Factory;
using TransportationLab2.Cargo.Unit;

namespace TransportationLab2.Cargo;

public class Warehouse
{
    public List<ICargo> Items { get; set; }

    public void FillWarehouse()
    {
        int range = new Random().Next(0, 3);
        for (int i = 0; i < range; ++i)
            Items.Add(new DangerousFactory("Опасный", new Random().Next(100, 500), Items.Count).CreateCargo());
        range = new Random().Next(0, 2);
        for (int i = 0; i < range; ++i)
            Items.Add(new FragileFactory("Хрупкий", new Random().Next(200, 600), Items.Count).CreateCargo());
        range = new Random().Next(0, 3);
        for (int i = 0; i < range; ++i)
            Items.Add(new LiquidFactory("Жидкий", new Random().Next(400, 900), Items.Count).CreateCargo());
        range = new Random().Next(0, 2);
        for (int i = 0; i < range; ++i)
            Items.Add(new PerishableFactory("Скоропортящийся", new Random().Next(300, 900), Items.Count).CreateCargo());
    }

    public Warehouse()
    {
        FillWarehouse();
    }
}