using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SummerPractice2024
{
    public class Flashlight : Detail
    {
        private const int diameterBig = 48;
        private const int diameterSmall = 12;
        public Flashlight(Point location, Color color) : base(location, color) 
        {
        }
        public override void Draw(Graphics graphics)
        {
            using var brush = new SolidBrush(Color);
            graphics.FillEllipse(brush, FirstPoint.X - diameterBig / 4, FirstPoint.Y - diameterBig / 4, diameterBig, diameterBig);
            using var pen = new Pen(Color.Black, 2);
            graphics.DrawEllipse(pen, FirstPoint.X - diameterBig / 4, FirstPoint.Y - diameterBig / 4, diameterBig, diameterBig);
            graphics.FillEllipse(Brushes.Yellow, FirstPoint.X - diameterSmall / 4, FirstPoint.Y, diameterSmall, diameterSmall);
            graphics.FillEllipse(Brushes.Yellow, FirstPoint.X + (4 * diameterSmall) / 3, FirstPoint.Y, diameterSmall, diameterSmall);
        }

        public override Rectangle GetBoundingRectangle()
        {
            return new Rectangle(FirstPoint, new Size(diameterBig, diameterBig));
        }
        public override int Toughness => -20;
        public override int Speed => 0;
        public override int Damage => 0;
        public override int Price => 50;

    }
}
