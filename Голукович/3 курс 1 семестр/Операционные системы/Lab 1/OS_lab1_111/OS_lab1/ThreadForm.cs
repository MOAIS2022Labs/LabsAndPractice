using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

//задача 1.1.1(стэк-лок)

namespace OS_lab1
{
    public partial class ThreadForm : Form
    {
        private Threads _threads = null; //класс потоков
        private bool _paused = false; //флаг приостановки
        public ThreadForm()
        {
            InitializeComponent();
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            //проверка, создан ли объект класса и запущен ли он
            if (_threads != null && _threads.IsAlive()) 
            {
                MessageBox.Show("Потоки уже работают!", "Ошибка",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            //количество читаемых/записываемых элементов для потоков
            int count0 = 0, count1 = 0, count2 = 0, count3 = 0;
            //размер буффера
            int size = 0;
            //проверка валидности
            if (!int.TryParse(textBoxBuffer.Text, out size)
                || !int.TryParse(textBoxThread0.Text, out count0)
                || !int.TryParse(textBoxThread1.Text, out count1)
                || !int.TryParse(textBoxThread2.Text, out count2)
                || !int.TryParse(textBoxThread3.Text, out count3)
                || count0 + count1 > count2 + count3)
            {
                MessageBox.Show("Введены неверные данные!", "Ошибка",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            //очистка текстовых полей на форме
            richTextBoxBuffer.Clear();
            richTextBoxThreads.Clear();

            //это не потоки, это классы с методом передачи информации из потоков в форму
            //для потоков один вывод
            //lock внутри чтобы потоки точно друг друга не перебивали при записи
            Writer threadWriter = new Writer((message) =>
            {
                BeginInvoke(new MethodInvoker(() =>
                {
                    lock (sender)
                    {
                        richTextBoxThreads.AppendText(message + '\n');
                    }
                }));
            });

            //для буффера другой, поинтереснее
            //работает как стек
            Writer bufferPushWriter = new Writer((message) =>
            {
                BeginInvoke(new MethodInvoker(() =>
                {
                    lock (sender)
                    {
                        //добавляет message в начало текстового поля буффера на форме
                        StringBuilder builder = new StringBuilder();
                        builder.AppendLine(message);
                        builder.AppendLine(richTextBoxBuffer.Text);
                        richTextBoxBuffer.Text = builder.ToString();
                    }
                }));
            });
            Writer bufferPopWriter = new Writer((message) =>
            {
                BeginInvoke(new MethodInvoker(() =>
                {
                    lock (sender)
                    {
                        //забирает первый попавшийся message из текстового поля буффера на форме
                        StringBuilder builder = new StringBuilder();
                        string[] bufferText = richTextBoxBuffer.Text.Split('\n');

                        for (int i = 0; i < bufferText.Length; ++i)
                            if (!bufferText[i].Equals(message))
                                builder.AppendLine(bufferText[i]);

                        richTextBoxBuffer.Text = builder.ToString();
                    }
                }));
            });

            //буффер
            StackBuffer<int> buffer = new StackBuffer<int>(size, bufferPushWriter, bufferPopWriter);

            //класс потоков
            _threads = new Threads(threadWriter, buffer, new List<int>() { count0, count1, count2, count3 });
            //запуск отдельного потока 
            _threads.Start();
        }

        private void buttonPause_Click(object sender, EventArgs e)
        {
            //проверка, создан ли объект класса и запущен ли он
            if (_threads != null && _threads.IsAlive())
            {
                //если на паузе
                if (_paused)
                {
                    _paused = false;
                    buttonPause.Text = "Приостановить";
                    _threads.Resume();
                }
                //если в потоке в ресурсе на волне
                else
                {
                    _paused = true;
                    buttonPause.Text = "Возобновить";
                    _threads.Pause();
                }
            }
        }

        private void ThreadForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            //проверка, создан ли объект класса
            if (_threads != null)
            {
                //на всякий возобновляем
                _threads.Resume();
                //ждем завершения, тк аборты - это плохо..
                _threads.Join();
            }
        }
    }
}
