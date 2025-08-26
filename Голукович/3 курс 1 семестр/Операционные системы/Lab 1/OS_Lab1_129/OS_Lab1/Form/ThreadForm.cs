using OS_Lab1.Model;

namespace OS_Lab1;

//задача 1.2.9 (стэк-семафоры/мютексы)

//делал для себя, поэтому комментов не будет)
public partial class ThreadForm : Form
{
    private ThreadService _service;

    public ThreadForm()
    {
        _service = new ThreadService(new(), new(), new() { });
        InitializeComponent();
    }

    private void startValuesInit(List<int> maxBufferSizes, List<int> tasksElemsCount)
    {
        (int, int) value;

        if (int.TryParse(textBox_0_bufferMaxSizeInput.Text, out value.Item1)
            && int.TryParse(textBox_0_tasksElemsCountInput.Text, out value.Item2)
            && value.Item1 > 0 && value.Item1 < 1000
            && value.Item2 > 0 && value.Item2 < 100)
        {
            maxBufferSizes[0] = value.Item1;
            tasksElemsCount[0] = value.Item2;
            this.label_0_buffer.BackColor = Color.White;
        }
        else
            this.label_0_buffer.BackColor = Color.Red;

        if (int.TryParse(textBox_1_bufferMaxSizeInput.Text, out value.Item1)
            && int.TryParse(textBox_1_tasksElemsCountInput.Text, out value.Item2)
            && value.Item1 > 0 && value.Item1 < 1000
            && value.Item2 > 0 && value.Item2 < 100)
        {
            maxBufferSizes[1] = value.Item1;
            tasksElemsCount[1] = value.Item2;
            this.label_1_buffer.BackColor = Color.White;
        }
        else
            this.label_1_buffer.BackColor = Color.Red;

        if (int.TryParse(textBox_2_bufferMaxSizeInput.Text, out value.Item1)
            && int.TryParse(textBox_2_tasksElemsCountInput.Text, out value.Item2)
            && value.Item1 > 0 && value.Item1 < 1000
            && value.Item2 > 0 && value.Item2 < 100)
        {
            maxBufferSizes[2] = value.Item1;
            tasksElemsCount[2] = value.Item2;
            this.label_2_buffer.BackColor = Color.White;
        }
        else
            this.label_2_buffer.BackColor = Color.Red;

        if (int.TryParse(textBox_3_bufferMaxSizeInput.Text, out value.Item1)
            && int.TryParse(textBox_3_tasksElemsCountInput.Text, out value.Item2)
            && value.Item1 > 0 && value.Item1 < 1000
            && value.Item2 > 0 && value.Item2 < 100)
        {
            maxBufferSizes[3] = value.Item1;
            tasksElemsCount[3] = value.Item2;
            this.label_3_buffer.BackColor = Color.White;
        }
        else
            this.label_3_buffer.BackColor = Color.Red;

        if (int.TryParse(textBox_4_bufferMaxSizeInput.Text, out value.Item1)
            && int.TryParse(textBox_4_tasksElemsCountInput.Text, out value.Item2)
            && value.Item1 > 0 && value.Item1 < 1000
            && value.Item2 > 0 && value.Item2 < 100)
        {
            maxBufferSizes[4] = value.Item1;
            tasksElemsCount[4] = value.Item2;
            this.label_4_buffer.BackColor = Color.White;
        }
        else
            this.label_4_buffer.BackColor = Color.Red;
    }

    private void button_start_Click(object sender, EventArgs e)
    {
        if (!_service.IsAlive)
        {
            List<int> maxBufferSizes = new() { -1, -1, -1, -1, -1 };
            List<int> tasksElemsCount = new() { -1, -1, -1, -1, -1 };
            List<bool> syncronizationData = new() { true, true, true, true, true };
            startValuesInit(maxBufferSizes, tasksElemsCount);

            _service = new ThreadService(
                maxBufferSizes,
                tasksElemsCount,
                new()
                {
                (
                    () => { this.label_0_buffer.BackColor = Color.Cyan; },
                    () => { this.label_0_buffer.BackColor = Color.LightGreen; },
                    () => { this.label_0_buffer.BackColor = Color.DarkOrange; },
                    () => { this.label_0_buffer.BackColor = Color.Red; }
                ),
                (
                    () => { this.label_1_buffer.BackColor = Color.Cyan; },
                    () => { this.label_1_buffer.BackColor = Color.LightGreen; },
                    () => { this.label_1_buffer.BackColor = Color.DarkOrange; },
                    () => { this.label_1_buffer.BackColor = Color.Red; }
                ),
                (
                    () => { this.label_2_buffer.BackColor = Color.Cyan; },
                    () => { this.label_2_buffer.BackColor = Color.LightGreen; },
                    () => { this.label_2_buffer.BackColor = Color.DarkOrange; },
                    () => { this.label_2_buffer.BackColor = Color.Red; }
                ),
                (
                    () => { this.label_3_buffer.BackColor = Color.Cyan; },
                    () => { this.label_3_buffer.BackColor = Color.LightGreen; },
                    () => { this.label_3_buffer.BackColor = Color.DarkOrange; },
                    () => { this.label_3_buffer.BackColor = Color.Red; }
                ),
                (
                    () => { this.label_4_buffer.BackColor = Color.Cyan; },
                    () => { this.label_4_buffer.BackColor = Color.LightGreen; },
                    () => { this.label_4_buffer.BackColor = Color.DarkOrange; },
                    () => { this.label_4_buffer.BackColor = Color.Red; }
                )
                });
            _service.SyncronizationData = syncronizationData;
            _service.WriteToOutput += (message) =>
            {
                BeginInvoke(new MethodInvoker(() =>
                {
                    this.richTextBox_tasksOutput.Text += message;
                    this.richTextBox_tasksOutput.Text += '\n';
                }));
            };
            _service.Start();
        }
    }

