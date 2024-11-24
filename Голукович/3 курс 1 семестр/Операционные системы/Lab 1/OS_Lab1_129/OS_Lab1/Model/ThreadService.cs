namespace OS_Lab1.Model
{
    public class ThreadService
    {
        public Action<string> WriteToOutput = Console.WriteLine;

        private Action<ThreadSafeBuffer<int>, int, int, List<bool>> _producerTask;

        private Action<ThreadSafeBuffer<int>, int, int, List<bool>> _consumerTask;

        private Dictionary<ThreadSafeBuffer<int>, (Thread, Thread)> _buffersThreads = new();

        private Thread _serviceThread;
        public bool IsAlive => _serviceThread.IsAlive;
        public List<bool> SyncronizationData { get; set; } = new();

        public ThreadService(List<int> maxBufferSizes, List<int> tasksCounts, List<(Action, Action, Action, Action)> viewActions)
        {
            _producerTask =
            (buffer, tasksCount, pushDelay, syncronizationData) =>
            {
                viewActions[buffer.Id].Item1();
                string message;
                while (tasksCount > 0)
                {
                    if (!syncronizationData[buffer.Id])
                    {
                        viewActions[buffer.Id].Item3();
                        message = "Поставщик " + buffer.Id + " был приостановлен";
                        WriteToOutput(message);
                        while (!syncronizationData[buffer.Id])
                            Thread.Sleep(1);
                        if (syncronizationData[buffer.Id])
                        {
                            viewActions[buffer.Id].Item1();
                            message = "Поставщик " + buffer.Id + " продолжил работу";
                            WriteToOutput(message);
                        }
                    }

                    int value = new Random().Next(100);

                    buffer.Push(value);
                    message = "Поставщик " + buffer.Id + " положил в буффер " + value;
                    tasksCount--;

                    WriteToOutput(message);
                    Thread.Sleep(pushDelay);
                }
                message = "Поставщик " + buffer.Id + " закончил работу";
                WriteToOutput(message);
            };

            _consumerTask =
            (buffer, tasksCount, popDelay, syncronizationData) =>
            {
                viewActions[buffer.Id].Item1();
                string message;
                while (tasksCount > 0)
                {
                    if (!syncronizationData[buffer.Id])
                    {
                        viewActions[buffer.Id].Item3();
                        message = "Потребитель " + buffer.Id + " был приостановлен";
                        WriteToOutput(message);
                        while (!syncronizationData[buffer.Id])
                            Thread.Sleep(1);
                        if (syncronizationData[buffer.Id])
                        {
                            viewActions[buffer.Id].Item1();
                            message = "Потребитель " + buffer.Id + " продолжил работу";
                            WriteToOutput(message);
                        }
                    }

                    int value = 0;

                    buffer.Pop(ref value);
                    message = "Потребитель " + buffer.Id + " взял из буффера " + value;
                    tasksCount--;

                    WriteToOutput(message);
                    Thread.Sleep(popDelay);
                }
                message = "Потребитель " + buffer.Id + " закончил работу";
                WriteToOutput(message);
                buffer.Clear();
                message = "Буффер " + buffer.Id + " был обработан и очищен";
                WriteToOutput(message);
                viewActions[buffer.Id].Item2();
            };

            _serviceThread = new Thread(() =>
            {
                for (int i = 0; i < tasksCounts.Count; ++i)
                {
                    if (maxBufferSizes[i] != -1 && tasksCounts[i] != -1)
                    {
                        Random random = new Random();
                        var buffer = new ThreadSafeBuffer<int>(maxBufferSizes[i], i);

                        _buffersThreads.Add(
                            buffer,
                            new(
                                new Thread(() => _producerTask(
                                    buffer, 
                                    tasksCounts[i], 
                                    random.Next(3, 40) * 100,
                                    SyncronizationData
                                )),
                                new Thread(() => _consumerTask(
                                    buffer, 
                                    tasksCounts[i], 
                                    random.Next(3, 40) * 100,
                                    SyncronizationData
                                ))));

                        int firstStart = random.Next(0, 2);
                        if (firstStart == 1)
                            _buffersThreads[buffer].Item1.Start();
                        else
                            _buffersThreads[buffer].Item2.Start();

                        int taskDelay = random.Next(1, 8);
                        Thread.Sleep(taskDelay * 1000);

                        if (firstStart == 1)
                            _buffersThreads[buffer].Item2.Start();
                        else
                            _buffersThreads[buffer].Item1.Start();

                        taskDelay = random.Next(1, 8);
                        Thread.Sleep(taskDelay * 1000);
                    }
                }
            });
        }

        public void Start()
        {
            _serviceThread.Start();
        }

        public void Join()
        {
            foreach (var bufferThreads in _buffersThreads)
            {
                bufferThreads.Value.Item1.Join();
                bufferThreads.Value.Item2.Join();
            }
            if (_serviceThread.IsAlive)
                _serviceThread.Join();
        }
    }
}
