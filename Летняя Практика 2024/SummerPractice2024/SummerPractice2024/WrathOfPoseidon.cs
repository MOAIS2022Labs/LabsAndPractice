using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SummerPractice2024
{
    public class WrathOfPoseidon : Detail
    {
        const int width = 50;
        const int height = 20;
        public WrathOfPoseidon(Point location, Color color) : base(location, color)
        {
        }
        public override void Draw(Graphics graphics)
        {
            using var brush = new SolidBrush(Color);

            graphics.FillEllipse(brush, FirstPoint.X, FirstPoint.Y, width, height);
            graphics.DrawEllipse(Pens.Black, FirstPoint.X, FirstPoint.Y, width, height);

            graphics.FillEllipse(Brushes.Orange, FirstPoint.X + 5, FirstPoint.Y + 5, 30, 10);
            graphics.FillRectangle(Brushes.Orange, FirstPoint.X + 35, FirstPoint.Y + 8, 15, 4);

            graphics.FillRectangle(brush, FirstPoint.X + 15, FirstPoint.Y + height, 10, 20);
            graphics.DrawRectangle(Pens.Black, FirstPoint.X + 15, FirstPoint.Y + height, 10, 20);
        }

        public override Rectangle GetBoundingRectangle()
        {
            return new Rectangle(FirstPoint, new Size(width, height + 20));
        }

        public override int Toughness => 0;
        public override int Speed => 50;
        public override int Damage => 1110;
        public override int Price => 800;
    }
}
