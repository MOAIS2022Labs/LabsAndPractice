using System;
using System.Windows.Forms;

namespace OS_Lab3
{
    public partial class LimitsForm : Form
    {
        public LimitsForm()
        {
            InitializeComponent();
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            Close();
        }
    }
}
