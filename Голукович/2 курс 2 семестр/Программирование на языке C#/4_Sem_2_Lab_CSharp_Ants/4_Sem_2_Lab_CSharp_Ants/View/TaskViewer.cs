using System;
using System.Collections.Generic;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

namespace _4_Sem_2_Lab_CSharp_Ants.View
{
    //компонент View
    //класс объекта для отрисовки на форме(изображение, которое будет двигаться на windows-форме)
    public class TaskViewer
    {
        //название
        public string Name { get; private set; }
        //отрисовываемая картинка
        public PictureBox PictureBox { get; private set; }
        //отрисовываемый текст
        public TextBox TextBox { get; private set; }
        //координата начала движения
        private Point startPoint;
        //координата конца движения
        private Point finishPoint;
        //числовое значение
        private int val;
        //Свойство для значения
        public int Value { get { return val; } set { val = value; if (val == 0) MovingFlag = 0; } }
        //метод движения(задается во View(mainForm))
        public Action<Point> Move;
        //флаг движения
        //  1 - в движении
        //  0 - остановлен
        //  -1 - остановлен навсегда
        public int MovingFlag { get; set; }
        //метод вычисления пути перемещения, возвращает список точек для перемещения
        private List<Point> movingPath(int count)
        {
            List<Point> points = new List<Point>();
            int distanceX = finishPoint.X - startPoint.X;
            int distanceY = finishPoint.Y - startPoint.Y;
            var stepX = distanceX / (count + 1);
            var stepY = distanceY / (count + 1);
            for (int k = 1; k < count; ++k)
            {
                int x = startPoint.X + k * stepX;
                int y = startPoint.Y + k * stepY;
                points.Add(new Point(x, y));
            }
            return points;
        }
        //конструктор
        public TaskViewer(string filePath, string name, Point startPoint, Point finishPoint)
        {
            Name = name;
            Value = 0;
            MovingFlag = 0;
            this.startPoint = startPoint;
            this.finishPoint = finishPoint;
            //инициализация картинки
            PictureBox = new PictureBox();
            PictureBox.Visible = false;
            PictureBox.Image = Image.FromFile(filePath);
            PictureBox.Location = startPoint;
            PictureBox.Size = new Size(100, 100);
            PictureBox.SizeMode = PictureBoxSizeMode.StretchImage;
            PictureBox.BackColor = Color.Transparent;
            PictureBox.Visible = true;
            //инициализация текста
            TextBox = new TextBox();
            TextBox.Visible = false;
            TextBox.ReadOnly = true;
            TextBox.Size = new Size(100, 10);
            TextBox.Location = new Point(startPoint.X, startPoint.Y + 100);
            TextBox.Visible = true;
        }
        //метод движения по вычисленным координатам
        //движение по кругу: startPoint -> finishPoint -> startPoint
        public void Run()
        {
            MovingFlag = 1;
            var points = movingPath(99);
            int lastPointIndex = 0;
            while (MovingFlag != -1)
            {
                //цикл, ожидающий ненулевое значение
                while (Value == 0)
                {
                    if (MovingFlag != 1)
                        break;
                    else
                        Thread.Sleep(5);
                }
                while (MovingFlag == 1)
                {
                    //вычисление индекса точки начала движения
                    int i;
                    if (lastPointIndex < points.Count)
                        i = lastPointIndex;
                    else
                        i = points.Count * 2 - 1 - lastPointIndex;

                    //обновление значения в зависимости от флага
                    if (Value == 0)
                        MovingFlag = MovingFlag == -1 ? -1 : 0;
                    else
                        MovingFlag = MovingFlag == -1 ? -1 : 1;

                    //движение от первой точки(в начале движения - startPoint) до finishPoint
                    for (; i < points.Count && MovingFlag == 1; ++i, ++lastPointIndex)
                    {
                        lock (PictureBox)
                        {
                            if (MovingFlag == 1)
                            {
                                Point curPoint = points[i];
                                Move(curPoint);
                                Thread.Sleep(10);
                            }
                        }
                        //обновление значения в зависимости от флага
                        if (Value == 0)
                            MovingFlag = MovingFlag == -1 ? -1: 0;
                        else
                            MovingFlag = MovingFlag == -1 ? -1 : 1;
                    }

                    //обновление значения в зависимости от флага
                    if (Value == 0)
                        MovingFlag = MovingFlag == -1 ? -1 : 0;
                    else
                        MovingFlag = MovingFlag == -1 ? -1 : 1;

                    //движение от последней точки(в начале движения - finishPoint) до startPoint
                    for (i -= 1; i >= 0 && MovingFlag == 1 && Value != 0; --i, ++lastPointIndex)
                    {
                        lock (PictureBox)
                        {
                            if (MovingFlag == 1)
                            {
                                Point curPoint = points[i];
                                Move(curPoint);
                                Thread.Sleep(10);
                            }
                        }
                        //обновление значения в зависимости от флага
                        if (Value == 0)
                            MovingFlag = MovingFlag == -1 ? -1 : 0;
                        else
                            MovingFlag = MovingFlag == -1 ? -1 : 1;
                    }
                    //обновление значения в зависимости от флага
                    if (Value == 0)
                        MovingFlag = MovingFlag == -1 ? -1 : 0;
                    else
                        MovingFlag = MovingFlag == -1 ? -1 : 1;
                    lastPointIndex = 0;
                }
            }
        }
    }
}
