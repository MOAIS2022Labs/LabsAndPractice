using Lab1Tree;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BalancedTreeWinForm
{
    public partial class InputForm<T> : Form
    {
        public string[] Result { get; private set; }
        public InputForm(bool isMultipleValues = true)
        {
            InitializeComponent();
            if (!isMultipleValues)
            {
                textBoxInput.Multiline = false;
                this.Height -= 200;
                buttonOK.Location = new Point(28, 48);
                buttonCancel.Location = new Point(245, 48);
                MessageBox.Show("Введите значение нужного типа", "Ввод", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
                MessageBox.Show("Введите значения нужного типа. Каждое новое значение вводится с новой строки",
                    "Ввод", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void buttonCancel_MouseMove(object sender, MouseEventArgs e)
        {
            buttonCancel.BackColor = Color.IndianRed;
        }

        private void buttonCancel_MouseLeave(object sender, EventArgs e)
        {
            buttonCancel.BackColor = SystemColors.Control;
        }

        private void buttonOK_MouseLeave(object sender, EventArgs e)
        {
            buttonOK.BackColor = SystemColors.Control;
        }

        private void buttonOK_MouseMove(object sender, MouseEventArgs e)
        {
            buttonOK.BackColor = Color.LimeGreen;
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {            
            if (typeof(T) == typeof(int))
                Result = textBoxInput.Lines.Where(s => !String.IsNullOrWhiteSpace(s) && s[1..s.Length].Count(x => x == '-') < 1).ToArray();
            else
                Result = textBoxInput.Lines.Where(s => !String.IsNullOrWhiteSpace(s)).ToArray();
            DialogResult = DialogResult.OK;
        }

        private void textBoxInput_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (typeof(T) == typeof(int))
            {
                char number = e.KeyChar;
                if (!char.IsDigit(number) && number != 8 && number != 13 && number != '-')
                    e.Handled = true;
            }
        }
    }
}
