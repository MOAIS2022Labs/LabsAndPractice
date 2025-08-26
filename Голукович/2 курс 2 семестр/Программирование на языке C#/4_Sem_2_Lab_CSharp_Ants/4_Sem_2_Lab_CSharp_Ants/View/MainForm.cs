using _4_Sem_2_Lab_CSharp_Ants.View;
using System;
using System.Collections.Generic;
using System.Threading;
using System.Windows.Forms;
using System.Drawing;

namespace _4_Sem_2_Lab_CSharp_Ants
{
    //View
    //основная windows-форма, на которой происходит отрисовка
    public partial class MainForm : Form
    {
        public int FoodMaxSize { get; set; } = 0;
        public int FoodCount { get; set; } = 0;
        public int Larvae { get; set; } = 0;
        public int SoldierAnts { get; set; } = 0;
        public int PoliceAnts { get; set; } = 0;
        public int WorkerAnts { get; set; } = 0;
        public int Pests { get; set; } = 0;
        //флаг, запущена ли форма
        //  1 - запущена
        //  0 - остановлена
        //  -1 - останавливается/запускается
        public int IsRunning { get; private set; }

        //событие, вызываемое пепед инициализацией taskViewers а так же после самой инициализации
        //(логика события прописывается в controller'е)
        public event Action NotifyInit;
        //событие, вызываемое при остановке работы формы
        //(логика события прописывается в controller'е)
        public event Action NotifyStop;

        //список объектов инициализации для TaskViewers
        public List<List<object>> TaskViewersArgs;
        //список объектов TaskViewers
        public List<TaskViewer> TaskViewers;
        //словарь TaskViewer/Thread
        //тк действия изменения положения TaskViewer на windows-форме должны происходить одновременно
        private Dictionary<TaskViewer, Thread> threads;
        //конструктор windows-формы
        public MainForm()
        {
            IsRunning = 0;
            TaskViewers = new List<TaskViewer>();
            threads = new Dictionary<TaskViewer, Thread>();
            InitializeComponent();
            textBoxFoodSize.Text = "Размер";
            textBoxFoodSizeInput.Text = "0";
            textBoxFoodCount.Text = "Количество";
            textBoxFoodCountInput.Text = "0";
            textBoxLarvae.Text = "Личинки";
            textBoxLarvaeInput.Text = "0";
            textBoxSoldierAnts.Text = "Солдаты";
            textBoxSoldierAntsInput.Text = "0";
            textBoxPoliceAnts.Text = "Полицейские";
            textBoxPoliceAntsInput.Text = "0";
            textBoxWorkerAnts.Text = "Рабочие";
            textBoxWorkerAntsInput.Text = "0";
            textBoxPests.Text = "Вредители";
            textBoxPestsInput.Text = "0";
        }
        //запуск действий TaskViewers
        private void StartTaskViewers()
        {
            foreach (List<object> args in TaskViewersArgs)
            {
                //инициализация taskViewer и запсук его действий в отдельном потоке
                TaskViewer taskViewer = new TaskViewer((string)args[1], (string)args[0], (Point)args[2], (Point)args[3]);
                TaskViewers.Add(taskViewer);
                threads[taskViewer] = new Thread(() =>
                {
                    //вызов из родительского потока, где был создан поток taskViewer'а
                    BeginInvoke(new MethodInvoker(() => 
                    {
                        //захват windows-формой PictureBox'а и TextBox'а, которые лежат в taskViewer'е
                        Controls.Add(taskViewer.PictureBox);
                        Controls.Add(taskViewer.TextBox);
                    }));
                    //инициализация метода Action Move taskViewer'а, отвечающего за перемещение taskViewer'а по windows-форме
                    taskViewer.Move = (Point curPoint) =>
                    {
                        //вызов из родительского потока, где был создан поток taskViewer'а
                        BeginInvoke(new MethodInvoker(() =>
                        {
                            //если taskViewer не закончил свое движение
                            if (taskViewer.MovingFlag != -1)
                            {
                                //задаем новые координаты для PictureBox'а и TextBox'а
                                taskViewer.PictureBox.Location = new Point(curPoint.X, curPoint.Y);
                                taskViewer.TextBox.Location = new Point(curPoint.X, curPoint.Y + taskViewer.PictureBox.Height);
                                //обновляем текстовые данные taskViewer'а в TextBox'е
                                // !!! тернарник - костыль, я вообще хз почему оно вообще может в Value получать отрицательные значения
                                taskViewer.TextBox.Text = taskViewer.Name + ": " + (taskViewer.Value < 0 ? "0" : taskViewer.Value.ToString());
                                //обновляем положение PictureBox'а и TextBox'а на windows-форме
                                int pictureBoxIndex = Controls.IndexOf(taskViewer.PictureBox);
                                Controls[pictureBoxIndex].Update();
                                int textBoxIndex = Controls.IndexOf(taskViewer.TextBox);
                                Controls[textBoxIndex].Update();
                            }
                        }));
                    };
                    //устанавливаем taskViewer'а в исходное положение
                    taskViewer.Move(taskViewer.PictureBox.Location);
                    //запускаем движение taskViewer'а по форме
                    taskViewer.Run();
                });
            }
            //запуск всех потоков taskViewers
            foreach (Thread thread in threads.Values)
                thread.Start();
        }
        //
        private void StopAllTaskViewers()
        {
            //остановка движения всех TaskViewer'ов 
            foreach (TaskViewer taskViewer in TaskViewers)
            {
                //меняем флаг taskViewer'а на -1
                taskViewer.MovingFlag = -1;
                //ожидаем полной остановки движения taskViewer'а на windows-форме
                threads[taskViewer].Join();
                Controls.Remove(taskViewer.PictureBox);
                Controls.Remove(taskViewer.TextBox);
            }
            //очищаем списки
            TaskViewers.Clear();
            threads.Clear();
        }
        //попытка остановить все TaskViewer'ы на windows-форме
        public bool TryStopAllTaskViewers()
        {
            bool result = false;
            if (IsRunning == 1)
            {
                //меняем флаг на "останавливается"
                IsRunning = -1;
                //вызываем событие остановки формы
                //(инициализируется в controller)
                NotifyStop();
                StopAllTaskViewers();
                //меняем флаг на "остановлен"
                IsRunning = 0;
                result = true;
            }
            return result;
        }

