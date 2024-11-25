using _4_Sem_2_Lab_CSharp_Ants.Models;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System.Threading;

namespace _4_Sem_2_Lab_CSharp_Ants.Controller
{
    //Controller
    //запускает и связывает работу view и модели
    public class ApplicationController
    {
        //список аргументов для инициализации движущихся объектов на форме
        private List<List<object>> taskViewersArgs = new List<List<object>>();

        //объект синхронизации
        private object lockObject = new object();

        //модель(муравейник)
        private Anthil anthill;
        //view(windows-форма)
        private MainForm mainForm;
        //поток, в котором запускается view
        private Thread formThread;

        //функция, которая создает список аргументов для инициализации движущихся объектов на форме
        private void InitTaskViewers()
        {
            //Название, путь к изображению, точки начала/конца движения
            taskViewersArgs = new List<List<object>>()
            {
                new List<object> { "Королева", "..\\..\\References\\Square.png", new Point(630, 290), new Point(530, 290) },
                new List<object> { "Хранилище", "..\\..\\References\\Circle.png", new Point(420, 290), new Point(420, 290) },
                new List<object> { "Личинки", "..\\..\\References\\Rhomb.png", new Point(420, 60), new Point(420, 170) },
                new List<object> { "Солдаты", "..\\..\\References\\Pentagonal_star.png", new Point(530, 520), new Point(630, 520) },
                new List<object> { "Полицейские", "..\\..\\References\\Star.png", new Point(210, 410), new Point(210, 520)},
                new List<object> { "Рабочие", "..\\..\\References\\Triangle.png", new Point(210, 290), new Point(310, 290) },
                new List<object> { "Вредители", "..\\..\\References\\Pentagon.png", new Point(420, 520), new Point(420, 410) }
            };
        }

        //запуск работы контроллера
        public void Start()
        {
            //инициализация аргументов движущихся объектов на форме
            InitTaskViewers();

            //создание формы
            mainForm = new MainForm();

            Action createTaskViewers = () => { };
            Action initTaskViewers = () => { };
            Action initAnthill = () => { };

            //событие, передающее аргументы для инициализации движущихся объектов на форме в саму форму
            createTaskViewers = () => 
            { 
                //передача аргументов
                mainForm.TaskViewersArgs = taskViewersArgs;
                //отписываем событие mainForm.NotifyInit от createTaskViewers(строка 57)
                //(createTaskViewers отписывает себя само)
                mainForm.NotifyInit -= createTaskViewers;
                //подписываем событие mainForm.NotifyInit на initTaskViewers(строка 70) и initAnthill(строка 86)
                mainForm.NotifyInit += initTaskViewers;
                mainForm.NotifyInit += initAnthill;
            };

            //событие, инициализирующее изначальные данные да движущихся объектах
            initTaskViewers = () =>
            {
                //инициализация
                mainForm.TaskViewers[0].Value = 1;
                mainForm.TaskViewers[1].Value = mainForm.FoodCount * 10;
                mainForm.TaskViewers[2].Value = mainForm.Larvae;
                mainForm.TaskViewers[3].Value = mainForm.SoldierAnts;
                mainForm.TaskViewers[4].Value = mainForm.PoliceAnts;
                mainForm.TaskViewers[5].Value = mainForm.WorkerAnts;
                mainForm.TaskViewers[6].Value = mainForm.Pests;
                //отписываем событие mainForm.NotifyInit от initTaskViewers(строка 70)
                //(initTaskViewers отписывает себя само)
                mainForm.NotifyInit -= initTaskViewers;
            };

            //событие, инициализирующее модель(муравейник) и запсукающее его
            initAnthill = () =>
            {
                //инициализация новгого муравейника
                anthill = new Anthil(mainForm.FoodMaxSize, mainForm.FoodCount, mainForm.Larvae, mainForm.SoldierAnts,
                    mainForm.PoliceAnts, mainForm.WorkerAnts, mainForm.Pests, lockObject);

                //подписываем событие QueenDead на необходимые действия(остановку всех движущихся объектов на форме, если они движутся)
                anthill.QueenDead += () =>
                {
                    if (mainForm.IsRunning == 1)
                        mainForm.BeginInvoke(new MethodInvoker(() => { mainForm.TryStopAllTaskViewers(); }));
                };

                //подписываем событие InsectChanged на необходимые действия(обновление данных конкретного движущегося объекта на форме)
                anthill.InsectChanged += (Type t, int val) =>
                {
                    lock (lockObject)
                    {
                        if (mainForm.IsRunning == 1)
                        {
                            if (t == (Type)new Larva().GetType())
                                mainForm.TaskViewers[2].Value += val;

                            if (t == (Type)new SoldierAnt().GetType())
                                mainForm.TaskViewers[3].Value += val;

                            if (t == (Type)new PoliceAnt().GetType())
                                mainForm.TaskViewers[4].Value += val;

                            if (t == (Type)new WorkerAnt().GetType())
                                mainForm.TaskViewers[5].Value += val;

                            if (t == (Type)new Pest().GetType())
                                mainForm.TaskViewers[6].Value += val;
                        }
                    }
                };

                //подписываем событие InsectChanged на необходимые действия(изменение данных объекта Хранилище на форме)
                anthill.foodStorage.ChangeFoodStorage += (int val) => 
                {
                    lock (lockObject)
                    {
                        if (mainForm.IsRunning == 1)
                            mainForm.TaskViewers[1].Value += val;
                    }
                };

                //отписываем событие mainForm.NotifyInit от initAnthill(строка 86)
                //(initAnthill отписывает себя само)
                mainForm.NotifyInit -= initAnthill;
                //подписываем событие mainForm.NotifyInit на createTaskViewers(строка 57)
                //таким образом мы образуем цикл: при следующем вызове события mainForm.NotifyInit на форме будет снова вызвано событие createTaskViewers(строка 57)
                //и так пока мы не закроем форму
                mainForm.NotifyInit += createTaskViewers;

                //запуск работы муравейника
                anthill.Start();
            };

            //впервые подписываем событие mainForm.NotifyInit на createTaskViewers(строка 57)
            mainForm.NotifyInit += createTaskViewers;

            //подписываем событие mainForm.NotifyStop на необходимые действия
            //(если муравейник все еще работает - остановку муравейника и ожидание пока не остановится)
            mainForm.NotifyStop += () => 
            {
                if (anthill.IsAlive)
                {
                    anthill.Stop();
                    while (anthill.IsAlive)
                        Thread.Sleep(10);
                }
            };

            //запуск view(windows-формы) в отдельном потоке
            formThread = new Thread(() => { Application.Run(mainForm); });
            formThread.Start();
            formThread.Join();
        }
    }
}
