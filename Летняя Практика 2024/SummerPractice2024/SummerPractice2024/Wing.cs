using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SummerPractice2024
{
    public class Wing : Detail
    {
        private Point[] spoiler;
        public Wing(Point location, Color color) : base(location, color)
        {
            spoiler = [
            FirstPoint,
            new Point(FirstPoint.X, FirstPoint.Y - 5),
            new Point(FirstPoint.X - 30, FirstPoint.Y + 10),
            new Point(FirstPoint.X + 5, FirstPoint.Y - 60),
            ];
        }
        public override void Draw(Graphics graphics)
        {
            using var brush = new SolidBrush(Color);
            
            graphics.FillPolygon(brush, spoiler);
            graphics.DrawPolygon(Pens.Black, spoiler);
            graphics.FillRectangle(brush, FirstPoint.X - 28, FirstPoint.Y + 8, 3, 15);
            graphics.DrawRectangle(Pens.Black, FirstPoint.X - 28, FirstPoint.Y + 8, 3, 15);
            graphics.FillRectangle(brush, FirstPoint.X - 2, FirstPoint.Y - 4, 3, 27);
            graphics.DrawRectangle(Pens.Black, FirstPoint.X - 2, FirstPoint.Y - 4, 3, 27);

        }

        public override Rectangle GetBoundingRectangle()
        {
            var points = new List<Point>(spoiler);
            points.Add(new(FirstPoint.X - 28, FirstPoint.Y + 8));
            points.Add(new(FirstPoint.X - 2 + 3, FirstPoint.Y - 4 + 27));
            return FindBoundingRectangle(points);
        }

        public override int Toughness => 100;
        public override int Speed => 50;
        public override int Damage => 10;
        public override int Price => 150;
    }
}
