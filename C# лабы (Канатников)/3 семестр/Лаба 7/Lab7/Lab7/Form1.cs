using System.Text;
using System.Windows.Forms;

namespace Lab7
{
    public partial class StudentsListForm : Form
    {
        public StudentsListForm()
        {
            InitializeComponent();
        }

        private int selectedNumber = -1;

        private AllStudents studentsList = new AllStudents();

        private string fileName = string.Empty;
        private enum FileType
        {
            None, Txt, Bin, Xml
        }

        private FileType fileType = FileType.None;

        private void helpToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Найти предметы, по которым нет неуспевающих.", "Условие задачи", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            listBoxSubjects.Items.Clear();
            studentsList = new AllStudents();
            var dlg = new OpenFileDialog();
            dlg.Filter = "Text (*.txt)|*.txt|Binary (*.bin)|*.bin|XML (*.xml)|*.xml";

            if (dlg.ShowDialog() == DialogResult.OK)
            {
                fileName = dlg.FileName;
                var extension = fileName.Substring(fileName.LastIndexOf("."));
                switch (extension)
                {
                    case ".txt":
                        fileType = FileType.Txt;
                        studentsList.OpenTxtFile(fileName);
                        ShowList();
                        break;

                    case ".bin":
                        fileType = FileType.Bin;
                        studentsList.OpenBinFile(fileName);
                        ShowList();
                        break;

                    case ".xml":
                        fileType = FileType.Xml;
                        studentsList.OpenXmlFile(fileName);
                        ShowList();
                        break;

                    default:
                        break;
                }
            }
        }

        private void ShowList(int index = 0)
        {
            var cnt = listBoxAllStudents.Items.Count;
            for (var i = cnt - 1; i >= index; --i)
            {
                listBoxAllStudents.Items.RemoveAt(i);
            }
            for (var i = index; i < studentsList.Students.Count; i++)
                listBoxAllStudents.Items.Add((i + 1).ToString() + ". " + studentsList.Students[i].ToListBox());
            listBoxAllStudents.Enabled = true;
        }

        private void createToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var dlg = new SaveFileDialog();
            dlg.DefaultExt = ".txt";
            studentsList = new AllStudents();
            fileName = String.Empty;
            if (dlg.ShowDialog() != DialogResult.Cancel)
            {
                fileName = dlg.FileName;
                StreamWriter f_out = new StreamWriter(fileName, false, Encoding.UTF8); ;
                f_out.Close();
                listBoxAllStudents.Items.Clear();
                MessageBox.Show("Файл успешно создан");
            }
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            switch (fileType)
            {
                case FileType.None:
                    //saveAsToolStripMenuItem_Click(sender, e);
                    createToolStripMenuItem_Click(sender, e);
                    break;

                case FileType.Txt:
                    studentsList.SaveTxtFile(fileName);
                    MessageBox.Show($"Файл {fileName.Substring(fileName.LastIndexOf("\\") + 1)} успешно сохранён");
                    break;

                case FileType.Xml:
                    studentsList.SaveXmlFile(fileName);
                    MessageBox.Show($"Файл {fileName.Substring(fileName.LastIndexOf("\\") + 1)} успешно сохранён");
                    break;

                case FileType.Bin:
                    studentsList.SaveBinFile(fileName);
                    MessageBox.Show($"Файл {fileName.Substring(fileName.LastIndexOf("\\") + 1)} успешно сохранён");
                    break;
            }
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var dlg = new SaveFileDialog();
            dlg.Filter = "Text (*.txt)|*.txt|Binary (*.bin)|*.bin|XML (*.xml)|*.xml";

