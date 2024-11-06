using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2Construction.Model.Factories
{
    // реализация шаблона "Фабрика" для построек
    public abstract class ConstructionFactory
    {
        protected readonly Point location;
        public ConstructionFactory(int x, int y)
        {
            this.location = new Point(x, y);
        }
        public ConstructionFactory(Point location)
        {
            this.location = location;
        }
        public abstract Construction BuildConstruction(); // всегда возвращает абстрактную постройку
    }
}
