using System;


namespace Lab4
{
    internal class Program
    {

        static void Main(string[] args)
        {
            int n;
            ReadAndCheck(out n, "Введите размер массива n: ", 0);
            int[,] matrix = new int[n, n];
            FillRandom(matrix);
            if (n != 0)
            {
                Console.WriteLine("\nИсходная матрица");
                PrintMatrix(matrix);
                Console.WriteLine("\nМассивы-результаты");
                for (int i = 0; i < n; ++i)
                {
                    Console.Write($"\nМассив {i + 1}\t");
                    PrintArray(ValuesBetween(n, i, ref matrix, out int new_size), new_size);
                }
            }
            else
                Console.WriteLine("\nМатрица пустая!");          
        }


        public static int[] ValuesBetween(int n, int row, ref int[,] matrix, out int n_res)
        {
            int[] result = new int[n];
            n_res = 0;
            int min_pos = 0, max_pos = 0;
            for (int i = 1; i < n; ++i)
            {
                if (matrix[row, i] < matrix[row, min_pos])
                    min_pos = i;
                if (matrix[row, i] >= matrix[row, max_pos])
                    max_pos = i;   
            }
            if (min_pos < max_pos)
                for (int i = min_pos + 1; i < max_pos; ++i)
                    result[n_res++] = matrix[row, i];
            return result;
        }

        public static void PrintMatrix(int[,] matrix)
        {
            for (int i = 0; i < matrix.GetLength(0); ++i)
            {
                for (int j = 0; j < matrix.GetLength(1); ++j)
                    Console.Write(matrix[i, j] + "\t");
                Console.WriteLine();
            }
        }

        public static void PrintArray(int[] arr, int len)
        {
            if (len > 0)
            {
                Console.WriteLine();
                for (int i = 0; i < len; ++i)
                    Console.Write(arr[i] + "\t");
                Console.WriteLine();
            }
            else
                Console.WriteLine("\nМассив пустой!");
        }       
        public static void FillRandom(int[,] matrix)
        {
            Random rnd = new Random();
            for (int i = 0; i < matrix.GetLength(0); ++i)
                for (int j = 0; j < matrix.GetLength(1); ++j)
                    matrix[i, j] = rnd.Next(100);
        }
        
        public static void ReadAndCheck(out int input, string message, int min = int.MinValue, int max = int.MaxValue)
        {
            Console.Write(message);
            while (!int.TryParse(Console.ReadLine(), out input) || input < min || input > max)
            {
                Console.WriteLine("\nДанные не корректны, повторите ввод!\n");
                Console.Write(message);
            }
        }
    }
}