            if (dlg.ShowDialog() == DialogResult.OK)
            {
                fileName = dlg.FileName;
                var extension = fileName.Substring(fileName.LastIndexOf("."));
                switch (extension)
                {
                    case ".txt":
                        fileType = FileType.Txt;
                        studentsList.SaveTxtFile(fileName);
                        break;

                    case ".bin":
                        fileType = FileType.Bin;
                        studentsList.SaveBinFile(fileName);
                        break;

                    case ".xml":
                        fileType = FileType.Xml;
                        studentsList.SaveXmlFile(fileName);
                        break;

                    default:
                        break;
                }
            }
        }

        private void taskToolStripMenuItem_Click(object sender, EventArgs e)
        {
            listBoxSubjects.Items.Clear();
            //if (fileType == FileType.None && selectedNumber == -1)
            //    MessageBox.Show("Файл не открыт.");
            //else
            if (listBoxAllStudents.Items.Count < 1)
                MessageBox.Show("Список пуст.");
            else
            {
                //var notBadSubjects = studentsList.ListOfSubjectsWithoutBadMarks();
                var notBadSubjects = studentsList.Task();
                if (notBadSubjects.Count == 0)
                    MessageBox.Show("Предметы без неуспевающих отсутствуют!");
                else
                {
                    for (var i = 0; i < notBadSubjects.Count; i++)
                        listBoxSubjects.Items.Add((i + 1).ToString() + ". " + notBadSubjects[i]);
                    listBoxSubjects.Enabled = true;
                }
            }
        }

        private void addStudentToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var form = new StudentForm();
            form.ShowDialog();         
            if (form.Changed)
            {
                studentsList.Students.Add(StudentForm.student);
                selectedNumber = studentsList.Students.Count - 1;
                listBoxAllStudents.Items.Add((selectedNumber + 1).ToString() + 
                    ". " + studentsList.Students[selectedNumber].ToListBox());
            }
            if (listBoxSubjects.Items.Count > 0)
                taskToolStripMenuItem_Click(sender, e);
        }

        private void listBoxAllStudents_SelectedIndexChanged(object sender, EventArgs e)
        {
            selectedNumber = listBoxAllStudents.SelectedIndex;
            if (selectedNumber >= 0)
            {
                var student = studentsList.Students[selectedNumber];
                var form = new StudentForm(student);
                form.ShowDialog();
                if (form.Changed)
                {
                    studentsList.Students[selectedNumber] = StudentForm.student;
                    ShowList(selectedNumber);
                }
                listBoxAllStudents.SelectedIndex = -1;
                if (listBoxSubjects.Items.Count > 0)
                    taskToolStripMenuItem_Click(sender, e);
            }
        }
        private void deleteStudentToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string s = showDeleteDialog("Выберите номер удаляемого студента", "Удаление");
            if (s != String.Empty)
            {
                int index = int.Parse(s) - 1;
                if (index < listBoxAllStudents.Items.Count && index >= 0)
                {
                    studentsList.Students.RemoveAt(index);
                    ShowList(index);
                    if (listBoxSubjects.Items.Count > 0)
                        taskToolStripMenuItem_Click(sender, e);
                }
                else
                    MessageBox.Show("Недопустимый номер студента", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        private static string showDeleteDialog(string message, string header)
        {
            Form formForDelete = new Form()
            {
                Width = 330,
                Height = 130,
                FormBorderStyle = FormBorderStyle.Fixed3D,
                Text = header,
                StartPosition = FormStartPosition.CenterScreen,
            };
            Label textLabel = new Label() { Left = 10, Top = 20, Text = message, Width = message.Length * 12 };
            TextBox textBox = new TextBox() { Left = 10, Top = 50, Width = 100 };
            Button confirmation = new Button() { Text = "OK", Left = 223, Width = 60, Top = 50, DialogResult = DialogResult.OK };
            textBox.KeyPress += (sender, e) =>
            {
                char number = e.KeyChar;
                if (number != 8 && !char.IsDigit(number))
                    e.Handled = true;
            };
            formForDelete.Controls.Add(textBox);
            formForDelete.Controls.Add(textLabel);
            formForDelete.Controls.Add(confirmation);
            formForDelete.AcceptButton = confirmation;//нажатие enter
            confirmation.Click += (sender, e) =>
            {
                formForDelete.Close();
            };
            return formForDelete.ShowDialog() == DialogResult.OK ? textBox.Text : "";
        }
    }
}