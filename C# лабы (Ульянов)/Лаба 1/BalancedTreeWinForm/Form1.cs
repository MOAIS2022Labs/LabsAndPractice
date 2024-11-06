using Lab1Tree;
using System.Text;

namespace BalancedTreeWinForm
{
    public partial class BalancedTreeForm : Form
    {
        private ITree<int> treeInt;
        private ITree<string> treeString;

        public enum Type { INT, STRING }
        public Type type;
        private enum Implementation { ARRAY, LINKED }
        private Implementation implementation;
        private void LockTreeOperations()
        {
            radioButtonMutable.Enabled = false;
            radioButtonUnmutable.Enabled = false;
            buttonInfo.Enabled = false;
            ��������ToolStripMenuItem.Enabled = false;
            ��������ToolStripMenuItem.Enabled = false;
            �������ToolStripMenuItem.Enabled = false;
            ������������ToolStripMenuItem.Enabled = false;
            �������ToolStripMenuItem.Enabled = false;
        }
        private void UnlockTreeOperations()
        {
            radioButtonMutable.Enabled = true;
            radioButtonUnmutable.Enabled = true;
            buttonInfo.Enabled = true;
            ��������ToolStripMenuItem.Enabled = true;
            ��������ToolStripMenuItem.Enabled = true;
            �������ToolStripMenuItem.Enabled = true;
            ������������ToolStripMenuItem.Enabled = true;
            �������ToolStripMenuItem.Enabled = true;
        }
        public BalancedTreeForm()
        {
            InitializeComponent();
            LockTreeOperations();
        }
        private void intLinkedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UnlockTreeOperations();
            type = Type.INT;
            implementation = Implementation.LINKED;
            treeInt = new LinkedTree<int>();
            textBoxVizualizer.Clear();
            radioButtonMutable.Checked = true;
            int�������ToolStripMenuItem.Enabled = true;
            string�������ToolStripMenuItem.Enabled = false;
        }

