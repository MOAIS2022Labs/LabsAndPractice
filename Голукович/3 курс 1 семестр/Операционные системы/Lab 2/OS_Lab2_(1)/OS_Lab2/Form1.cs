using OS_Lab2.Service;
using System;
using System.Collections.Generic;
using System.Threading;
using System.Windows.Forms;

//неизвестен без названия (похожа на 1 задачу)

namespace OS_Lab2
{
    public partial class Form1 : Form
    {
        private Thread controlThread; //основной поток
        private Thread taskThread1; //первый поток считает директории внутри первого каталога
        private Thread taskThread2; //второй поток считает директории внутри второго каталога

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (controlThread != null && controlThread.IsAlive) //проверка на существование или выполнение
                return;

            if (label3.Text != "" && label4.Text != "") //если не пусты
            {
                if (label3.Text != label4.Text) //если не равны
                {
                    List<string> dirs1 = new List<string>(); //список директорий первого каталога
                    List<string> dirs2 = new List<string>(); //список директорий второго каталога
                    taskThread1 = new Thread(() => //первый поток считает директории внутри первого каталога
                    {
                        dirs1 = new FileService().FindDirsCount(label3.Text);
                    });
                    taskThread2 = new Thread(() => //второй поток считает директории внутри второго каталога
                    {
                        dirs2 = new FileService().FindDirsCount(label4.Text);
                    });

                    //инициализация основного потока
                    //основной поток запускает и ожидает завершения двух других потоков
                    controlThread = new Thread(() => 
                    {
                        try
                        {
                            //запуск
                            taskThread1.Start();
                            taskThread2.Start();

                            //ожидание завершения
                            taskThread1.Join();
                            taskThread2.Join();

                            //вызов для родительского потока
                            //(в данном случае для системного потока в котором запускается сама форма)
                            BeginInvoke(new MethodInvoker(() =>
                            {
                                //чистим внешку
                                richTextBox1.Clear();
                                //кладем файлы во внешку
                                foreach (string dir in dirs1)
                                    richTextBox1.AppendText(dir + '\n');

                                //чистим внешку
                                richTextBox2.Clear();
                                //кладем файлы во внешку
                                foreach (string dir in dirs2)
                                    richTextBox2.AppendText(dir + '\n');
                            }));

                            //если количество равно
                            if (dirs1.Count == dirs2.Count)
                                MessageBox.Show($"Count of directories is equals ({dirs1.Count})", "Result",
                                    MessageBoxButtons.OK, MessageBoxIcon.Information);
                            else
                            {
                                //если больше/меньше
                                if (dirs1.Count > dirs2.Count)
                                    MessageBox.Show($"Count of directories from 1 catalog ({dirs1.Count}) more then 2 catalog ({dirs2.Count}): ", "Result",
                                        MessageBoxButtons.OK, MessageBoxIcon.Information);
                                else
                                    MessageBox.Show($"Count of directories from 2 catalog ({dirs2.Count}) more then 1 catalog ({dirs1.Count}): ", "Result",
                                        MessageBoxButtons.OK, MessageBoxIcon.Information);
                            }
                        }
                        catch(Exception ex) // рандомное исключение из функции FindDirsCount
                        {
                            MessageBox.Show(ex.Message, "Error!",
                                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        }
                    });

                    //запуск основного потока
                    controlThread.Start();
                }
                else
                    MessageBox.Show("Catalogs are equals!", "Error!",
                                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else
                MessageBox.Show("Catalog is empty!", "Error!",
                                MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }

        //кнопка крестик закрытие завершение 
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (controlThread != null) //если создан - надо подождать
                controlThread.Join();
        }

        //кнопка - поле для выбора первого каталога
        private void label3_Click(object sender, EventArgs e)
        {
            //вызов диалога с файловой системой
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            dialog.ShowNewFolderButton = false;
            dialog.Description = "Select 1 catalog:";
            //если результат диалога - конпка ОК
            if (dialog.ShowDialog() == DialogResult.OK)
                label3.Text = dialog.SelectedPath;
        }

        //кнопка - поле для выбора второго каталога
        private void label4_Click(object sender, EventArgs e)
        {
            //вызов диалога с файловой системой
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            dialog.ShowNewFolderButton = false;
            dialog.Description = "Select 2 catalog:";
            //если результат диалога - конпка ОК
            if (dialog.ShowDialog() == DialogResult.OK)
                label4.Text = dialog.SelectedPath;
        }
    }
}
