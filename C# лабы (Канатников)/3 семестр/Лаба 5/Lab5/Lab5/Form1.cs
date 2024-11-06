using System.Text;

namespace Lab5
{
    public partial class Form1 : Form
    {
        private string fileName = "";

        public Form1()
        {
            InitializeComponent();
        }

        private void helpToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Даны 2 текстовых файла. Написать программу, " +
                 "которая сравнивала бы их на совпадение и выводила бы в качестве результата " +
                 "номер строки и номер символа, где встретилось первое отличие.", "Условие задачи");
        }
        private void file1ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "All Files|*.*|Text|*.txt";
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                fileName = dlg.FileName;
                using (var st = new StreamReader(fileName, Encoding.UTF8))
                {
                    txtInput1.Text = st.ReadToEnd();
                }
            }
        }

        private void file2ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "All Files|*.*|Text|*.txt";
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                fileName = dlg.FileName;
                using (var st = new StreamReader(fileName, Encoding.UTF8))
                {
                    txtInput2.Text = st.ReadToEnd();
                }
            }
        }

        private void SaveInput1ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (fileName != "")
            {
                using (var st = new StreamWriter(fileName, false, Encoding.UTF8))
                {
                    st.Write(txtInput1.Text);
                }
            }
            else
                SaveAsInput1ToolStripMenuItem1_Click(sender, e);
        }
        private void SaveInput2ToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (fileName != "")
            {
                using (var st = new StreamWriter(fileName, false, Encoding.UTF8))
                {
                    st.Write(txtInput1.Text);
                }
            }
            else
                SaveAsInput2ToolStripMenuItem_Click(sender, e);
        }

        private void SaveOutputToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (fileName != "")
            {
                using (var st = new StreamWriter(fileName, false, Encoding.UTF8))
                {
                    st.Write(txtOutput.Text);
                }
                MessageBox.Show($"Файл {fileName} успешно сохранён");
            }
            else
                SaveAsOutputToolStripMenuItem1_Click(sender, e);
        }

        private void SaveAsInput1ToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            var dlg = new SaveFileDialog();
            dlg.Filter = "All Files|*.*|Text|*.txt";
            dlg.DefaultExt = ".txt";
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                using (var st = new StreamWriter(dlg.FileName, false, Encoding.UTF8))
                {
                    st.Write(txtInput1.Text);
                }
            }
        }

        private void SaveAsInput2ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var dlg = new SaveFileDialog();
            dlg.Filter = "All Files|*.*|Text|*.txt";
            dlg.DefaultExt = ".txt";
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                using (var st = new StreamWriter(dlg.FileName, false, Encoding.UTF8))
                {
                    st.Write(txtInput1.Text);
                }
            }
        }

        private void SaveAsOutputToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            var dlg = new SaveFileDialog();
            dlg.Filter = "All Files|*.*|Text|*.txt";
            dlg.DefaultExt = ".txt";
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                using (var st = new StreamWriter(dlg.FileName, false, Encoding.UTF8))
                {
                    st.Write(txtOutput.Text);
                }
            }
        }

        private void clearInput1ToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            txtInput1.Clear();
        }

        private void clearInput2ToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            txtInput2.Clear();
        }

        private void clearOutputToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            txtOutput.Clear();
        }

        private void clearAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            txtOutput.Clear();
            txtInput1.Clear();
            txtInput2.Clear();
        }

        // проверить, отличаются ли файлы, и если да вывести с какой строки и с какого символа
        private void taskToolStripMenuItem_Click(object sender, EventArgs e)
        {
            txtOutput.Clear();
            string answer = "Файлы не отличаются";
            int countLines1 = txtInput1.Lines.Count();
            int countLines2 = txtInput2.Lines.Count();
            int countLinesMin = Math.Min(countLines1, countLines2);
            for (var i = 0; i < countLinesMin && answer == "Файлы не отличаются"; ++i)
            {
                string line1 = txtInput1.Lines[i].TrimEnd();
                string line2 = txtInput2.Lines[i].TrimEnd();
                if (!String.IsNullOrWhiteSpace(line1) && !String.IsNullOrWhiteSpace(line2))
                {
                    int minLength = Math.Min(line1.Length, line2.Length);
                    for (var j = 0; j < minLength && answer == "Файлы не отличаются"; ++j)
                    {
                        if (line1[j] != line2[j])
                            answer = $"line {i}, symbol {j}";
                    }
                    if (answer == "Файлы не отличаются" && line1.Length != line2.Length)
                    {
                        answer = $"line {i}, symbol {minLength}";
                    }
                }
                if (String.IsNullOrWhiteSpace(line1) && !String.IsNullOrWhiteSpace(line2) || !String.IsNullOrWhiteSpace(line1) && String.IsNullOrWhiteSpace(line2))
                    answer = $"line {i} symbol 0";
            }
            if (answer == "Файлы не отличаются")
            {
                if (countLines1 > countLines2)
                {
                    for (var i = countLinesMin; i < countLines1; ++i)
                        if (!String.IsNullOrWhiteSpace(txtInput1.Lines[i]))
                            answer = $"line {i}, symbol 0";
                }
                else
                    if (countLines1 < countLines2)
                    for (var i = countLinesMin; i < countLines1; ++i)
                        if (!String.IsNullOrWhiteSpace(txtInput2.Lines[i]))
                            answer = $"line {i}, symbol 0";
            }
            if (countLinesMin == 1)
            {
                var line1 = txtInput1.Lines[0].TrimEnd();
                var line2 = txtInput2.Lines[0].TrimEnd();
                int minLength = Math.Min(line1.Length, line2.Length);
                for (var i = 0; i < minLength && answer == "Файлы не отличаются"; ++i)
                {
                    if (line1[i] != line2[i])
                        answer = $"line 0, symbol {i}";
                }
            }
            txtOutput.Text = answer;
        }

       
    }
}