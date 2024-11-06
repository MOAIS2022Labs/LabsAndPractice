using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2Construction.Model
{
    public abstract class Construction
    {
        public Point Location { get; set; } // местонахождение постройки на форме
        public Construction(int x, int y) 
        { 
            Location = new Point(x, y);
        }
        public Construction(Point location)
        {
            Location = location;
        }
        public abstract MaterialType MaterialType { get; } // материал, из которого состроит данное здание
    }
}
