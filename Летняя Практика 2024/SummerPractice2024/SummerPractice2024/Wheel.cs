using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SummerPractice2024
{
    public class Wheel : Detail
    {
        private const int diameterBig = 40;
        private const int diameterSmall = 30;
        
        public Wheel(Point location, Color color) : base(location, color)
        {
        }
        public override void Draw(Graphics graphics)
        {
            using var brush = new SolidBrush(Color);
            graphics.FillEllipse(Brushes.Black, FirstPoint.X - diameterBig / 4, FirstPoint.Y - diameterBig / 4, diameterBig, diameterBig);
            graphics.FillEllipse(brush, FirstPoint.X - diameterBig / 4 + diameterSmall / 8 + 2, 
                FirstPoint.Y - diameterBig / 4 + diameterSmall / 8 + 2, diameterSmall, diameterSmall);
        }

        public override Rectangle GetBoundingRectangle()
        {
            return new Rectangle(FirstPoint, new Size(diameterBig, diameterBig));
        }

        public override int Toughness => 0;
        public override int Speed => 500;
        public override int Damage => 0;
        public override int Price => 50;
    }
}
