using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SummerPractice2024
{
    public class Rocket : Detail
    {
        private Point[] nosePoints;
        private const int height = 70;
        const int width = 25;
        public Rocket(Point location, Color color) : base(location, color)
        {
            nosePoints = [
            FirstPoint,
            new Point(FirstPoint.X + width / 2, FirstPoint.Y - height / 2),
            new Point(FirstPoint.X + width, FirstPoint.Y)
            ];
        }
        public override void Draw(Graphics graphics)
        {
            var frameHeight = height - 20;
            graphics.FillRectangle(Brushes.White, FirstPoint.X, FirstPoint.Y, width, frameHeight);
            using (var pen = new Pen(Color.Black, 2))
                graphics.DrawRectangle(pen, FirstPoint.X, FirstPoint.Y, width, frameHeight);
            
            using var brush = new SolidBrush(Color);
            graphics.FillPolygon(brush, nosePoints);

            graphics.FillRectangle(brush, FirstPoint.X - 5, FirstPoint.Y + frameHeight, 10, height - frameHeight);
            graphics.FillRectangle(brush, FirstPoint.X + 20, FirstPoint.Y + frameHeight, 10, height - frameHeight);
        }

        public override Rectangle GetBoundingRectangle()
        {
            var points = new List<Point>(nosePoints);
            points.Add(new(FirstPoint.X - 5, FirstPoint.Y + height));
            points.Add(new(FirstPoint.X + 20 + 10, FirstPoint.Y + height));
            return FindBoundingRectangle(points);
        }

        public override int Toughness => 0;
        public override int Speed => -30;
        public override int Damage => 700;
        public override int Price => 650;
    }
}
