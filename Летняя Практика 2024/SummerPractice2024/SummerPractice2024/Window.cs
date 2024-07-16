using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SummerPractice2024
{
    public class Window : ScalableDetail
    {
        public Window(Point location, Color color) : base(location, color)
        {
        }
        public override void Draw(Graphics graphics)
        {
            var width = SecondPoint.X - FirstPoint.X;
            var height = SecondPoint.Y - FirstPoint.Y;
            using (var brush = new SolidBrush(Color))
                graphics.FillRectangle(brush, FirstPoint.X, FirstPoint.Y, width, height);
            graphics.DrawRectangle(Pens.Black, FirstPoint.X, FirstPoint.Y, width, height);
            using var pen = new Pen(Color.Black, 2);
            graphics.DrawLine(pen, new Point(FirstPoint.X + width / 2, FirstPoint.Y), new Point(FirstPoint.X + width / 2, FirstPoint.Y + height));
            graphics.DrawLine(pen, new Point(FirstPoint.X, FirstPoint.Y + height / 2), new Point(FirstPoint.X + width, FirstPoint.Y + height / 2));
        }
        public override int Toughness 
        { 
            get
            {
                var width = SecondPoint.X - FirstPoint.X;
                var height = SecondPoint.Y - FirstPoint.Y;
                return 0 - (width * height) / 16;
            }
        }
        public override int Speed 
        {
            get
            {
                var width = SecondPoint.X - FirstPoint.X;
                var height = SecondPoint.Y - FirstPoint.Y;
                return 0 - (width * height) / 64;
            }
        }
        public override int Damage { get => 0; }
        public override int Price 
        {
            get
            {
                var width = SecondPoint.X - FirstPoint.X;
                var height = SecondPoint.Y - FirstPoint.Y;
                return 0 + (width * height) / 10;
            }
        }
    }
}
