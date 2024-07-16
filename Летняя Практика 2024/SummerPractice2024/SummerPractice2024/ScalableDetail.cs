using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SummerPractice2024
{
    public abstract class ScalableDetail : Detail
    {
        public ScalableDetail(Point location, Color color) : base(location, color)
        {
        }

        // координаты правого нижнего угла
        public Point SecondPoint { get; set; }
        public override Rectangle GetBoundingRectangle()
        {
            return new Rectangle(FirstPoint, new Size(SecondPoint.X - FirstPoint.X, SecondPoint.Y - FirstPoint.Y));
        }       
    }
}
