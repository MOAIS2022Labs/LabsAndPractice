namespace TransportationLab2.Cargo.Unit;

public interface ICargo
{
    int Id { get; }
    CargoType Type { get; } // тип груза
    string Name { get; } // наименование
    int Cost { get; } // цена за доставк
}