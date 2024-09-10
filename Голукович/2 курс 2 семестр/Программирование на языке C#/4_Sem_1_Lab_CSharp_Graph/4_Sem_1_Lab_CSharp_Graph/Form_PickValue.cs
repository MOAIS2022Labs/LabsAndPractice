using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _4_Sem_1_Lab_CSharp_Graph
{
    public partial class Form_PickValue : Form
    {
        public string value;

        public Form_PickValue(string title, string message)
        {
            InitializeComponent();
            this.textBox_PickValue_Message.Text = message;
        }

        private void button_PickValue_OK_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void textBox_PickValue_Input_TextChanged(object sender, EventArgs e)
        {
            value = textBox_PickValue_Input.Text;
        }
    }
}
