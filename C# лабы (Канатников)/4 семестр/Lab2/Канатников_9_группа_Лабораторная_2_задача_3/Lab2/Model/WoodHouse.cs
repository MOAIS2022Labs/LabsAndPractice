using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2Construction.Model
{
    public class WoodHouse : Construction
    {
        public override MaterialType MaterialType => MaterialType.Wood;

        public WoodHouse(int x, int y) : base(x, y)
        {
        }

        public WoodHouse(Point point) : base(point) { }


        public override string ToString()
        {
            return $"WoodHouse";
        }
    }
}
