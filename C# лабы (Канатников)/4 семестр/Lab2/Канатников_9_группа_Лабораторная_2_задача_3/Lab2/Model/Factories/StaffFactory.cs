using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2Construction.Model.Factories
{
    // реализация шаблона "Фабрика" для рабочих
    public abstract class StaffFactory
    {
        protected readonly Point location;
        protected readonly MaterialType workWith;
        protected readonly int id;
        public StaffFactory(int x, int y, int id)
        {
            location = new Point(x, y);
            this.id = id;
        }

        public StaffFactory(Point location, int id)
        {
            this.location = location;
            this.id = id;
        }

        public abstract Staff CreateStaff(); // всегда возвращает абстрактного рабочего
    }
}
