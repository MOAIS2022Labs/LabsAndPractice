using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.ComponentModel;
using System;
using System.IO;

namespace OS_Lab2.Service
{
    using FILETIME = System.Runtime.InteropServices.ComTypes.FILETIME;

    public class FileService
    {
        string _path = string.Empty;
        public FileService(string path)
        {
            _path = path;
        }

        public WIN32_FIND_DATA? FindFirstDatedFile()
        {
            WIN32_FIND_DATA? result = null;
            foreach (var fileData in GetFiles(_path)) 
            {
                if (result != null && CompareFileCreationDate(fileData, (WIN32_FIND_DATA)result) <= 0)
                    result = fileData;

                if (result == null)
                    result = fileData;
            }
            return result;
        }

        public void SwitchCatalog(string Path)
        {
            _path = Path;
        }

        private IEnumerable<WIN32_FIND_DATA> GetFiles(string path)
        {
            WIN32_FIND_DATA data;
            IntPtr findHandle = FindFirstFile(Path.Combine(path, "*"), out data);
            if (findHandle == INVALID_HANDLE_VALUE)
                throw new Win32Exception(Marshal.GetLastWin32Error());
            try
            {
                do
                {
                    if ((data.dwFileAttributes & FileAttributes.Directory) != 0
                        && data.cFileName != "." && data.cFileName != "..")
                    {
                        foreach (var fileData in GetFiles(Path.Combine(path, data.cFileName)))
                            yield return fileData;
                    }

                    if ((data.dwFileAttributes & FileAttributes.Directory) == 0)
                        yield return data;
                }
                while (FindNextFile(findHandle, out data));
            }
            finally
            {
                FindClose(findHandle);
            }
        }

        public static int CompareFileCreationDate(WIN32_FIND_DATA dataLeft, WIN32_FIND_DATA dataRight)
        {
            long valueLeft = (((long)dataLeft.ftCreationTime.dwHighDateTime << 32)
                                    | dataLeft.ftCreationTime.dwLowDateTime);
            long valueRight = (((long)dataRight.ftCreationTime.dwHighDateTime << 32)
                                    | dataRight.ftCreationTime.dwLowDateTime);
            return valueLeft.CompareTo(valueRight);
        }

        #region

        private const int MAX_PATH = 260;
        [Serializable]
        [BestFitMapping(false)]
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
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
