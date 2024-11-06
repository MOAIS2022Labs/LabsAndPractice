using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2Construction.Model
{
    public class Driver : Staff
    {
        // груз, который везёт водитель
        public override MaterialType WorkWith => workWith;

        public Driver(int x, int y, MaterialType workWith, int id) : base(x, y, id)
        {
            this.workWith = workWith;
        }

        public Driver(Point point, MaterialType workWith, int id) : base(point, id) 
        {
            this.workWith = workWith;
        }

        public override string ToString()
        {
            return $"{WorkWith.ToString()}Track";
        }
    }
}