        //событие нажатия на кнопку Stop
        private void buttonStop_Click(object sender, EventArgs e)
        {
            //пытаемся остановить форму
            if (!TryStopAllTaskViewers())
                MessageBox.Show("Приложение уже остановлено.", "Предупреждение!",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }

        //событие нажатия на кнопку Start
        private void buttonStart_Click(object sender, EventArgs e)
        {
            //если остановлена
            if (IsRunning == 0)
            {
                IsRunning = -1;

                //инициализируем исходные значения значениями из TextBox'ов
                bool isZero = false;
                int value;

                if (!int.TryParse(textBoxFoodSizeInput.Text, out value))
                {
                    isZero = true;
                    FoodMaxSize = 0;
                }
                else
                    FoodMaxSize = value;

                if (!int.TryParse(textBoxFoodCountInput.Text, out value))
                {
                    isZero = true;
                    FoodCount = 0;
                }
                else
                    FoodCount = value;

                if (!int.TryParse(textBoxLarvaeInput.Text, out value))
                {
                    isZero = true;
                    Larvae = 0;
                }
                else
                    Larvae = value;

                if (!int.TryParse(textBoxSoldierAntsInput.Text, out value))
                {
                    isZero = true;
                    SoldierAnts = 0;
                }
                else
                    SoldierAnts = value;

                if (!int.TryParse(textBoxPoliceAntsInput.Text, out value))
                {
                    isZero = true;
                    PoliceAnts = 0;
                }
                else
                    PoliceAnts = value;

                if (!int.TryParse(textBoxWorkerAntsInput.Text, out value))
                {
                    isZero = true;
                    WorkerAnts = 0;
                }
                else
                    WorkerAnts = value;

                if (!int.TryParse(textBoxPestsInput.Text, out value))
                {
                    isZero = true;
                    Pests = 0;
                }
                else
                    Pests = value;

                if (isZero)
                    MessageBox.Show("Нечисловые значения были восприняты как 0.",
                        "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);

                //вызов события, инициализирующего TaskViewers
                NotifyInit();
                //запуск работы(движения) TaskViewers
                StartTaskViewers();
                //уведомление controller'а о том, что TaskViewers запущены
                //(так же через событие NotifyInit, которое инициализирует TaskViewers)
                NotifyInit();
                IsRunning = 1;
            }
            else
                MessageBox.Show("Приложение уже было запущено.",
                        "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }

        //событие, вызываемое при нажатии на кнопку "закрыть окно"(крестик)
        private void MainForm_Load(object sender, EventArgs e)
        {
            //событие, вызываемое при закрытии windows-формы
            Closed += (object s, EventArgs ev) => 
            {
                IsRunning = -1;
                StopAllTaskViewers();
                IsRunning = 0;
            };
        }
    }
}
