using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace OS_Lab2
{
    public class FileService
    {
        //единственная рекурсивная функция для прохода по всем файлам директории path и вычисления количества бла бла по задаче
        public int GetArchiveFilesCount(string path)
        {
            //итоговое количество для текущей директории
            int result = 0;

            //создаем сущность, в которой будут храниться данные о файле или о директории (зависит от того, что далее находит функция)
            WIN32_FIND_DATA data;
            //функция, находящая первый файл или директорию по указанному пути (* для того, чтобы просмотрела все файлы и директории)
            //data передается через out, значит после выполнения будет заполнена (если не ошибка хд)
            IntPtr findHandle = FindFirstFile(Path.Combine(path, "*"), out data);
            //ловим ошибку отправляем в форму
            if (findHandle == INVALID_HANDLE_VALUE)
                throw new Win32Exception(Marshal.GetLastWin32Error());
            try
            {
                //начинаем цикл прохода по файлам
                do
                {
                    //если data - директория с названием не "."(текущая директория) и не ".."(родительская директория)
                    if ((data.dwFileAttributes & FileAttributes.Directory) != 0
                        && data.cFileName != "." && data.cFileName != "..")
                    {
                        //вызываем рекурсию и добавляем в текущий результат
                        result += GetArchiveFilesCount(Path.Combine(path, data.cFileName));
                    }

                    //если файл с атрибутом Archive - увеличиваем result на 1
                    if ((data.dwFileAttributes & FileAttributes.Archive) != 0)
                        result++;
                }
                //ищем следующий файл или директорию
                while (FindNextFile(findHandle, out data));
            }
            finally
            {
                //не забываем освободить за собой память
                FindClose(findHandle);
            }
            return result;
        }

        #region

        //константа для максимальной длинны пути к файлу
        private const int MAX_PATH = 260;
        [Serializable]
        [BestFitMapping(false)]
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        //сама сущность WIN32_FIND_DATA
        public struct WIN32_FIND_DATA
        {
            public FileAttributes dwFileAttributes;
            public FILETIME ftCreationTime;
            public FILETIME ftLastAccessTime;
            public FILETIME ftLastWriteTime;
            public int nFileSizeHigh;
            public int nFileSizelow;
            public int dwReserved0;
            public int dwReserved1;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = MAX_PATH)]
            public string cFileName;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 14)]
            public string cAlternate;
        }

        //исмпорт необходимых функций из kernel32
        [DllImport("kernel32", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern IntPtr FindFirstFile(string lpFileName, out WIN32_FIND_DATA lpFindFileData);

        [DllImport("kernel32", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern bool FindNextFile(IntPtr hFindFile, out WIN32_FIND_DATA lpFindFileData);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern bool FindClose(IntPtr hFindFile);

        private static readonly IntPtr INVALID_HANDLE_VALUE = new IntPtr(-1);

        #endregion
    }
}
