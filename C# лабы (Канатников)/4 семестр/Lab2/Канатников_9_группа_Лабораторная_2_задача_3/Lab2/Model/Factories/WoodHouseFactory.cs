using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2Construction.Model.Factories
{
    public class WoodHouseFactory : ConstructionFactory
    {
        public WoodHouseFactory(int x, int y) : base(x, y)
        {
        }

        public WoodHouseFactory(Point point) : base(point) { }

        public override Construction BuildConstruction()
        {
            var house = new WoodHouse(location);
            return house;
        }
    }
}
