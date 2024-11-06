using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2Construction.Model
{
    public class Woodworker : Staff
    {
        public Woodworker(int x, int y, int id) : base(x, y, id)
        {
        }

        public Woodworker(Point point, int id) : base(point, id) { }
        public override MaterialType WorkWith => MaterialType.Wood;
    }
}