        private void stringLinkedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UnlockTreeOperations();
            type = Type.STRING;
            implementation = Implementation.LINKED;
            treeString = new LinkedTree<string>();
            textBoxVizualizer.Clear();
            radioButtonMutable.Checked = true;
            int�������ToolStripMenuItem.Enabled = false;
            string�������ToolStripMenuItem.Enabled = true;
        }

        private void intArrayToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UnlockTreeOperations();
            type = Type.INT;
            implementation = Implementation.ARRAY;
            treeInt = new ArrayTree<int>();
            textBoxVizualizer.Clear();
            radioButtonMutable.Checked = true;
            int�������ToolStripMenuItem.Enabled = true;
            string�������ToolStripMenuItem.Enabled = false;
        }

        private void stringArrayToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UnlockTreeOperations();
            type = Type.STRING;
            implementation = Implementation.ARRAY;
            treeString = new ArrayTree<string>();
            textBoxVizualizer.Clear();
            radioButtonMutable.Checked = true;
            int�������ToolStripMenuItem.Enabled = false;
            string�������ToolStripMenuItem.Enabled = true;
        }

        private void ��������ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                if (type == Type.INT)
                    treeInt.Clear();
                else
                    treeString.Clear();

                textBoxVizualizer.Clear();
            }
            catch (TreeException ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void ��������ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string[] input = Array.Empty<string>();
            if (type == Type.INT)
            {
                var inputForm = new InputForm<int>();
                if (inputForm.ShowDialog() == DialogResult.OK)
                    input = inputForm.Result;
                if (input.Length > 0)
                {
                    try
                    {
                        foreach (var val in input)
                            treeInt.Add(int.Parse(val));
                    }
                    catch (TreeException ex)
                    {
                        MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

                    }
                    textBoxVizualizer.Text = treeInt.ToString();
                }
            }
            else
            {
                var inputForm = new InputForm<string>();
                if (inputForm.ShowDialog() == DialogResult.OK)
                    input = inputForm.Result;
                if (input.Length > 0)
                {
                    try
                    {
                        foreach (var val in input)
                            treeString.Add(val);
                    }
                    catch (TreeException ex)
                    {
                        MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

                    }
                    textBoxVizualizer.Text = treeString.ToString();
                }
            }
        }

        private void �������ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string[] input = Array.Empty<string>();
            if (type == Type.INT)
            {
                var inputForm = new InputForm<int>();
                if (inputForm.ShowDialog() == DialogResult.OK)
                    input = inputForm.Result;
                if (input.Length > 0)
                {
                    try
                    {
                        foreach (var val in input)
                            treeInt.Remove(int.Parse(val));
                    }
                    catch (TreeException ex)
                    {
                        MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

                    }
                    textBoxVizualizer.Text = treeInt.ToString();
                }
            }
            else
            {
                var inputForm = new InputForm<string>();
                if (inputForm.ShowDialog() == DialogResult.OK)
                    input = inputForm.Result;
                if (input.Length > 0)
                {
                    try
                    {
                        foreach (var val in input)
                            treeString.Remove(val);
                    }
                    catch (TreeException ex)
                    {
                        MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

                    }
                    textBoxVizualizer.Text = treeString.ToString();
                }
            }
        }

        private void ������������ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string input = String.Empty;
            if (type == Type.INT)
            {
                var inputForm = new InputForm<int>(false);
                if (inputForm.ShowDialog() == DialogResult.OK)
                    input = inputForm.Result[0];
                if (input.Length > 0)
                {
                    try
                    {
                        MessageBox.Show($"������� {input} {(treeInt.Contains(int.Parse(input)) ? "" : "��")} ���������� � ������",
                            "Contains result", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                    catch (TreeException ex)
                    {
                        MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

                    }
                }
            }
            else
            {
                var inputForm = new InputForm<string>(false);
                if (inputForm.ShowDialog() == DialogResult.OK)
                    input = inputForm.Result[0];
                if (input.Length > 0)
                {
                    try
                    {
                        MessageBox.Show($"������� {input} {(treeString.Contains(input) ? "���������� � ������" : "�� ���������� � ������")}",
                            "Contains result", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                    catch (TreeException ex)
                    {
                        MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
            }
        }

        private void buttonInfo_Click(object sender, EventArgs e)
        {
            var sb = new StringBuilder();
            sb.Append((implementation == Implementation.LINKED ? "Linked" : "Array") + "Tree<");
            sb.AppendLine((type == Type.INT ? "int" : "string") + ">");
            sb.AppendLine(radioButtonMutable.Checked ? "����������" : "������������");
            sb.Append("���������� ���������: ");
            sb.AppendLine(type == Type.INT ? treeInt.Count.ToString() : treeString.Count.ToString());
            MessageBox.Show(sb.ToString(), "���������� � ������",
                MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void radioButtonMutable_CheckedChanged(object sender, EventArgs e)
        {
            if (!radioButtonMutable.Checked)
            {
                if (type == Type.INT)
                    treeInt = new UnmutableTree<int>(treeInt);
                else
                    treeString = new UnmutableTree<string>(treeString);
                radioButtonMutable.Enabled = false;
                radioButtonUnmutable.Enabled = false;
            }
        }

        private void buttonInfo_MouseMove(object sender, MouseEventArgs e)
        {
            buttonInfo.BackColor = Color.BlueViolet;
        }

        private void buttonInfo_MouseLeave(object sender, EventArgs e)
        {
            buttonInfo.BackColor = Color.PaleTurquoise;
        }

        private void ������������������ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                MessageBox.Show(TreeUtils<int>.Exists(treeInt, node => node.Value % 2 == 0) ? "����������" : "�� ����������",
                    "������ �����", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (TreeException ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void ������������������ToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            try
            {
                MessageBox.Show(TreeUtils<int>.FindAll(treeInt, node => (node.Value < 100 && node.Value > 9),
                    implementation == Implementation.ARRAY ? TreeUtils<int>.ArrayTreeConstructor : TreeUtils<int>.LinkedTreeConstructor).ToString(),
                    "��� ����������", MessageBoxButtons.OK);
            }
            catch (TreeException ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void �������������2����ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (radioButtonUnmutable.Checked)
            {
                MessageBox.Show("������� ForEach �� ����� �������� ���������� ������������� ������", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            TreeUtils<int>.ForEach(treeInt, node => node.Value *= 2);
            textBoxVizualizer.Text = treeInt.ToString();
        }

        private void ������������3ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                MessageBox.Show(TreeUtils<int>.CheckForAll(treeInt, node => node.Value % 3 == 0) ? "����� ��� ����" : "����� �� ��� ����",
                    "��� ������� �� 3", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (TreeException ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void ������������������������������������ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            TreeUtils<string>.CheckDelegate equalSymbols = node =>
            {
                var s = node.Value;
                for (int i = 0; i < s.Length - 1; ++i)
                    if (s[i] != s[i + 1])
                        return false;
                return true;
            };

            try
            {
                MessageBox.Show(TreeUtils<string>.Exists(treeString, equalSymbols) ? "����������" : "�� ����������",
                    "������ �� ���������� ��������", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (TreeException ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void �����������������������������������ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                MessageBox.Show(TreeUtils<string>.FindAll(treeString, node => (node.Value[0] >= 65 && node.Value[0] <=90),
                    implementation == Implementation.ARRAY ? TreeUtils<string>.ArrayTreeConstructor : TreeUtils<string>.LinkedTreeConstructor).ToString(),
                    "��� ������������ � ��������� ��������� �����", MessageBoxButtons.OK);
            }
            catch (TreeException ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void �����������������ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (radioButtonUnmutable.Checked)
            {
                MessageBox.Show("������� ForEach �� ����� �������� ���������� ������������� ������", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            TreeUtils<string>.ForEach(treeString, node => node.Value = new string(node.Value.Reverse().ToArray()));
            textBoxVizualizer.Text = treeString.ToString();
        }

        private void ����������������ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                MessageBox.Show(TreeUtils<string>.CheckForAll(treeString, node => node.Value.Length % 2 == 1) ? "����� ��� ����" : "����� �� ��� ����",
                    "��� �������� �����", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (TreeException ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
