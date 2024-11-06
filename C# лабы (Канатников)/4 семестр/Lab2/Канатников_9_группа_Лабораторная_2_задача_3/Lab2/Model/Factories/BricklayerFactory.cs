using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2Construction.Model.Factories
{
    public class BricklayerFactory : StaffFactory
    {
        public BricklayerFactory(int x, int y, int id) : base(x, y, id)
        {
        }

        public BricklayerFactory(Point location, int id) : base(location, id) { }

        public override Staff CreateStaff()
        {
            var bricklayer = new Bricklayer(location, id);
            return bricklayer;
        }
    }
}
