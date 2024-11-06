using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2Construction.Model.Factories
{
    public class BrickHouseFactory : ConstructionFactory
    {
        public BrickHouseFactory(int x, int y) : base(x, y)
        {
        }

        public BrickHouseFactory(Point location) : base(location) { }

        public override Construction BuildConstruction()
        {
            var house = new BrickHouse(location);
            return house;
        }
    }
}
