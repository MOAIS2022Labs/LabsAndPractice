using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2Construction.Model.Factories
{
    public class GarageFactory : ConstructionFactory
    {
        public GarageFactory(int x, int y) : base(x, y)
        {
        }

        public GarageFactory(Point point) : base(point) { }

        public override Construction BuildConstruction()
        {
            var garage = new Garage(location);
            return garage;
        }
    }
}
