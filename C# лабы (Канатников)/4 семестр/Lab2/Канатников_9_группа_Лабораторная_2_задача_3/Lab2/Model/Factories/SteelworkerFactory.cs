using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2Construction.Model.Factories
{
    public class SteelworkerFactory : StaffFactory
    {
        public SteelworkerFactory(int x, int y, int id) : base(x, y, id)
        {
        }

        public SteelworkerFactory(Point location, int id) : base(location, id) { }

        public override Staff CreateStaff()
        {
            var steelworker = new Steelworker(location, id);
            return steelworker;
        }
    }
}
