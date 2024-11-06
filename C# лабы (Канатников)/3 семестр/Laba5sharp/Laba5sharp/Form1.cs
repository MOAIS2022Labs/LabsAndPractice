using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace SharpLaba5
{
    public partial class Form1 : Form
    {
        static string FILENAME;
        string text = "";

        public Form1()
        {
            InitializeComponent();
            openFileDialog1.Filter = "Text files(*.txt)|*.txt|All files(*.*)|*.*";
            saveFileDialog1.Filter = "Text files(*.txt)|*.txt|All files(*.*)|*.*";
        }

        private void �������ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.Cancel)
                return;
            string filename = saveFileDialog1.FileName;
            MessageBox.Show("���� ������");
            StreamWriter File = new StreamWriter(filename, true);
            File.Write(text);
            File.Close();
        }

        private void �������ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.Cancel)
                return;
            FILENAME = openFileDialog1.FileName;
            string FileText = File.ReadAllText(FILENAME);
            textBox1.Text = FileText;
            textBox2.Clear();
        }

        private void ���������ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (FILENAME is null)
            {
                ������������ToolStripMenuItem_Click(sender, e);
            }
            else
            {
                using (StreamWriter outputFile = new StreamWriter(FILENAME))
                {
                    outputFile.WriteLine(textBox1.Text);
                }
                MessageBox.Show("���� ��������");
            }
        }

        private void ������������ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog SaveFileDialog1 = new SaveFileDialog();
            SaveFileDialog1.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
            if (SaveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                using (StreamWriter outputFile = new StreamWriter(SaveFileDialog1.FileName, false))
                {
                    outputFile.WriteLine(textBox1.Text);
                }
                MessageBox.Show("���� ��������");
            }
        }

        private void ���������ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string inputText = textBox1.Text;
            string[] words = inputText.Split(new char[] { ' ', '\n', '\r' }, StringSplitOptions.RemoveEmptyEntries);

            string forbiddenLetters = words[0];

            var filteredWords = words.Where(word => !word.Any(c => forbiddenLetters.Contains(c)));

            textBox2.Text = string.Join(" ", filteredWords);
            textBox2.Refresh();

            string outputFile = "output.txt";
            using (StreamWriter writer = new StreamWriter(outputFile))
            {
                writer.Write(string.Join(" ", filteredWords));
            }
        }

        private void ���������ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("��������� ���������");
            Close();
        }

        private void ��������ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            textBox1.Clear();
            textBox2.Clear();
        }

        private void ������ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("��� ��������� ����, ���������� �����, ����������� ����� ��� ����������� ���������." +
                " ������� ����� ����, �������� �� ���� ��������� ����� ��� �����, ������� ������� ���� �� ���� ����� �� ��������� ������");
        }

        private void ����ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}