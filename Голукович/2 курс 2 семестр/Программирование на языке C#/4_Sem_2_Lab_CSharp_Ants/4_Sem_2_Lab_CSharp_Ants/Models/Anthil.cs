using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

namespace _4_Sem_2_Lab_CSharp_Ants.Models
{
    //Model
    //Муравейник
    public class Anthil
    {
        //флаг, показывающий, работает муравейник или уже нет
        public bool IsAlive { get; private set; }

        //хранилище еды
        public FoodStorage foodStorage;

        //королева
        public Queen queen;

        //промежуточное количество личинок
        private int larvaeCount;
        //список обектов-личинок
        public List<Larva> Larvae { get; private set; }

        //промежуточное количество муравьев-полицейских
        private int policeAntsCount;
        //список обектов-муравьев-полицейских
        public List<PoliceAnt> PoliceAnts { get; private set; }

        //промежуточное количество муравьев-солдат
        private int soldierAntsCount;
        //список обектов-муравьев-солдат
        public List<SoldierAnt> SoldierAnts { get; private set; }

        //промежуточное количество муравьев-рабочих
        private int workerAntsCount;
        //список обектов-муравьев-рабочих
        public List<WorkerAnt> WorkerAnts { get; private set; }

        //промежуточное количество вредителей
        private int pestsCount;
        //список обектов-вредителей
        public List<Pest> Pests { get; private set; }

        //событие, вызываемое при "смерти" королевы
        public event Action QueenDead = delegate { };
        //событие, вызываемое при "смерти" личинки
        private event Action LarvaDead = delegate { };
        //событие, вызываемое при "смерти" муравья
        private event Action AntDead = delegate { };

        //событие, вызываемое при изменении количества насекомых в муравейнике
        //(для изменения отображаемых view данных и обновления текущих данных в модели:
        //  будет вызван запрос на обновление данных во view для определенного TaskViewr'а во view)
        public event Action<Type, int> InsectChanged = delegate { };

        //словарь потоков, в которых происходят действия отдельных насекомых(ключ - само насекомое)
        private Dictionary<Insect, Thread> threads;

        //объект синхронизации
        private object lockObject;
        //коэффициент для работы муравьев-полицейских и муравьев-рабочих
        private Int32 coefficient;

        //конструктор(максимальное кол-во еды, начальное кол-во еды, начальное кол-во личинок, начальное кол-во муравьев-солдат,
        //начальное кол-во муравьев-полицейских, начальное кол-во муравьев-рабочих, начальное кол-во вредителей)
        public Anthil(int maxFoodStorageSize, int foodCount, int larvaeCount, int soldierAntsCount, int policeAntsCount, int workerAntsCount, int pestsCount, object lockObject)
        {
            //инициализация начальных данных
            IsAlive = true;
            this.lockObject = lockObject;
            coefficient = 1;

            this.larvaeCount = larvaeCount;
            this.soldierAntsCount = soldierAntsCount;
            this.policeAntsCount = policeAntsCount;
            this.workerAntsCount = workerAntsCount;
            this.pestsCount = pestsCount;

            //создаем объекты согласно изначальным данным
            foodStorage = new FoodStorage(maxFoodStorageSize, lockObject);
            for (int i = 0; i < foodCount; ++i)
                foodStorage.Add(10);

            queen = new Queen();

            Larvae = new List<Larva>();
            for (int i = 0; i < larvaeCount; ++i)
                Larvae.Add(new Larva());

            SoldierAnts = new List<SoldierAnt>();
            for (int i = 0; i < soldierAntsCount; ++i)
                SoldierAnts.Add(new SoldierAnt());

            PoliceAnts = new List<PoliceAnt>();
            for (int i = 0; i < policeAntsCount; ++i)
                PoliceAnts.Add(new PoliceAnt());

            WorkerAnts = new List<WorkerAnt>();
            for (int i = 0; i < workerAntsCount; ++i)
                WorkerAnts.Add(new WorkerAnt());

            Pests = new List<Pest>();
            for (int i = 0; i < pestsCount; ++i)
                Pests.Add(new Pest());

            //словарь потоков
            threads = new Dictionary<Insect, Thread>();

            //подписываем событие QueenDead на необходимые действия
            //(от жизни королевы зависит жизнь муравейника: умирает королева - умирает муравейник)
            //в этом событии мы ждем пока закончат работу все насекомые муравейника, если королева мертва
            QueenDead += () => {
                IsAlive = false;
                Thread.Sleep(1000);
                foreach (var thread in threads)
                    if (thread.Key != queen)
                        thread.Value.Join();
                threads.Clear();
                Larvae.Clear();
                SoldierAnts.Clear();
                PoliceAnts.Clear();
                WorkerAnts.Clear();
                Pests.Clear();
            };

            //подписываем событие LarvaDead на необходимые действия
            //(при смерти личинки вызывается событие для изменения отображаемых view данных и обновления текущих данных в модели)
            LarvaDead += () => { InsectChanged(new Larva().GetType(), -1); };

            //подписываем событие AntDead на необходимые действия
            //(создаем новый объект Вредитель и запускаем его действия в отдельном потоке)
            AntDead += () =>
            {
                lock (lockObject)
                {
                    Pests.Add(new Pest());
                    SetPestAction(Pests.Last());
                    StartInsectAction(Pests.Last());
                }
            };
        }

