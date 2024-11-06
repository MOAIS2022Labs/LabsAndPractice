using Lab2;
using Lab2Construction.Model.Factories;
using System.Collections.Generic;
using System.Collections.ObjectModel;

/*
 * Канатников Максим 2 курс 9 группа
 * 3. Строительная фирма. Основные сущности: строящиеся объекты (дома, гаражи, квартиры), 
 * кадры (каменщики, плотники, маляры, водители, крановщики), стройматериалы (цемент, кирпич, плиты и т.д.). 
 * Смоделировать процесс строительства объектов.
 */

namespace Lab2Construction.Model
{
    public class MyModel
    {
        
        public delegate void MoveDelegate(ref Staff staff, Point point);
        // события — реализация шаблона "Наблюдатель" (подпись на события идёт в контроллере)
        public event MoveDelegate MoveToEvent; // событие передвижения рабочего на новую точку
        public event Action<Staff> StaffDrawing; // отрисовка рабочего на форме
        public event Action<Construction> ConstructionDrawing; // отрисовка постройки на форме
        public event Action<Construction> ConstructionBuilding; // отрисовка процесса строительства

        public MyModel()
        {
        }

        private const int NCONSTRUCTION = 3; // количество построек
        private readonly Thread[] _threads = new Thread[NCONSTRUCTION]; // массив потоков (1 поток — 1 строящийся объект)
        private readonly Dictionary<MaterialType, object> _lockers = new(); // синхронизация строений
                                                                            // на каждый тип материала есть по одному строителю и водителю
                                                                            // поэтому если они уже заняты строительством, поток с другим объектом
                                                                            // того же типа ждёт, пока рабочие освободятся
        private readonly Construction[] _constructions = new Construction[NCONSTRUCTION];
        private readonly Dictionary<MaterialType, Staff> _staffDict = new(); // строители, учавствующие в каком-то строительстве
        private readonly Dictionary<MaterialType, Staff> _driversDict = new(); // водители, учавствующие в каком-то строительстве

        private ConstructionFactory constructionFactory;
        private StaffFactory staffFactory;


        private void CreateStaff(Construction construction)
        {
            var driver = _driversDict[construction.MaterialType];
            var worker = _staffDict[construction.MaterialType];
            // выполнение делегата событий, если есть подписавшиеся
            StaffDrawing?.Invoke(driver); 
            StaffDrawing?.Invoke(worker);            
        }

        private void BuildingProcess(Construction construction)
        {
            lock (_lockers[construction.MaterialType]) // синхронизация строений      
            {
                var driver = _driversDict[construction.MaterialType];
                var worker = _staffDict[construction.MaterialType];
                
                MoveToEvent?.Invoke(ref driver, construction.Location);
                MoveToEvent?.Invoke(ref worker, construction.Location);

                ConstructionBuilding?.Invoke(construction);
                Thread.Sleep(5000); // симуляция процесса строительства

                ConstructionDrawing?.Invoke(construction);
            }
        }

        public void Build(int startPoint, Point[] buildLocations)
        {
            Random rnd = new Random();
            for (var i = 0; i < NCONSTRUCTION; ++i)
            {
                var type = (MaterialType)rnd.Next(1, NCONSTRUCTION + 1); 
                switch (type) // в зависимости от типа материала выбирается вид строения и какие рабочие участвуют в создании
                {
                    case MaterialType.Brick:
                        constructionFactory = new BrickHouseFactory(buildLocations[i]);
                        staffFactory = new BricklayerFactory(0, startPoint, _staffDict.Count);
                        break;
                    case MaterialType.Wood:
                        constructionFactory = new WoodHouseFactory(buildLocations[i]);
                        staffFactory = new WoodworkerFactory(0, startPoint, _staffDict.Count);
                        break;
                    case MaterialType.Steel:
                        constructionFactory = new GarageFactory(buildLocations[i]);
                        staffFactory = new SteelworkerFactory(0, startPoint, _staffDict.Count);
                        break;
                }
                var construction = constructionFactory.BuildConstruction();
                _constructions[i] = construction;
                if (!_lockers.ContainsKey(type)) // надо ли добавлять новые данные о рабочих, или с таким материалом уже работали?
                                                 // (если уже работали, то новые рабочие не появляются
                {
                    _lockers.Add(type, new object());
                    var staff = staffFactory.CreateStaff();
                   _staffDict.Add(type, staff);
                    staffFactory = new DriverFactory(0, startPoint, type, _driversDict.Count);
                    staff = staffFactory.CreateStaff();
                    _driversDict.Add(type, staff);
                }

                CreateStaff(construction); // создаётся нужный тип рабочих для объекта из данного материала

                _threads[i] = new Thread(() => BuildingProcess(construction)) // создание потока (процесс строительства)
                {
                    Name = $"Thread{i}"
                };
            }

            foreach (var t in _threads) // запуск потоков
                t.Start();
        }
    }
}
