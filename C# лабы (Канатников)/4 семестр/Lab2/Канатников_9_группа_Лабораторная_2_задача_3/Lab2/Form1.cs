using Lab2Construction;


namespace Lab2
{
    public partial class MainForm : Form
    {
        private Controller controller;
        public Dictionary<Point, PictureBox> Locations { get; private set; } = new(); // местоположение построек на форме

        public MainForm()
        {
            InitializeComponent();
        }

        public void AddControl(Control control) => Controls.Add(control);

        private void buttonStart_Click(object sender, EventArgs e)
        {
            buttonStart.Enabled = false;
            buttonStart.Visible = false;
            controller.Start();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            CenterToScreen();
            Locations.Add(pictureBox1.Location, pictureBox1);
            Locations.Add(pictureBox2.Location, pictureBox2);
            Locations.Add(pictureBox3.Location, pictureBox3);
            FormBorderStyle = FormBorderStyle.FixedSingle;
            controller = new Controller(this);

        }
    }
}
