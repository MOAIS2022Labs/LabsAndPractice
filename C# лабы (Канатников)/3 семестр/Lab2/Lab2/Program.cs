using System;

namespace Lab2
{
    class Program
    {

        static void Main(string[] args)
        {

            double x0, xn, h, eps;
            //ReadInterval(out x0, out xn);
            //ReadAndCheck(out h, "Введите значения шага: ");
            //ReadAndCheck(out eps, "Введите значение точности вычислений: ");
            //Function(h, eps, x0, xn);
            string s = null;
            Console.WriteLine(s.Length);
        }

        public static void PrintToString(double i, double sum, double exp, ref int x, ref int y)
        {
            if (x == 0 || x >= 93)
            {
                x = 0;
                y += 9;            
                Console.SetCursorPosition(x, y);
                Console.WriteLine("Значение х:           " + $"{i, 8:f4}\n");
                Console.WriteLine("Значение вычисленное: " + $"{sum, 8:f4}\n");
                Console.WriteLine("Значение по формуле:  "+ $"{exp, 8:f4}\n");
                x += 37;
            }
            else
            {
                x += 12;
                Console.SetCursorPosition(x, y);
                Console.Write($" {i, 8:f4}");
                Console.SetCursorPosition(x, y + 2);
                Console.WriteLine($" {sum, 8:f4}");
                Console.SetCursorPosition(x, y + 4);
                Console.WriteLine($" {exp, 8:f4}");
                x += 17;
            }
        }

        public static double SumSeries(double x, double eps)
        {
            double sum = 1, term = 1;
            int n = 1;
            while (Math.Abs(term) > eps)
            {
                term *= (-1 * x * x) / n;
                ++n;
                sum += term;
            }
            return sum;
        }

        public static void Function(double h, double eps, double x0, double xn)
        {
            double sum, exp;
            int x = 0, y = 0;
            double i = x0;
            while (Math.Abs(i - xn) > eps && i < xn)
            {
                sum = SumSeries(i, eps);
                exp = Math.Exp(-1 * i * i);
                PrintToString(i, sum, exp, ref x, ref y);
                i += h;
            }
            sum = SumSeries(xn, eps);
            exp = Math.Exp(-1 * xn * xn);
            PrintToString(xn, sum, exp, ref x, ref y);
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

        public static void ReadInterval(out double x0, out double xn)
        {
            ReadAndCheck(out x0, "Введите левую границу интервала: ");
            ReadAndCheck(out xn, "Введите правую границу интервала: ");
            while (xn <= x0)
            {
                Console.WriteLine("\nОшибка ввода, правая граница должна быть больше левой!\n");
                ReadAndCheck(out x0, "Введите левую границу интервала: ");
                ReadAndCheck(out xn, "Введите правую границу интервала: ");
            }
        }
    }
}