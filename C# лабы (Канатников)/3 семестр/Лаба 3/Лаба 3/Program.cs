using System;


namespace Lab3
{
    
    public class Point
    {
        public double x { get; set; }
        public double y { get; set; }
        public Point(double x, double y)
        {
            this.x = x;
            this.y = y;
        }
        public override string ToString()
        {
            return ($"({x}, {y})");
        }
    }

    public class Straight
    {
        public double a { get; set; }
        public double b { get; set; }
        public double c { get; set; } 
        public Straight(double a, double b, double c)
        {
            this.a = a;
            this.b = b;
            this.c = c;
        }

        public bool IsParallel(Straight straight) // если определитель равен нулю, то прямые параллельны
        {
            return Math.Abs(this.a * straight.b - this.b * straight.a) < double.Epsilon; 
        }
        public Point Intersection(Straight straight) // по методу крамера
        {
            double det = this.a * straight.b - this.b * straight.a;
            double det_x = this.c * straight.b - this.b * straight.c;
            double det_y = this.a * straight.c - this.c * straight.a;
            return new Point(det_x / det, det_y / det);
        }
        public bool Contains(Point point)
        {
            return this.a * point.x + this.b * point.y == this.c;
        }
        public override string ToString()
        {
            return ($"({a}, {b}, {c})");
        }
    }
    

    public class Program
    {
        static void Main(string[] args)
        {
            int n;
            ReadAndCheck(out n, "Введите количество прямых n: ", 1);
            Straight[] straights = CreateArray(n);
            if (!Task(straights))
                Console.WriteLine("Среди прямых отсутствуют 3 прямые, пересекающиеся в одной точке");
        }



        public static void ReadAndCheck(out int input, string message, int left = int.MinValue)
        {
            Console.Write(message);
            while (!int.TryParse(Console.ReadLine(), out input) || input < left)
            {
                Console.WriteLine("\nДанные не корректны, повторите ввод!\n");
                Console.Write(message);
            }
        }
        public static void ReadAndCheck(out double input, string message)
        {
            Console.Write(message);
            while (!double.TryParse(Console.ReadLine(), out input))
            {
                Console.WriteLine("\nДанные не корректны, повторите ввод!\n");
                Console.Write(message);
            }
        }

        public static void ReadCoefficients(out double a, out double b, out double c)
        {
            Console.WriteLine("Введите коэффициенты прямой, они не могут быть одновременно нулевыми");
            ReadAndCheck(out a, "Введите координату a: ");
            ReadAndCheck(out b, "Введите координату b: ");
            ReadAndCheck(out c, "Введите координату c: ");
            while (a == 0 && b == 0 && c == 0)
            {
                Console.WriteLine("Координаты не могут быть одновременно нулевыми, повторите ввод");
                ReadAndCheck(out a, "Введите координату a: ");
                ReadAndCheck(out b, "Введите координату b: ");
                ReadAndCheck(out c, "Введите координату c: ");
            }
        }

        public static Straight[] CreateArray(int n)
        {
            Straight[] straights = new Straight[n];
            for (int i = 0; i < n; ++i)
            {
                double a, b, c;
                ReadCoefficients(out a, out b, out c);
                straights[i] = new Straight(a, b, c);
            }
            return straights;
        }

        public static void PrintArray(Straight[] straights)
        {
            for (var i = 0; i < straights.Length; i++)
                Console.WriteLine(straights[i]);
        }

        public static bool Task(Straight[] straights)
        {
            bool result = false;
            int n = straights.Length;
            int i = 0;
            while (i < n - 1 && !result)
            {
                int j = i + 1;
                while (j < n && !result)
                {
                    if (!straights[i].IsParallel(straights[j]))
                    {
                        Point intersection = straights[i].Intersection(straights[j]);
                        int k = 0;
                        while (k != i && k != j && k < n && !result)
                        {
                            if (straights[k].Contains(intersection))
                            {
                                result = true;
                                Console.WriteLine($"Прямые {straights[i]}, {straights[j]}, {straights[k]} пересекаются в точке {intersection}");
                            }
                            ++k;
                        }
                    }
                    ++j;
                }
                ++i;
            }
            return result;
        }
    }
}
