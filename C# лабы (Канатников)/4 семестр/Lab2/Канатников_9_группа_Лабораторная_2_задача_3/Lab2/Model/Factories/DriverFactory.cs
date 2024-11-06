using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2Construction.Model.Factories
{
    public class DriverFactory : StaffFactory
    {
        private MaterialType _cargo; // тип груза, который возит этот водитель
        public DriverFactory(int x, int y, MaterialType cargo, int id) : base(x, y, id)
        {
            _cargo = cargo;
        }

        public DriverFactory(Point location, MaterialType cargo, int id) : base(location, id)
        {
            _cargo = cargo;
        }

        public override Staff CreateStaff()
        {
            var driver = new Driver(location, _cargo, id);
            return driver;
        }
    }
}
