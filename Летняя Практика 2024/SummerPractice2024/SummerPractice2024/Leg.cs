using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SummerPractice2024
{
    public class Leg : Detail
    {
        const int width = 20;
        const int height = 80;
        public Leg(Point location, Color color) : base(location, color)
        {
        }
        public override void Draw(Graphics graphics)
        {
            using var brush = new SolidBrush(Color);
            graphics.FillRectangle(brush, FirstPoint.X, FirstPoint.Y, width, height);
            graphics.FillRectangle(brush, FirstPoint.X + width, FirstPoint.Y + 60, width, 20);
        }

        public override Rectangle GetBoundingRectangle()
        {
            return new Rectangle(FirstPoint, new Size(2 * width, height));
        }

        public override int Toughness => 50;
        public override int Speed => 200;
        public override int Damage => 30;
        public override int Price => 200;
    }
}
