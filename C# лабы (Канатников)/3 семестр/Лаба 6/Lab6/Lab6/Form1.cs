using System.Data;

namespace Lab6
{
    public partial class Form1 : Form
    {
        private int size;
        public Form1()
        {
            InitializeComponent();
        }
        // Условие
        private void button1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Добавить в конец строку, содержащую максимумы всех строк.", "Условие");
        }
        // Размер
        private void button2_Click(object sender, EventArgs e)
        {
            int i;
            if (textBox1.Text == "")
                size = 0;
            else
                try
                {
                    size = int.Parse(textBox1.Text);
                    DataTable matr = new DataTable("matrix");
                    DataColumn[] cols = new DataColumn[size];
                    for (i = 0; i < size; ++i)
                    {
                        cols[i] = new DataColumn(i.ToString());
                        matr.Columns.Add(cols[i]);
                    }
                    for (i = 0; i < size; ++i)
                    {
                        DataRow newRow = matr.NewRow();
                        matr.Rows.Add(newRow);
                    }
                    dataGridView1.DataSource = matr;
                    for (i = 0; i < size; i++)
                        dataGridView1.Columns[i].Width = 50;
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message, "Error!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }

        }
        // Добавить в конец строку, содержащую максимумы всех строк.
        private void button3_Click(object sender, EventArgs e)
        {
            Matrix matrix = new Matrix(size);
            if (matrix.GridToMatrix(dataGridView1))
            {
                matrix.Task();
                matrix.MatrixToGrid(dataGridView2);
            }
            else
                MessageBox.Show("Данные, введённые в матрицу, не корректны!", "Error!", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}