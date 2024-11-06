namespace ButtonCleacker
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            Text = "Task Resize Button";
            Size = new Size(200, 200);
            StartPosition = FormStartPosition.CenterScreen;
            BackColor = Color.White;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Random rand = new Random();
            int delta = rand.Next(10, 20);
            button1.Width += delta;
            button1.Height += delta;
            button1.Text = $"{button1.Width.ToString()} {button1.Height.ToString()}";
        }
    }
}