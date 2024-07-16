using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SummerPractice2024
{
    public abstract class Detail
    {
        // координаты верхнего левого угла
        public Point FirstPoint { get; set; }
        public Detail(Point location, Color color)
        {
            FirstPoint = location;
            Color = color;
        }
        public Color Color { get; set; }
        public abstract void Draw (Graphics graphics);
        public abstract int Toughness { get; }
        public abstract int Speed { get; }
        public abstract int Damage { get; }
        public abstract int Price { get; }
        protected static Rectangle FindBoundingRectangle(IEnumerable<Point> points)
        {
            int minX = points.Min(p => p.X);
            int maxX = points.Max(p => p.X);
            int minY = points.Min(p => p.Y);
            int maxY = points.Max(p => p.Y);

            return new Rectangle(minX, minY, maxX - minX, maxY - minY);
        }
        public abstract Rectangle GetBoundingRectangle(); 
        public bool IntersectWith(Detail other) => GetBoundingRectangle().IntersectsWith(other.GetBoundingRectangle());
    }
}