        //запуск работы муравейника
        public void Start()
        {
            //подписываем событие InsectChanged на необходимые действия
            //(обновление текущих данных в модели)
            InsectChanged += (Type type, int count) =>
            {
                if (count > 0)
                {
                    if (type == new Larva().GetType())
                        //обновить данные личинок
                        UpdateLarvae();
                    if (type == new SoldierAnt().GetType())
                        //обновить данные муравьев-солдат
                        UpdateSoldierAnts();
                    if (type == new PoliceAnt().GetType())
                        //обновить данные муравьев-полицейских
                        UpdatePoliceAnts();
                    if (type == new WorkerAnt().GetType())
                        //обновить данные муравьев-рабочих
                        UpdateWorkerAnts();
                    if (type == new Pest().GetType())
                        //обновить данные вредителей
                        UpdatePests();
                }
            };

            //запускаем обновление для проинициализированных насекомых в муравейнике и запускаем действия потоков
            QueenActions();

            LarvaeActions();

            SoldierAntsActions();

            PoliceAntsActions();

            WorkerAntsActions();

            PestsActions();
        }

        //метод для остановки работы муравейника(убиваем королеву - останавливают свою работу все насекомые)
        public void Stop()
        {
            queen.Kill();
        }

        /*блок методов для обновления действий для новых насекомых*/
        private void UpdateLarvae()
        {
            int newInsectCount;
            lock(lockObject) { newInsectCount = Larvae.Count; }
            for (int i = larvaeCount; i < newInsectCount; i++) 
            {
                bool flag;
                lock (lockObject)
                {
                    if (Larvae.Count > i)
                        flag = threads.ContainsKey(Larvae[i]);
                    else
                        flag = true;
                }
                if (!flag && IsAlive)
                {
                    SetLarvaAction(Larvae[i]);
                    StartInsectAction(Larvae[i]);
                }
            }
            int removeCount = Larvae.RemoveAll(larva => !larva.State);
            larvaeCount = newInsectCount - removeCount;
        }
        private void UpdateSoldierAnts()
        {
            int newInsectCount;
            lock (lockObject) { newInsectCount = SoldierAnts.Count; }
            for (int i = soldierAntsCount; i < newInsectCount; i++)
            {
                bool flag;
                lock (lockObject)
                {
                    if (SoldierAnts.Count > i)
                        flag = threads.ContainsKey(SoldierAnts[i]);
                    else
                        flag = true;
                }
                if (!flag && IsAlive)
                {
                    SetSoldierAntAction(SoldierAnts[i]);
                    StartInsectAction(SoldierAnts[i]);
                }
            }
            int removeCount = SoldierAnts.RemoveAll(ant => !ant.State);
            soldierAntsCount = newInsectCount - removeCount;
        }
        private void UpdatePoliceAnts()
        {
            int newInsectCount;
            lock (lockObject) { newInsectCount = PoliceAnts.Count; }
            for (int i = policeAntsCount; i < newInsectCount; i++)
            {
                bool flag;
                lock (lockObject) 
                {
                    if (PoliceAnts.Count > i)
                        flag = threads.ContainsKey(PoliceAnts[i]);
                    else
                        flag = true;
                }
                if (!flag && IsAlive)
                {
                    SetPoliceAntAction(PoliceAnts[i]);
                    StartInsectAction(PoliceAnts[i]);
                }
            }
            int removeCount = PoliceAnts.RemoveAll(ant => !ant.State);
            policeAntsCount = newInsectCount - removeCount;
        }
        private void UpdateWorkerAnts()
        {
            int newInsectCount;
            lock (lockObject) { newInsectCount = WorkerAnts.Count; }
            for (int i = workerAntsCount; i < newInsectCount; i++)
            {
                bool flag;
                lock (lockObject) 
                {
                    if (WorkerAnts.Count > i)
                        flag = threads.ContainsKey(WorkerAnts[i]);
                    else
                        flag = true;
                }
                if (!flag && IsAlive)
                {
                    SetWorkerAntAction(WorkerAnts[i]);
                    StartInsectAction(WorkerAnts[i]);
                }
            }
            int removeCount = WorkerAnts.RemoveAll(ant => !ant.State);
            workerAntsCount = newInsectCount - removeCount;
        }
        private void UpdatePests()
        {
            int newPestsCount;
            lock (lockObject) { newPestsCount = Pests.Count; }
            for (int i = pestsCount; i < newPestsCount; i++)
            {
                bool flag;
                lock (lockObject) 
                { 
                    if (Pests.Count > i) 
                        flag = threads.ContainsKey(Pests[i]);
                    else
                        flag = true;
                }
                if (!flag && IsAlive)
                {
                    SetPestAction(Pests[i]);
                    StartInsectAction(Pests[i]);
                }
            }
            int removeCount;
            lock (lockObject) { removeCount = Pests.RemoveAll(pest => !pest.State); }
            pestsCount = newPestsCount - removeCount;
        }
        /**/


