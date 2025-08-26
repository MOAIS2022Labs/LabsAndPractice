using OS_Lab1.Model;
using System;
using System.Text;
using System.Threading;
using System.Windows.Forms;

//задача 6

namespace Lab1_OS
{
    // задача такая: есть 4 потока - 2 писателя/2 читателя, у каждой пары свой буффер,
    // то есть в 1 буффер кладет 1 писатель и забирает 1 читатель,
    // а во 2 буффер кладет 2 писатель и забирает 2 читатель
    
    // мы умеем: отдельно приостанавливать каждый из потоков писателей/читателей

    public partial class ThreadingForm : Form
    {
        //потоки 1 и 2 читателей
        private Thread firstReaderThread;
        private Thread secondReaderThread;
        //потоки 1 и 2 писателей
        private Thread firstWriterThread;
        private Thread secondWriterThread;
        //1 и 2 буфферы
        private ThreadSafeBuffer firstBuffer;
        private ThreadSafeBuffer secondBuffer;

        //флаг полной остановки 1 писателя и 2 читателя
        private bool threads1StopFlag = false;
        //флаг полной остановки 2 писателя и 2 читателя
        private bool threads2StopFlag = false;
        //флаги приостановки соответственно по названию
        private bool writer1ResumeFlag = false;
        private bool writer2ResumeFlag = false;
        private bool reader1ResumeFlag = false;
        private bool reader2ResumeFlag = false;
        //конструктор формы
        public ThreadingForm()
        {
            InitializeComponent();
        }

        //кнопка старт
        private void startButton_Click(object sender, EventArgs e)
        {
            //проверка что потоки еще не существуют или уже завершились,
            //тк не можем запустить уже запущенное
            if (firstReaderThread != null && firstReaderThread.IsAlive
                || secondReaderThread != null && secondReaderThread.IsAlive
                || firstWriterThread != null && firstWriterThread.IsAlive
                || secondWriterThread != null && secondWriterThread.IsAlive)
            {
                MessageBox.Show("Приложение уже запущено!",
                                "Ошибка!",
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Warning);
                return;
            }

            //инициализация максимальных размеров буфферов
            int firstBufferCapacity = 0;
            int secondBufferCapacity = 0;

            //парсим из текстовых полей на форме, если успешно - заходим в if
            if (int.TryParse(capacityFirstBufferTextBox.Text, out firstBufferCapacity)
                && int.TryParse(capacitySecondBufferTextBox.Text, out secondBufferCapacity))
            {
                //(action как лямбда)
                //action, который будет вызываться в методе Push/Pop первого буффера для связи с формой
                Action<string> writeFirstBuffer = (message) =>
                {
                    //пишет в форму какое-то сообщение message, задаваемое в методе, который будет вызывать action
                    BeginInvoke(new MethodInvoker(() => firstBufferRichTextBox.AppendText('\n' + message)));
                };
                //action, который будет вызываться в методе Push/Pop второго буффера для связи с формой
                Action<string> writeSecondBuffer = (message) =>
                {
                    //пишет в форму какое-то сообщение message, задаваемое в методе, который будет вызывать action
                    BeginInvoke(new MethodInvoker(() => secondBufferRichTextBox.AppendText('\n' + message)));
                };

                //инициализация буфферов с соответствующими аргументами
                firstBuffer = new ThreadSafeBuffer(firstBufferCapacity, writeFirstBuffer);
                secondBuffer = new ThreadSafeBuffer(secondBufferCapacity, writeSecondBuffer);

                //инициализируем поток 1 читателя
                firstReaderThread = new Thread(() =>
                {
                    //пока он полностью не остановлен (можно изменять значение флага вне этой области видимости)
                    while (!threads1StopFlag)
                    {
                        //реализация приостановки
                        //если поднят флаг на приостановку
                        if (reader1ResumeFlag)
                            //пока поднят флаг
                            while (reader1ResumeFlag)
                                //делаем жесткий слип0
                                Thread.Sleep(0);

                        //выполняем задачу: забираем значение из буффера(1)
                        //пофиг что не сохраняем, тк инфа уже выведена на форму в методе Pop
                        firstBuffer.Pop();

                        //типа рандомим время ожидания, имитация случайной работы
                        Thread.Sleep(new Random().Next(5, 10) * 100);
                    }
                    //в конце пишем, что закончили работу
                    writeFirstBuffer("reader end");
                });

                //инициализируем 2 читателя
                secondReaderThread = new Thread(() =>
                {
                    //все то же самое, только другие флаги (для 2 читателя) и другой буффер (2)
                    while (!threads2StopFlag)
                    {
                        if (reader2ResumeFlag)
                            while (reader2ResumeFlag)
                                Thread.Sleep(0);
                        secondBuffer.Pop();

                        Thread.Sleep(new Random().Next(5, 7) * 50);
                    }
                    writeSecondBuffer("reader end");
                });

                //инициализируем 1 писателя
                firstWriterThread = new Thread(() =>
                {
                    //индексатор, для количества произведенных успешеных записей
                    int i = 0;
                    //пока не остановлены
                    while (!threads1StopFlag)
                    {
                        //реализация приостановки (с флагом для 1 писателя)
                        if (writer1ResumeFlag)
                            while (writer1ResumeFlag)
                                Thread.Sleep(0);

                        //говорим, что 1 писатель положил i значение в буффер(1)
                        (int, int) value = (1, i);
                        //собственно кладем
                        firstBuffer.Push(value);
                        //увеличиваем индексатор
                        i++;
                        //рандомим время ожидания 
                        //где-то 50 где-то 100 чтобы явно задать, что некоторые потоки работают быстрее, некоторые медленее
                        Thread.Sleep(new Random().Next(1, 2) * 50);
                    }
                    //снова говорим что закончились
                    writeFirstBuffer("writer end");
                });

                //инициализируем 2 писателя соответственно как 1, только другие флаги и другой буффер(2)
                secondWriterThread = new Thread(() =>
                {
                    int i = 0;
                    while (!threads2StopFlag)
                    {
                        if (writer2ResumeFlag)
                            while (writer2ResumeFlag)
                                Thread.Sleep(0);

                        //говорим, что 2 писатель положил i значение в буффер(2)
                        (int, int) value = (2, i);
                        secondBuffer.Push(value);
                        i++;
                        Thread.Sleep(new Random().Next(5, 10) * 100);
                    }
                    writeSecondBuffer("writer end");
                });

                //запускаем все потоки
                firstReaderThread.Start();
                secondReaderThread.Start();
                firstWriterThread.Start();
                secondWriterThread.Start();
            }
            else //случай, если не распарсили данные
                MessageBox.Show("Неверные данные!",
                                "Ошибка!",
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Warning);
        }

