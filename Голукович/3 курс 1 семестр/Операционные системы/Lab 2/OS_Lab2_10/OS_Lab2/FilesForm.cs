using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using static OS_Lab2.FileService;

namespace OS_Lab2
{
    public partial class FilesForm : Form
    {
        //основной поток
        private Thread mainThread = null;
        //два доп потока для двух директорий
        private Thread firstThread = null;
        private Thread secondThread = null;

        public FilesForm()
        {
            InitializeComponent();
        }

        //кнопка старт
        private void button1_Click(object sender, EventArgs e)
        {
            //инициализируем заданные пути для потоков
            string path1 = label1.Text;
            string path2 = label2.Text;
            //проверяем валидность
            if (path1 == "" || path2 == "" || path1 == path2)
                return;


            //количество бла бла по задаче для первого каталога
            int firstCatalogResult = 0;
            //первый поток будет это считать
            firstThread = new Thread(() =>
            {
                FileService fs = new FileService();
                firstCatalogResult = fs.GetArchiveFilesCount(path1);
            });

            //количество бла бла по задаче для второго каталога
            int secondCatalogResult = 0;
            //второй поток будет это считать
            secondThread = new Thread(() =>
            {
                FileService fs = new FileService();
                secondCatalogResult = fs.GetArchiveFilesCount(path2);
            });

            //основной поток (чтобы вычисления были в отдельных потоках и не занимали саму форму)
            mainThread = new Thread(() =>
            {
                //тк могут падать ожидаемые исключения
                try
                {
                    //запускаем потоки
                    firstThread.Start();
                    secondThread.Start();

                    //ждем завершения
                    firstThread.Join();
                    secondThread.Join();

                    //по итогу вычислений показываем результат
                    if (firstCatalogResult > secondCatalogResult)
                    {
                        MessageBox.Show($"В первом каталоге архивных файлов больше: {firstCatalogResult} > {secondCatalogResult}",
                                        "Результат",
                                        MessageBoxButtons.OK,
                                        MessageBoxIcon.Information);
                    }
                    if (firstCatalogResult < secondCatalogResult)
                    {
                        MessageBox.Show($"Во втором каталоге архивных файлов больше: {firstCatalogResult} < {secondCatalogResult}",
                                        "Результат",
                                        MessageBoxButtons.OK,
                                        MessageBoxIcon.Information);
                    }
                    if (firstCatalogResult == secondCatalogResult)
                    {
                        MessageBox.Show($"В каталогах равное количество архивных файлов больше: {firstCatalogResult} = {secondCatalogResult}",
                                        "Результат",
                                        MessageBoxButtons.OK,
                                        MessageBoxIcon.Information);
                    }
                }
                //если выпала ошибка - говорим какая
                catch (Exception ex)
                {
                    MessageBox.Show($"Win32 error {ex.Message}",
                                        "Ошибка",
                                        MessageBoxButtons.OK,
                                        MessageBoxIcon.Warning);
                }
            });

            //запускаем основной поток
            mainThread.Start();
        }

        //нажатие на первый лейбл
        private void label1_Click(object sender, EventArgs e)
        {
            //создаем диалог для выбора каталога
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            //настраиваем
            dialog.ShowNewFolderButton = false;
            dialog.Description = "Выберите первый каталог:";
            //показываем и если результат ок - все круто, мы выбрали каталог
            if (dialog.ShowDialog() == DialogResult.OK)
                label1.Text = dialog.SelectedPath;
        }

        //нажатие на второй лейбл
        private void label2_Click(object sender, EventArgs e)
        {
            //создаем диалог для выбора каталога
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            //настраиваем
            dialog.ShowNewFolderButton = false;
            dialog.Description = "Выберите второй каталог:";
            //показываем и если результат ок - все круто, мы выбрали каталог
            if (dialog.ShowDialog() == DialogResult.OK)
                label2.Text = dialog.SelectedPath;
        }

        //когда форма закрывается
        private void FilesForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            //если поток существует и работает - ждем пока завершится
            if (mainThread != null && mainThread.IsAlive)
                mainThread.Join();
        }
    }
}
