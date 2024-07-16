using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SummerPractice2024
{
    public class Block : ScalableDetail
    {
        
        public Block(Point location, Color color) : base(location, color) 
        {
        }


        public override void Draw(Graphics graphics)
        {
            var width = SecondPoint.X - FirstPoint.X;
            var height = SecondPoint.Y - FirstPoint.Y;
            using var brush = new SolidBrush(Color);
            graphics.FillRectangle(brush, FirstPoint.X, FirstPoint.Y, width, height);     
        }

        public override int Toughness
        {
            get
            {
                var width = SecondPoint.X - FirstPoint.X;
                var height = SecondPoint.Y - FirstPoint.Y;
                return 0 + (width * height) / 8;
            }
        }
        public override int Speed
        {
            get
            {
                var width = SecondPoint.X - FirstPoint.X;
                var height = SecondPoint.Y - FirstPoint.Y;
                return 0 - (width * height) / 62;
            }
        }
        public override int Damage 
        {
            get
            {
                var width = SecondPoint.X - FirstPoint.X;
                var height = SecondPoint.Y - FirstPoint.Y;
                return 0 + (width * height) / 100;
            }
        }
        public override int Price
        {
            get
            {
                var width = SecondPoint.X - FirstPoint.X;
                var height = SecondPoint.Y - FirstPoint.Y;
                return 0 + (width * height) / 20;
            }
        }
    }
}
