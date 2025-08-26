using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using static OS_Lab3.SnapshotService;

//задача 8

namespace OS_Lab3
{
    public partial class SnapshotForm : Form
    {
        private Thread _mainTread;
        private int _processEntriesLimit = -1;
        private int _heapEntriesLimit = 500;
        public SnapshotForm()
        {
            InitializeComponent();
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            if (_mainTread != null && _mainTread.IsAlive)
                return;

            richTextBoxProcesses.Clear();
            Action mainThreadTask = () =>
            {
                try
                {
                    uint maxFreeHeapsSize = 0;
                    var result = new List<PROCESSENTRY32>();

                    var processesHeaps = SnapshotService.GetProcessesHeaps(_processEntriesLimit, _heapEntriesLimit);
                    foreach (var entry in processesHeaps)
                    {
                        string processEntryInfo = entry.Key.th32ProcessID + " | "
                            + entry.Key.cntThreads + " | "
                            + entry.Key.th32ParentProcessID + " | "
                            + entry.Key.szExeFile + " | "
                            + entry.Value + " bytes\n";

                        BeginInvoke(new MethodInvoker(() =>
                        {
                            richTextBoxProcesses.AppendText(processEntryInfo);
                        }));

                        if (result.Count == 0 || maxFreeHeapsSize == entry.Value)
                        {
                            result.Add(entry.Key);
                            maxFreeHeapsSize = entry.Value;
                        }
                        if (result.Count > 0 && maxFreeHeapsSize < entry.Value)
                        {
                            result.Clear();
                            result.Add(entry.Key);
                            maxFreeHeapsSize = entry.Value;
                        }
                    }
                    StringBuilder messageBuilder = new StringBuilder();
                    messageBuilder.AppendLine("Max free heap size: " + maxFreeHeapsSize + " bytes");
                    messageBuilder.AppendLine("Processes:");
                    foreach (var process in result)
                    {
                        messageBuilder.Append(process.th32ProcessID);
                        messageBuilder.Append(" | ");
                        messageBuilder.Append(process.cntThreads);
                        messageBuilder.Append(" | ");
                        messageBuilder.Append(process.th32ParentProcessID);
                        messageBuilder.Append(" | ");
                        messageBuilder.AppendLine(process.szExeFile);
                    }
                    MessageBox.Show(messageBuilder.ToString(), "Result", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message, "Excepiton!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                
            };
            _mainTread = new Thread(() => mainThreadTask());
            _mainTread.Start();
        }

        private void buttonInfo_Click(object sender, EventArgs e)
        {
            string message = "Вывести информацию о владельцах самого большого объема свободной памяти";
            MessageBox.Show(message, "Info", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (_mainTread != null)
                _mainTread.Join();
        }

        private void buttonLimits_Click(object sender, EventArgs e)
        {
            var limits = new LimitsForm();
            limits.ShowDialog();
            if (limits.DialogResult == DialogResult.OK)
            {
                int.TryParse(limits.textBoxProcesses.Text, out _processEntriesLimit);
                int.TryParse(limits.textBoxHeaps.Text, out _heapEntriesLimit);
            }
        }
    }
}
