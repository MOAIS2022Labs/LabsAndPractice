using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2Construction.Model
{
    public abstract class Staff
    {
        public Point Location { get; set; } // место, где находится работник на форме
        protected MaterialType workWith; // тип материалов, с которым работает данный строитель
        public abstract MaterialType WorkWith { get; }
        public int Id {  get; private set; } // Идентификатор рабочего

        public Staff(int x, int y, int id)
        {
            Location = new Point(x, y);
            Id = id;
        }

        public Staff(Point location, int id)
        {
            Location = location;
            Id = id;
        }
    }
}
