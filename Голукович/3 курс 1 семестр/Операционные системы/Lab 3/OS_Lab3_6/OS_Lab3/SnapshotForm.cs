using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using static OS_Lab3.SnapshotWorker;

//задача 6

namespace OS_Lab3
{
    public partial class SnapshotForm : Form
    {
        //поток для вычислений
        private Thread snapshotThread;
        //задаваемое n
        private uint n = 0;

        //инициализация формы
        public SnapshotForm()
        {
            InitializeComponent();
        }

        //кнопка Запуск
        private void buttonStart_Click(object sender, EventArgs e)
        {
            //если поток для вычислений работает
            if (snapshotThread != null && snapshotThread.IsAlive)
                return;

            //если поле для n не пусто и при этом не удалость распарсить
            if (!textBoxN.Text.Equals("") && !uint.TryParse(textBoxN.Text, out n))
            {
                MessageBox.Show("Введены неверные данные!", "Ошибка!",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            //ставим задачу потока
            snapshotThread = new Thread(() =>
            {
                //создаем новый объект для работы со снапшотами
                SnapshotWorker worker = new SnapshotWorker(n);
                //получаем список процессов и объем первых их куч, превышающих n
                List<(PROCESSENTRY32, uint)> list = worker.Task();

                //если список не пуст
                if (list.Count > 0)
                {
                    foreach (var pair in list)
                    {
                        //печать в вывод из родительского потока
                        BeginInvoke(new MethodInvoker(() =>
                        {
                            //печатаем название процесса и объем первой его кучи, превышающий n
                            richTextBoxProcesses.AppendText($"{pair.Item1.szExeFile} : {pair.Item2} байт\n");
                        }));
                    }
                }
                else
                {
                    //печать в вывод из родительского потока
                    BeginInvoke(new MethodInvoker(() =>
                    {
                        richTextBoxProcesses.AppendText($"Нет процессов, использующих блоки больше чем {n} байт");
                    }));
                }
            });

            //чистим вывод
            richTextBoxProcesses.Clear();
            //запускаем поток для вычислений
            snapshotThread.Start();
        }

        //событие при закрытии формы
        private void SnapshotForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            //если поток для вычислений существует и работает - перед закрытием ждем завершения
            if (snapshotThread != null && snapshotThread.IsAlive)
                snapshotThread.Join();
        }
    }
}
