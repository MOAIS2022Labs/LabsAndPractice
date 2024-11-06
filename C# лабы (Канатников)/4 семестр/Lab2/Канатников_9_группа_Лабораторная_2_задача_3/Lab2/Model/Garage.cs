using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2Construction.Model
{
    public class Garage : Construction
    {
        public override MaterialType MaterialType => MaterialType.Steel;

        public Garage(int x, int y) : base(x, y)
        {
        }

        public Garage(Point point) : base(point) { }

        public override string ToString()
        {
            return "Garage";
        }
    }
}
