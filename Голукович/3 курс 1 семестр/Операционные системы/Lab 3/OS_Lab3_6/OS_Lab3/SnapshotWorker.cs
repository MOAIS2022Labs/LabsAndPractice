using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.InteropServices;

namespace OS_Lab3
{
    public class SnapshotWorker
    {
        //дно для прохода по кучам, ограничение чтобы не зависало при поиске
        private const int HEAP_LIST_MAX = 10000000;
        //задаваемое n
        private readonly uint n;
        
        //конструктор, инициализируем n
        public SnapshotWorker(uint n)
        {
            this.n = n;
        }

        //вывести информацию о владельцах блоков, больших заданного n
        public List<(PROCESSENTRY32, uint)> Task()
        {
            //инициализируем пустой список пар (процесс : размер блока)
            List < (PROCESSENTRY32, uint)> result = new List<(PROCESSENTRY32, uint)>();
            //инициализируем указатель на снапшот
            IntPtr currentSnapshot = IntPtr.Zero;
            try
            {
                //создаем снапшот, тк флаг All - снапшот собирает информацию обо всех доступных сущностях
                currentSnapshot = CreateToolhelp32Snapshot((UInt32)SnapshotFlags.All, 0);

                //инициализируем сущность процесса для итерации
                PROCESSENTRY32 processEntry = new PROCESSENTRY32();
                //задаем размер сущности, тк если не задать - упадет с исключением
                processEntry.dwSize = (uint)Marshal.SizeOf(typeof(PROCESSENTRY32));

                //если нашли первый процесс
                if (Process32First(currentSnapshot, ref processEntry))
                {
                    //начинаем итерироваться по процессам
                    do
                    {
                        //инициализируем сущность кучи для итерации
                        HEAPLIST32 heapList = new HEAPLIST32();
                        //задаем размер сущности, тк если не задать - упадет с исключением
                        heapList.dwSize = (uint)Marshal.SizeOf(typeof(HEAPLIST32));

                        //инициализируем сущность блока кучи для итерации
                        HEAPENTRY32 heapEntry = new HEAPENTRY32();
                        //задаем размер сущности, тк если не задать - упадет с исключением
                        heapEntry.dwSize = (uint)Marshal.SizeOf(typeof(HEAPENTRY32));

                        //счетчик для дна HEAP_LIST_MAX
                        int heapListEntryCounter = 0;
                        //флаг, нашли ли кучу, превышающую n
                        bool addedFlag = false;

                        //если нашли первую кучу
                        if (Heap32ListFirst(currentSnapshot, ref heapList))
                        {
                            //начинаем итерироваться по кучам
                            do
                            {
                                //если это куча текущего процесса - начинаем итерироваться по блокам этой кучи
                                if (processEntry.th32ProcessID == heapList.th32ProcessID)
                                {
                                    //если нашли кучу
                                    if (Heap32First(ref heapEntry, heapList.th32ProcessID, heapList.th32HeapID))
                                    {
                                        //увеличили счетчик для дна HEAP_LIST_MAX
                                        heapListEntryCounter++;

                                        //начинаем итерироваться по блокам кучи
                                        do
                                        {
                                            //если размер кучи превышает n
                                            if (heapEntry.dwBlockSize >= n)
                                            {
                                                //поднимаем флаг
                                                addedFlag = true;
                                                result.Add((processEntry, heapEntry.dwBlockSize));
                                            }
                                        }
                                        //продолжаем итерацию пока не закончатся блоки кучи или не найдем нужный
                                        while (Heap32Next(ref heapEntry)/* && !addedFlag*/);
                                    }
                                    else
                                    {
                                        //если не нашли первый блок кучи - win32 бросил исключение
                                        //берем последнюю ошибку и выбрасываем наверх
                                        throw new Win32Exception($"Win32 error code {Marshal.GetLastWin32Error()}");
                                    }
                                }
                            }
                            //продолжаем итерацию пока:
                                //не закончатся кучи
                                //не найдем нужный блок кучи для процесса
                                //не превысим лимит HEAP_LIST_MAX
                            while (Heap32ListNext(currentSnapshot, ref heapList)/* && heapListEntryCounter < HEAP_LIST_MAX && !addedFlag*/);
                        }
                        else
                        {
                            //если не нашли первую кучу - win32 бросил исключение
                            //берем последнюю ошибку и выбрасываем наверх
                            throw new Win32Exception($"Win32 error code {Marshal.GetLastWin32Error()}");
                        }
                    }
                    //продолжаем итерацию пока не закончатся процессы
                    while (Process32Next(currentSnapshot, ref processEntry));
                }
                else
                {
                    //если не нашли первый процесс - win32 бросил исключение
                    //берем последнюю ошибку и выбрасываем наверх
                    throw new Win32Exception($"Win32 error code {Marshal.GetLastWin32Error()}");
                }
            }
            //в конце освобождаем память, выделенную под снапшот
            finally
            {
                CloseHandle(currentSnapshot);
            }
            //возвращаем список пар (процесс : размер блока)
            return result;
        }

        #region kernel32

        //флаги для создания снапшота
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

        //импорт методов создания и освобождения памяти, выделенной под снапшот
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern IntPtr CreateToolhelp32Snapshot([In] UInt32 dwFlags, [In] uint th32ProcessID);
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern bool CloseToolhelp32Snapshot([In] IntPtr hSnapshot);
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern bool CloseHandle([In] IntPtr hObject);

        //структура-сущность процесса
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

        //импорт методов поиска первого и следующего процесса в снапшоте
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        static extern bool Process32First([In] IntPtr hSnapshot, ref PROCESSENTRY32 lppe);
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        static extern bool Process32Next([In] IntPtr hSnapshot, ref PROCESSENTRY32 lppe);

        //структура-сущность кучи
        public struct HEAPLIST32
        {
            public uint dwSize; // размер записи
            public uint th32ProcessID; // идентификационный номер процесса
            public uint th32HeapID; // идентификатор кучи
            public uint dwFlags; // признак, определяющий тип кучи
        }

        //импорт методов поиска первой и следующей кучи в снапшоте
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern bool Heap32ListFirst([In] IntPtr hSnapshot, ref HEAPLIST32 lphl);
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern bool Heap32ListNext([In] IntPtr hSnapshot, ref HEAPLIST32 lphl);

        //структура-сущность блока кучи
        public struct HEAPENTRY32
        {
            public uint dwSize; // размер записи
            public IntPtr hHandle; // дескриптор блока кучи
            public uint dwAddress; // линейный адрес начала блока кучи
            public uint dwBlockSize; // размер блока кучи в байтах
            public uint dwFlags; // признак, определяющий тип кучи
            public uint dwLockCount; // счетчик блокировок блока памяти
            public uint dwResvd; // зарезервировано в данный момент и не должно использоваться
            public uint th32ProcessID; // идентификационный номер процесса
            public uint th32HeapID; // идентификатор кучи
        }

        //импорт методов поиска первого и следующего блока заданной кучи в снапшоте
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern bool Heap32First(ref HEAPENTRY32 lphe, [In] uint th32ProcessID, [In] uint th32HeapID);
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern bool Heap32Next(ref HEAPENTRY32 lphe);

        #endregion
    }
}
