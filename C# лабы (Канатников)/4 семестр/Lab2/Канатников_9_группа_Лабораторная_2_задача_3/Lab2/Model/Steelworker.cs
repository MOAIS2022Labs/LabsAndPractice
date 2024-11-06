using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2Construction.Model
{
    public class Steelworker : Staff
    {
        public Steelworker(int x, int y, int id) : base(x, y, id)
        {
        }

        public Steelworker(Point point, int id) : base(point, id) { }

        public override MaterialType WorkWith => MaterialType.Steel;
    }
}
