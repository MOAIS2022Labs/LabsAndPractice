using System.Runtime.InteropServices;
using System.ComponentModel;
using System;
using System.IO;
using System.Collections.Generic;

namespace OS_Lab2.Service
{
    using FILETIME = System.Runtime.InteropServices.ComTypes.FILETIME;

    public class FileService
    {
        public List<string> FindDirsCount(string path) //ищет количество директорий внутри каталога
        {
            List<string> dirs = new List<string>(); //список всех директорий и поддиректорий внутри каталога
            WIN32_FIND_DATA data; //данные о директориях или файлах

            //ищем первый указатель на файлы или директории внутри текущего каталога
            IntPtr findHandle = FindFirstFile(Path.Combine(path, "*"), out data);

            if (findHandle == INVALID_HANDLE_VALUE) //если не нашли - бросок исключения
                throw new Win32Exception(Marshal.GetLastWin32Error());
            try
            {
                do
                {
                    if ((data.dwFileAttributes & FileAttributes.Directory) != 0 //если атрибуты существуют и это директория
                        && data.cFileName != "." && data.cFileName != "..") //при этом не является текущей или родительской директорией
                    {
                        dirs.Add(data.cFileName); //добавляем текущую
                        dirs.AddRange(FindDirsCount(Path.Combine(path, data.cFileName))); //добавляем вложенные из текущей
                    }
                }
                while (FindNextFile(findHandle, out data)); //пока не дошли до конца директории
            }
            finally
            {
                FindClose(findHandle); //хз) чета типа закрыли поиск
            }

            return dirs; //возвращаем полученный список
        }

        #region

        //из методички

        private const int MAX_PATH = 260;
        [Serializable]
        [BestFitMapping(false)]
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        public struct WIN32_FIND_DATA //данные о файлах и директориях
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

        //поиск первого файла или директории в выбранном каталоге
        [DllImport("kernel32", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern IntPtr FindFirstFile(string lpFileName, out WIN32_FIND_DATA lpFindFileData);
        //поиск следующего файла или директории по текущему указателю

        [DllImport("kernel32", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern bool FindNextFile(IntPtr hFindFile, out WIN32_FIND_DATA lpFindFileData);
        //что-то типа закрываем поиск

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern bool FindClose(IntPtr hFindFile);
        //указатель, по которому итерируемся, пока ищем файлы или директории

        private static readonly IntPtr INVALID_HANDLE_VALUE = new IntPtr(-1);

        #endregion

    }
}
