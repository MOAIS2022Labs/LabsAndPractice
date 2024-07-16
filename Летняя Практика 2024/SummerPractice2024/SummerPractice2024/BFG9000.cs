using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SummerPractice2024
{
    public class BFG9000 : Detail
    {
        private const int width = 81;
        private const int height = 25;
        public BFG9000(Point location, Color color) : base(location, color)
        {
        }
        public override void Draw(Graphics graphics)
        {
            using var brush = new SolidBrush(Color);

            graphics.FillRectangle(brush, FirstPoint.X, FirstPoint.Y, width - 6, height);
            graphics.DrawRectangle(Pens.Black, FirstPoint.X, FirstPoint.Y, width - 6, height);

            graphics.FillRectangle(Brushes.PaleGreen, FirstPoint.X + 12, FirstPoint.Y + 6, 12, 6);
            graphics.FillRectangle(Brushes.PaleGreen, FirstPoint.X + 51, FirstPoint.Y + 6, 12, 6);
            graphics.FillEllipse(Brushes.PaleGreen, FirstPoint.X + 31, FirstPoint.Y + 6, 12, 12); 

            graphics.FillRectangle(brush, FirstPoint.X + width - 6, FirstPoint.Y + 6, 6, 6);
            graphics.DrawRectangle(Pens.Black, FirstPoint.X + width - 6, FirstPoint.Y + 6, 6, 6);
            
        }

        public override Rectangle GetBoundingRectangle()
        {
            return new Rectangle(FirstPoint, new Size(width, height));
        }

        public override int Toughness => 100;
        public override int Speed => -70;
        public override int Damage => 1000;
        public override int Price => 500;
    }
}
