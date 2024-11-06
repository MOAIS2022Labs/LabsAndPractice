using Lab2;
using Lab2Construction.Model;

namespace Lab2Construction
{
    public class Controller
    {
        private MainForm form;
        private MyModel model;

        private List<PictureBox> workersPictureBoxes = new();
        private List<PictureBox> driversPictureBoxes = new();
        private Dictionary<Point, PictureBox> constructionPictureBoxes = new();

        private object workersLocker = new();
        private object driversLocker = new();
       
        public Controller(MainForm form)
        {
            this.form = form;
            model = new MyModel();

            // контроллер подписывается на события модели
            model.StaffDrawing += DrawStaff;
            model.ConstructionBuilding += ConstructionBuildingProcess;
            model.ConstructionDrawing += DrawConstruction;
            model.MoveToEvent += MoveStaff;

            // забираем из формы информацию о местоположении построек (вместе с PictureBox'ами для отрисовки)
            constructionPictureBoxes = form.Locations;

            // по завершении работы с формой (при её закрытии) отписываемся от событий модели
            form.FormClosed += (_, _) =>
            {
                model.StaffDrawing -= DrawStaff;
                model.ConstructionBuilding -= ConstructionBuildingProcess;
                model.ConstructionDrawing -= DrawConstruction;
                model.MoveToEvent -= MoveStaff;
            };

        }

        private void ConstructionBuildingProcess(Construction construction)
        {
            string path = "..\\..\\..\\Resources\\Building.gif"; // относительный путь до картинки
            // опрашиванием, имеется ли дескриптор для элемента управления, 
            // чтобы предотвратить попытку обращения к несуществующему дескриптору
            // (для предотвращения ошибки при закрытии формы через "крестик" при незавершившейся работе потоков
            if (form.IsHandleCreated) 
                // выполняет делегат в главном потоке, который создал элемент управления
                // нужно, потому что нельзя добавлять/изменять элементы управления формы не из потока, в котором они созданы
                // (а данный код будет выполняться в дочернем потоке). Аналогично в иных случаях использования BeginInvoke
                form.BeginInvoke(new Action(() => 
                {
                    constructionPictureBoxes[construction.Location].Image = Image.FromFile(path);
                    constructionPictureBoxes[construction.Location].Refresh();
                }));
        }

        // Запуск контроллера
        public void Start() => model.Build(form.Height, form.Locations.Keys.ToArray());

        // список точек, составляющих путь объекта
        private List<Point> GetWay(Point start, Point end)
        {
            List<Point> points = new();

            int distanceX = end.X - start.X;
            int distanceY = end.Y - start.Y;

            int count = (int)(Math.Sqrt(Math.Pow(distanceX, 2) + Math.Pow(distanceY, 2)) / 10);
            int stepX = distanceX / (count + 1);
            int stepY = distanceY / (count + 1);

            for (int j = 1; j <= count; j++)
            {
                int x = start.X + j * stepX;
                int y = start.Y + j * stepY;
                points.Add(new(x, y));
            }

            points.Add(end);
            return points;
        }

        // создание PictureBox'а с рабочим
        private void DrawStaff(Staff staff)
        {
            var pictureBox = new PictureBox
            {
                Location = staff.Location,
                SizeMode = PictureBoxSizeMode.StretchImage, // для подстраивания размера изображения под размер элемента управления
                BackColor = Color.Transparent, // для прозрачности *.png изображения
            };
            var rnd = new Random();
            if (staff is Driver)
            {
                pictureBox.Size = new Size(180, 130);
                string path = $"..\\..\\..\\Resources\\{staff.WorkWith.ToString()}Track.png"; // из файла по относительному пути
                pictureBox.Image = Image.FromFile(path);
                lock (driversLocker)
                {
                    driversPictureBoxes.Add(pictureBox);
                }
            }
            else
            {
                pictureBox.Size = new Size(50, 130);
                if (rnd.Next(1, 3) == 1)
                    pictureBox.Image = Properties.Resources.ravshan; // из файла ресурсов, лежащего в папке "Properties"
                                                                     // (туда добавлены используемые изображения)
                else
                    pictureBox.Image = Properties.Resources.jamshut;
                lock (workersLocker) // синхронизация доступа к разделяемому ресурсу
                {
                    workersPictureBoxes.Add(pictureBox);
                }
            }
            pictureBox.BringToFront();
            if (form.IsHandleCreated)
                form.BeginInvoke(new Action(() => form.AddControl(pictureBox)));

        }

        private void DrawConstruction(Construction construction)
        {
            string path = $"..\\..\\..\\Resources\\{construction.ToString()}.png";
            if (form.IsHandleCreated)
                form.BeginInvoke(new Action(() =>
                {
                    constructionPictureBoxes[construction.Location].Image = Image.FromFile(path);
                    constructionPictureBoxes[construction.Location].Refresh();
                }));
        }

        // Движение рабочего по форме
        private void MoveStaff(ref Staff staff, Point destination)
        {
            var points = GetWay(staff.Location, destination);
            PictureBox pictureBox = staff is Driver ? driversPictureBoxes[staff.Id] : workersPictureBoxes[staff.Id];
            
            foreach (var point in points)
            {
                if (form.IsHandleCreated)
                    form.BeginInvoke(new Action(() =>
                    {
                        pictureBox.Location = point;
                        pictureBox.BringToFront(); // вывод движущегося рабочего на передний план                        
                    }));
                Thread.Sleep(100);
            }

            staff.Location = destination;

            if (form.IsHandleCreated)
                form.BeginInvoke(new Action(() =>
                {
                    constructionPictureBoxes[destination].BringToFront(); // вывод постройки на передний план
                }));
        }
    }
}
