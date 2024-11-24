using OS_Lab2.Service;
using System;
using System.Threading;
using System.Windows.Forms;
using static OS_Lab2.Service.FileService;

//задача 6

namespace OS_Lab2
{
    public partial class FileForm : Form
    {
        private Thread _firstCatalogThread;
        private Thread _secondCatalogThread;
        private Thread _mainThread;
        private bool _inWork = false;

        public FileForm()
        {
            InitializeComponent();
        }

        private void button_Check_Click(object sender, System.EventArgs e)
        {
            if (_inWork)
                return;

            string firstDirectoryPath = label_FirstPath.Text;
            string secondDirectoryPath = label_SecondPath.Text;

            if (firstDirectoryPath != "" && secondDirectoryPath != "")
            {
                if (firstDirectoryPath != secondDirectoryPath)
                {
                    WIN32_FIND_DATA?[] filesData = new WIN32_FIND_DATA?[2];
                    _firstCatalogThread = new Thread(() => 
                    {
                        try
                        {
                            FileService fileService = new FileService(firstDirectoryPath);
                            filesData[0] = fileService.FindFirstDatedFile();
                        }
                        catch(Exception exception)
                        {
                            BeginInvoke(new MethodInvoker(() => {
                                MessageBox.Show(exception.Message,
                                                "Исключение!",
                                                MessageBoxButtons.OK,
                                                MessageBoxIcon.Error);
                            }));
                            filesData[0] = null;
                        }
                    });
                    _secondCatalogThread = new Thread(() =>
                    {
                        try
                        {
                            FileService fileService = new FileService(secondDirectoryPath);
                            filesData[1] = fileService.FindFirstDatedFile();
                        }
                        catch (Exception exception)
                        {
                            BeginInvoke(new MethodInvoker(() => {
                                MessageBox.Show(exception.Message,
                                                "Исключение!",
                                                MessageBoxButtons.OK,
                                                MessageBoxIcon.Error);
                            }));
                            filesData[1] = null;
                        }
                    });

                    _mainThread = new Thread(() => 
                    {
                        _inWork = true;

                        _firstCatalogThread.Start();
                        _secondCatalogThread.Start();

                        _firstCatalogThread.Join();
                        _secondCatalogThread.Join();

                        if (filesData[0] != null && filesData[1] != null)
                        {
                            int result = FileService.CompareFileCreationDate((WIN32_FIND_DATA)filesData[0],
                                                                                (WIN32_FIND_DATA)filesData[1]);
                            if (result == 1)
                            {
                                MessageBox.Show($"Во втором каталоге есть файл \"{((WIN32_FIND_DATA)filesData[1]).cFileName}\" , "
                                            + "который был создан раньше любого из файлов в первом каталоге",
                                            "Результат",
                                            MessageBoxButtons.OK,
                                            MessageBoxIcon.Information);
                            }
                            else
                            {
                                MessageBox.Show("Во втором каталоге нет файлов, созданных раньше любых файлов в первом каталоге",
                                            "Результат",
                                            MessageBoxButtons.OK,
                                            MessageBoxIcon.Information);
                            }
                        }
                        else
                            MessageBox.Show("Невозможно провести сравнение, так как один или оба каталога пусты!",
                                            "Ошибка!",
                                            MessageBoxButtons.OK,
                                            MessageBoxIcon.Warning);
                        _inWork = false;
                    });
                    _mainThread.Start();
                }
                else
                    MessageBox.Show("Выбраны одинаковые каталоги!",
                                    "Ошибка!",
                                    MessageBoxButtons.OK, 
                                    MessageBoxIcon.Warning);
            }
            else
                MessageBox.Show("Каталог не выбран!", 
                                "Ошибка!",
                                MessageBoxButtons.OK, 
                                MessageBoxIcon.Warning);
        }

        private void labelFirstPath_Click(object sender, System.EventArgs e)
        {
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            dialog.ShowNewFolderButton = false;
            dialog.Description = "Выберите первый каталог:";
            if (dialog.ShowDialog() == DialogResult.OK)
                label_FirstPath.Text = dialog.SelectedPath;
        }

        private void labelSecondPath_Click(object sender, System.EventArgs e)
        {
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            dialog.ShowNewFolderButton = false;
            dialog.Description = "Выберите второй каталог:";
            if (dialog.ShowDialog() == DialogResult.OK)
                label_SecondPath.Text = dialog.SelectedPath;
        }

        private void FileForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (_mainThread != null)
                _mainThread.Join();
        }
    }
}
