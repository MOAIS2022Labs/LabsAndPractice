using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SummerPractice2024
{
    public class Basukha : Detail
    {
        List<Point> body = new();
        Point[] strings;
        public Basukha(Point location, Color color) : base(location, color)
        {
            body = [
            new Point(FirstPoint.X + 25, FirstPoint.Y + 22),
            FirstPoint,
            new Point(FirstPoint.X + 60, FirstPoint.Y + 20),
            new Point(FirstPoint.X + 60, FirstPoint.Y + 27),
            new Point(FirstPoint.X, FirstPoint.Y + 40),
            ];

            strings = [
            new Point(FirstPoint.X + 25, FirstPoint.Y + 20),
            new Point(FirstPoint.X + 155, FirstPoint.Y + 20),
            new Point(FirstPoint.X + 25, FirstPoint.Y + 22),
            new Point(FirstPoint.X + 155, FirstPoint.Y + 22),
            new Point(FirstPoint.X + 25, FirstPoint.Y + 24),
            new Point(FirstPoint.X + 155, FirstPoint.Y + 24),
            new Point(FirstPoint.X + 25, FirstPoint.Y + 26),
            new Point(FirstPoint.X + 155, FirstPoint.Y + 26)
            ];
        }
        public override void Draw(Graphics graphics)
        {
            using var pen = new Pen(Color.Black, 2);
            
            using (var brush = new SolidBrush(Color))
                graphics.FillPolygon(brush, body.ToArray());

            graphics.FillRectangle(Brushes.SandyBrown, FirstPoint.X + 60, FirstPoint.Y + 18, 100, 11);

            graphics.DrawEllipse(pen, FirstPoint.X + 160, FirstPoint.Y + 12, 10, 10);
            graphics.DrawEllipse(pen, FirstPoint.X + 160, FirstPoint.Y + 17, 10, 10);
            graphics.DrawEllipse(pen, FirstPoint.X + 160, FirstPoint.Y + 22, 10, 10);
            graphics.DrawEllipse(pen, FirstPoint.X + 160, FirstPoint.Y + 27, 10, 10);

            using var stringPen = new Pen(Color.Black, 1);

            graphics.DrawLines(stringPen, strings);
            graphics.FillRectangle(Brushes.Black, FirstPoint.X + 22, FirstPoint.Y + 19, 4, 9);
        }

        public override Rectangle GetBoundingRectangle()
        {
            // Дополняем список точек для определения описанного прямоугольника
            var points = new List<Point>(body);
            points.Add(new(FirstPoint.X + 170, FirstPoint.Y + 12 + 10));
            points.Add(new(FirstPoint.X + 170, FirstPoint.Y + 27 + 10));
            return FindBoundingRectangle(points);
        }

        public override int Toughness => 50;
        public override int Speed => -10;
        public override int Damage => 200;
        public override int Price => -150;
    }
}
