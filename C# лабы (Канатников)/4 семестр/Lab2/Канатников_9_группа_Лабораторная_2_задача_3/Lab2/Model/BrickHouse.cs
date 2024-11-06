using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2Construction.Model
{
    public class BrickHouse : Construction
    {
        public override MaterialType MaterialType => MaterialType.Brick;

        public BrickHouse(int x, int y) : base(x, y)
        {
        }
        public BrickHouse(Point point) : base(point)
        {
        }

        public override string ToString()
        {
            return $"BrickHouse";
        }
    }
}