        //событие, когда нажимаешь на крестик
        private void ThreadingForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            //явно останавливаем все потоки навсегда (поднимаем флаги)
            threads1StopFlag = true;
            threads2StopFlag = true;

            //если какие-то потоки были приостановлены - возобновляем, чтобы доработали (поднимаем флаги)
            writer1ResumeFlag = false;
            writer2ResumeFlag = false;
            reader1ResumeFlag = false;
            reader2ResumeFlag = false;

            //для каждого потока проверям, существует ли он, если существует - ождидаем завершения (если уже завершен - Join этой поймет)
            if (firstBuffer != null)
                firstReaderThread.Join();
            if (secondReaderThread != null)
                secondReaderThread.Join();
            if (firstWriterThread != null)
                firstWriterThread.Join();
            if (secondWriterThread != null)
                secondWriterThread.Join();

            //чистим буфферы (можно не чистить)
            if (firstBuffer != null)
                firstBuffer.Clear();
            if (secondBuffer != null)
                secondBuffer.Clear();
        }

        //кнопочка информативная (О лабе)
        private void infoButton_Click(object sender, EventArgs e)
        {
            StringBuilder builder = new StringBuilder();
            builder.AppendLine("Создать приложение с двумя дополнительными потоками ");
            builder.Append("писателей и двумя потоками читателей.");
            builder.AppendLine("Писатели в случайные моменты времени помещают записи, ");
            builder.Append("содержащие номер потока писателя и номер записи в буфер, ");
            builder.Append("читатели в случайные моменты времени удаляют записи, делая об этом сообщения.");
            builder.AppendLine("Каждая пара читатель — писатель использует свой буфер.");
            MessageBox.Show(builder.ToString(),
                            "О лабе",
                            MessageBoxButtons.OK,
                            MessageBoxIcon.Information);
        }

        //кнопки паузы соответствущих потоков, все аналогичные и почти одинаковые
        private void Writer1PauseButton_Click(object sender, EventArgs e)
        {
            //если поток существует и сейчас работает
            if (firstWriterThread != null && firstWriterThread.IsAlive)
            {
                //если приостановлен - возобновляем
                if (writer1ResumeFlag)
                {
                    //пишем на кнопку другую надпись
                    Writer1PauseButton.Text = "Приостановка писателя";
                    //возобновляем поток (поднимаем флаг)
                    writer1ResumeFlag = false;
                }
                //если работает - приостанавливаем
                else
                {
                    //пишем на кнопку другую надпись
                    Writer1PauseButton.Text = "Возобновление писателя";
                    //приостанавливаем поток (поднимаем флаг)
                    writer1ResumeFlag = true;
                }
            }
        }

        private void Reader1PauseButton_Click(object sender, EventArgs e)
        {
            if (firstReaderThread != null && firstReaderThread.IsAlive)
            {
                if (reader1ResumeFlag)
                {
                    Reader1PauseButton.Text = "Приостановка читателя";
                    reader1ResumeFlag = false;
                }
                else
                {
                    Reader1PauseButton.Text = "Возобновление читателя";
                    reader1ResumeFlag = true;
                }
            }
        }

        private void Writer2PauseButton_Click(object sender, EventArgs e)
        {
            if (secondWriterThread != null && secondWriterThread.IsAlive)
            {
                if (writer2ResumeFlag)
                {
                    Writer2PauseButton.Text = "Приостановка писателя";
                    writer2ResumeFlag = false;
                }
                else
                {
                    Writer2PauseButton.Text = "Возобновление писателя";
                    writer2ResumeFlag = true;
                }
            }
        }

        private void Reader2PauseButton_Click(object sender, EventArgs e)
        {
            if (secondReaderThread != null && secondReaderThread.IsAlive)
            {
                if (reader2ResumeFlag)
                {
                    Reader2PauseButton.Text = "Приостановка читателя";
                    reader2ResumeFlag = false;
                }
                else
                {
                    Reader2PauseButton.Text = "Возобновление читателя";
                    reader2ResumeFlag = true;
                }
            }
        }
    }
}