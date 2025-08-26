using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Threading;

namespace OS_lab1
{
    public class Threads
    {
        private Thread _readerThread1;
        private Thread _readerThread2;
        private Thread _writerThread1;
        private Thread _writerThread2;
        private Thread _thread;
        private bool _paused;
        private Writer _writer;
        private StackBuffer<int> _buffer;

        public Threads(Writer writer, StackBuffer<int> buffer, List<int> counts)
        {
            _paused = false;
            _writer = writer;
            Random random = new Random();

            _readerThread1 = new Thread(() =>
            {
                int i = counts[0];
                while (i > 0)
                {
                    if (_paused)
                        while (_paused)
                            Thread.Sleep(1);

                    int val = 0;
                    if (buffer.Pop(ref val))
                    {
                        writer.write("читатель1 считал " + val);
                        i--;
                    }
                    else
                        writer.write("читатель1 не смог считать");

                    Thread.Sleep(random.Next(100, 1000));
                }
            });
            _readerThread2 = new Thread(() =>
            {
                int i = counts[1];
                while (i > 0)
                {
                    if (_paused)
                        while (_paused)
                            Thread.Sleep(1);

                    int val = 0;
                    if (buffer.Pop(ref val))
                    {
                        writer.write("читатель2 считал " + val);
                        i--;
                    }
                    else
                        writer.write("читатель2 не смог считать");

                    Thread.Sleep(random.Next(100, 1000));
                }
            });
            _writerThread1 = new Thread(() =>
            {
                int i = counts[2];
                while (i > 0)
                {
                    if (_paused)
                        while (_paused)
                            Thread.Sleep(1);

                    int val = random.Next(0, 1000);
                    if (buffer.Push(val))
                    {
                        writer.write("писатель1 записал " + val);
                        i--;
                    }
                    else
                        writer.write("писатель1 не смог записать");

                    Thread.Sleep(random.Next(100, 1000));
                }
            });
            _writerThread2 = new Thread(() =>
            {
                int i = counts[3];
                while (i > 0)
                {
                    if (_paused)
                        while (_paused)
                            Thread.Sleep(1);

                    int val = random.Next(0, 1000);
                    if (buffer.Push(val))
                    {
                        writer.write("писатель2 записал " + val);
                        i--;
                    }
                    else
                        writer.write("писатель2 не смог записал");

                    Thread.Sleep(random.Next(100, 1000));
                }
            });

            _thread = new Thread(() =>
            {
                _writerThread1.Start();
                Thread.Sleep(random.Next(1000, 7000));
                
                _readerThread2.Start();
                Thread.Sleep(random.Next(1000, 7000));

                _writerThread2.Start();
                Thread.Sleep(random.Next(1000, 7000));

                _readerThread1.Start();
                Thread.Sleep(random.Next(1000, 7000));
            });
        }

        public void Start() => _thread.Start();

        public void Join()
        {
            _thread.Join();
            _readerThread1.Join();
            _readerThread2.Join();
            _writerThread1.Join();
            _writerThread2.Join();
            _writer.write("потоки завершились");
        }

        public void Pause() => _paused = true;
        public void Resume() => _paused = false;
        public bool IsAlive() => _readerThread1.IsAlive || _readerThread2.IsAlive
                                 || _writerThread1.IsAlive || _writerThread2.IsAlive
                                 || _thread.IsAlive;
    }
}
