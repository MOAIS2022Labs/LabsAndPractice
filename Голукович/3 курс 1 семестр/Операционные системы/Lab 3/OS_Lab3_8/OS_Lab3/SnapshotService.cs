using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.InteropServices;

namespace OS_Lab3
{
    public static class SnapshotService
    {
        public static Dictionary<PROCESSENTRY32, uint> GetProcessesHeaps(int processEntriesLimit = -1, int heapEntriesLimit = 500)
        {
            var result = new Dictionary<PROCESSENTRY32, uint>();
            IntPtr currentSnapshot = IntPtr.Zero;
            try
            {
                currentSnapshot = CreateToolhelp32Snapshot((UInt32)SnapshotFlags.All, 0);

                var processEntry = new PROCESSENTRY32();
                processEntry.dwSize = (uint)Marshal.SizeOf(typeof(PROCESSENTRY32));

                int processEntryCounter = 0;
                if (Process32First(currentSnapshot, ref processEntry))
                {
                    do
                    {
                        if (processEntriesLimit > -1)
                            processEntryCounter++;

                        var heapList = new HEAPLIST32();
                        heapList.dwSize = (uint)Marshal.SizeOf(typeof(HEAPLIST32));

                        var heapEntry = new HEAPENTRY32();
                        heapEntry.dwSize = (uint)Marshal.SizeOf(typeof(HEAPENTRY32));

                        int heapListEntryCounter = 0;
                        uint emptyBlockSize = 0;
                        if (Heap32ListFirst(currentSnapshot, ref heapList))
                        {
                            do
                            {
                                if (processEntry.th32ProcessID == heapList.th32ProcessID)
                                {
                                    if (Heap32First(ref heapEntry, heapList.th32ProcessID, heapList.th32HeapID))
                                    {
                                        heapListEntryCounter++;
                                        
                                        do
                                        {
                                            if (heapEntry.dwFlags == 1)
                                                emptyBlockSize += heapEntry.dwBlockSize;
                                        }
                                        while (Heap32Next(ref heapEntry));
                                        
                                    }
                                    else
                                    {
                                        throw new Win32Exception($"Heap32First failed with win32 error code {Marshal.GetLastWin32Error()}");
                                    }
                                }
                            }
                            while (Heap32ListNext(currentSnapshot, ref heapList) && heapListEntryCounter < heapEntriesLimit);
                            result.Add(processEntry, emptyBlockSize);
                        }
                        else
                        {
                            throw new Win32Exception($"Heap32ListFirst failed with win32 error code {Marshal.GetLastWin32Error()}");
                        }
                    }
                    while (Process32Next(currentSnapshot, ref processEntry)
                            && (processEntriesLimit == -1 || processEntryCounter < processEntriesLimit));
                }
                else
                {
                    throw new Win32Exception($"Process32First failed with win32 error code {Marshal.GetLastWin32Error()}");
                }
            }
            finally
            {
                CloseHandle(currentSnapshot);
            }
            return result;
        }

        #region kernel32 import

        [Flags]
        private enum SnapshotFlags : uint
        {
            HeapList = 0x00000001,
            Process = 0x00000002,
            Thread = 0x00000004,
            Module = 0x00000008,
            Module32 = 0x00000010,
            Inherit = 0x80000000,
            All = 0x0000001F,
            NoHeaps = 0x40000000
        }

        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern IntPtr CreateToolhelp32Snapshot([In] UInt32 dwFlags, [In] uint th32ProcessID);
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern bool CloseToolhelp32Snapshot([In] IntPtr hSnapshot);
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern bool CloseHandle([In] IntPtr hObject);

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public struct PROCESSENTRY32
        {
            public uint dwSize; // размер записи
            public uint cntUsage; // счетчик ссылок процессa
            public uint th32ProcessID; // идентификационный номер процесса
            public IntPtr th32DefaultHeapID;
            public uint th32ModuleID; // идентифицирует модуль связанный с процессом
            public uint cntThreads; // кол-во потоков в данном процессе
            public uint th32ParentProcessID; // идентификатор родительского процесса
            public int pcPriClassBase; // базовый приоритет процесса
            public uint dwFlags; // зарезервировано
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 260)]
            public string szExeFile; // путь к exe фaйлу или драйверу связанному с этим процессом
        }

        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        static extern bool Process32First([In] IntPtr hSnapshot, ref PROCESSENTRY32 lppe);
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        static extern bool Process32Next([In] IntPtr hSnapshot, ref PROCESSENTRY32 lppe);

        public struct HEAPLIST32
        {
            public uint dwSize;
            public uint th32ProcessID;
            public uint th32HeapID;
            public uint dwFlags;
        }

        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern bool Heap32ListFirst([In] IntPtr hSnapshot, ref HEAPLIST32 lphl);
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern bool Heap32ListNext([In] IntPtr hSnapshot, ref HEAPLIST32 lphl);

        public struct HEAPENTRY32
        {
            public uint dwSize;
            public IntPtr hHandle;
            public uint dwAddress;
            public uint dwBlockSize;
            public uint dwFlags;
            public uint dwLockCount;
            public uint dwResvd;
            public uint th32ProcessID;
            public uint th32HeapID;
        }
        public static readonly uint LF32_FREE = 0x00008000;

        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern bool Heap32First(ref HEAPENTRY32 lphe, [In] uint th32ProcessID, [In] uint th32HeapID);
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern bool Heap32Next(ref HEAPENTRY32 lphe);

        #endregion
    }
}