        /*блок методов, которые создают задачу для потока, в которой запускаются действия для конкретного насекомого*/
        public void SetLarvaAction(Larva larva)
        {
            lock (lockObject)
            {
                threads[larva] = new Thread(() => {
                    try
                    {
                        while (queen.State)
                            larva.Eat(foodStorage);
                    }
                    catch (DeadException)
                    {
                        LarvaDead();
                        InsectChanged(larva.GetType(), -1);
                    }
                });
            }
        }

        public void SetSoldierAntAction(SoldierAnt ant)
        {
            lock (lockObject)
            {
                threads[ant] = new Thread(() =>
                {
                    try
                    {
                        while (queen.State)
                        {
                            ant.Eat(foodStorage);
                            ant.Work(Pests, lockObject);
                            InsectChanged(new Pest().GetType(), -1);
                        }
                    }
                    catch (DeadException)
                    {
                        AntDead();
                        InsectChanged(ant.GetType(), -1);
                        InsectChanged(new Pest().GetType(), 1);
                    }
                });
            }
        }

        public void SetPoliceAntAction(PoliceAnt ant)
        {
            lock (lockObject)
            {
                threads[ant] = new Thread(() => {
                    try
                    {
                        while (queen.State && ant.State)
                        {
                            ant.Eat(foodStorage);
                            coefficient = ant.Work();
                        }
                    }
                    catch (DeadException)
                    {
                        AntDead();
                        InsectChanged(ant.GetType(), -1);
                        InsectChanged(new Pest().GetType(), 1);
                    }
                });
            }
        }
        public void SetWorkerAntAction(WorkerAnt ant)
        {
            lock (lockObject)
            {
                threads[ant] = new Thread(() => {
                    try
                    {
                        while (queen.State && ant.State)
                        {
                            ant.Eat(foodStorage);
                            ant.Work(foodStorage, coefficient);
                        }
                    }
                    catch (DeadException)
                    {
                        AntDead();
                        InsectChanged(ant.GetType(), -1);
                        InsectChanged(new Pest().GetType(), 1);
                    }
                });
            }
        }
        public void SetPestAction(Pest pest)
        {
            if (!threads.ContainsKey(pest))
                threads[pest] = new Thread(() => {
                    try
                    {
                        while (queen.State)
                            pest.Eat(foodStorage);
                    }
                    catch (DeadException)
                    {
                        InsectChanged(pest.GetType(), -1);
                    }
                });
        }
        private void QueenActions()
        {
            threads[queen] = new Thread(
                () => {
                    try
                    {
                        while (true)
                        {
                            queen.Eat(foodStorage);
                            int count = 0;
                            Type type = queen.Work(Larvae, SoldierAnts, PoliceAnts, WorkerAnts, lockObject, ref count);
                            InsectChanged((Type)new Larva().GetType(), count);
                            if (type != new object().GetType())
                                InsectChanged(type, 1);
                        }
                    }
                    catch (DeadException)
                    {
                        QueenDead();
                        InsectChanged(queen.GetType(), -1);
                    }
                });
            threads[queen].Start();
        }
        /**/


        /*блок методов, которые используются для запуска действий в муравейнике*/
        private void LarvaeActions()
        {
            int j;
            lock (lockObject) { j = larvaeCount; }
            for (int i = 0; i < j; ++i)
                if (Larvae[i].State)
                {
                    SetLarvaAction(Larvae[i]);
                    StartInsectAction(Larvae[i]);
                }
        }
        private void SoldierAntsActions()
        {
            int j;
            lock (lockObject) { j = soldierAntsCount; }
            for (int i = 0; i < j; ++i)
            {
                SoldierAnt ant = SoldierAnts[i];
                if (ant.State && !threads.ContainsKey(ant))
                {
                    SetSoldierAntAction(ant);
                    StartInsectAction(ant);
                }
            }
        }
        private void PoliceAntsActions()
        {
            int j;
            lock (lockObject) { j = policeAntsCount; }
            for (int i = 0; i < j; ++i)
            {
                PoliceAnt ant = PoliceAnts[i];
                if (ant.State)
                {
                    SetPoliceAntAction(ant);
                    StartInsectAction(ant);
                }
            }
        }
        private void WorkerAntsActions()
        {
            int j;
            lock (lockObject) { j = workerAntsCount; }
            for (int i = 0; i < j; ++i)
            {
                WorkerAnt ant = WorkerAnts[i];
                if (ant.State)
                {
                    SetWorkerAntAction(ant);
                    StartInsectAction(ant);
                }
            }
        }
        private void PestsActions()
        {
            int j;
            lock (lockObject) { j = pestsCount; }
            for (int i = 0; i < j; ++i)
            {
                Pest pest = Pests[i];
                if (pest.State)
                {
                    SetPestAction(pest);
                    StartInsectAction(pest);
                }
            }
        }

        //запуск потока действия для насекомого
        public void StartInsectAction(Insect insect)
        {
            if (threads.ContainsKey(insect) && !threads[insect].IsAlive)
                threads[insect].Start();
        }
    }
}
