using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SummerPractice2024
{
    public class Bumper : Detail
    {
        private const int radius = 40;
        private const int width = 150;
        private const int height = 26;
        public Bumper(Point location, Color color) : base(location, color) 
        {
        }
        public override void Draw(Graphics graphics)
        {
            using var brush = new SolidBrush(Color);
            using Pen pen = new Pen(Color.Black, 2);
            
            graphics.FillRectangle(brush, FirstPoint.X, FirstPoint.Y, width, height);
            graphics.DrawRectangle(pen, FirstPoint.X, FirstPoint.Y, width, height);

            graphics.DrawLine(pen, FirstPoint.X, FirstPoint.Y + height / 2, FirstPoint.X + width, FirstPoint.Y + height / 2); 
            graphics.FillEllipse(Brushes.Black, FirstPoint.X + height / 2, FirstPoint.Y + 5, height / 2, height / 2); 
            graphics.FillEllipse(Brushes.Black, FirstPoint.X + 125, FirstPoint.Y + 5, height / 2, height / 2);
            
        }

        public override Rectangle GetBoundingRectangle()
        {
            return new Rectangle(FirstPoint, new Size(width, height));
        }
        public override int Toughness => 300;
        public override int Speed => -30;
        public override int Damage => 20;
        public override int Price => 100;

    }
}