    private void button_info_Click(object sender, EventArgs e)
    {
        string information = "������� ����� � ��������� ������� �������"
            + " ��������� ���� ����� - ��������, ������� � ��������� ������� �������"
            + " ������� ������ �� ������� � ��������������� ����������, ���� ����� -"
            + " ��������, ������� � ��������� ������� ������� �������� ������ � ������"
            + "� �������� �� ����. ������ ���� �������� - �������� ���������� ���� ������.";

        MessageBox.Show(information, this.button_info.Text, MessageBoxButtons.OK, MessageBoxIcon.Information);
    }

    private void button_app_info_Click(object sender, EventArgs e)
    {
        string information = "����� ���� ��� ����� ������� - ������������ ���������� ��������� � �������.\n"
            + "������ ���� ��� ����� ������� - ���������� ��������� ��� ������ ������� ���������-���������.\n"
            + "\n������ - ��������� ������ ��������� ������.\n"
            + "\n������ ������ ����� �������� ���������:\n"
            + "����� - ������ ��������-�������� ��� �� ������ ������ � ��������;\n"
            + "����� - ������ ��������-�������� �������� � ��������;\n"
            + "������� - ������ ��������-�������� ��������� ������ � ��������;\n"
            + "��������� - ������ ��������-�������� ������������� ������ � ��������;\n"
            + "������� - ������ ��������-�������� �� ����� �������� � ��������;"
            + " (������� ������������ ������ ��� �������������).\n"
            + "\n��� ������� �� ������ ����������� ������������/������������� ������ ������� ��������-�������� � ��������.\n";

        MessageBox.Show(information, this.button_app_info.Text, MessageBoxButtons.OK, MessageBoxIcon.Information);
    }

    private void ThreadForm_FormClosing(object sender, FormClosingEventArgs e)
    {
        for (int i = 0; _service.SyncronizationData.Count > 0 && i < 5; ++i)
            _service.SyncronizationData[i] = true;
        _service.Join();
    }

    private void label_0_buffer_Click(object sender, EventArgs e)
    {
        if (this.label_0_buffer.BackColor == Color.Cyan && _service.SyncronizationData[0])
            _service.SyncronizationData[0] = false;
        else
            if (this.label_0_buffer.BackColor == Color.DarkOrange && !_service.SyncronizationData[0])
                _service.SyncronizationData[0] = true;
    }

    private void label_1_buffer_Click(object sender, EventArgs e)
    {
        if (this.label_1_buffer.BackColor == Color.Cyan && _service.SyncronizationData[1])
            _service.SyncronizationData[1] = false;
        else
            if (this.label_1_buffer.BackColor == Color.DarkOrange && !_service.SyncronizationData[1])
                _service.SyncronizationData[1] = true;
    }

    private void label_2_buffer_Click(object sender, EventArgs e)
    {
        if (this.label_2_buffer.BackColor == Color.Cyan && _service.SyncronizationData[2])
            _service.SyncronizationData[2] = false;
        else
            if (this.label_2_buffer.BackColor == Color.DarkOrange && !_service.SyncronizationData[2])
                _service.SyncronizationData[2] = true;
    }

    private void label_3_buffer_Click(object sender, EventArgs e)
    {
        if (this.label_3_buffer.BackColor == Color.Cyan && _service.SyncronizationData[3])
            _service.SyncronizationData[3] = false;
        else
            if (this.label_3_buffer.BackColor == Color.DarkOrange && !_service.SyncronizationData[3])
                _service.SyncronizationData[3] = true;
    }

    private void label_4_buffer_Click(object sender, EventArgs e)
    {
        if (this.label_4_buffer.BackColor == Color.Cyan && _service.SyncronizationData[4])
            _service.SyncronizationData[4] = false;
        else
            if (this.label_4_buffer.BackColor == Color.DarkOrange && !_service.SyncronizationData[4])
                _service.SyncronizationData[4] = true;
    }
}