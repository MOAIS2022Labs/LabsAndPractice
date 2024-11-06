namespace Lab5
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            txtInput1 = new TextBox();
            txtOutput = new TextBox();
            menuStrip1 = new MenuStrip();
            fileToolStripMenuItem = new ToolStripMenuItem();
            openToolStripMenuItem = new ToolStripMenuItem();
            file1ToolStripMenuItem = new ToolStripMenuItem();
            file2ToolStripMenuItem = new ToolStripMenuItem();
            saveToolStripMenuItem = new ToolStripMenuItem();
            inputToolStripMenuItem = new ToolStripMenuItem();
            input2ToolStripMenuItem1 = new ToolStripMenuItem();
            outputToolStripMenuItem = new ToolStripMenuItem();
            saveAsToolStripMenuItem = new ToolStripMenuItem();
            inputToolStripMenuItem1 = new ToolStripMenuItem();
            input2ToolStripMenuItem = new ToolStripMenuItem();
            outputToolStripMenuItem1 = new ToolStripMenuItem();
            projectToolStripMenuItem = new ToolStripMenuItem();
            taskToolStripMenuItem = new ToolStripMenuItem();
            clearToolStripMenuItem = new ToolStripMenuItem();
            clearInput1ToolStripMenuItem1 = new ToolStripMenuItem();
            clearInput2ToolStripMenuItem1 = new ToolStripMenuItem();
            clearOutputToolStripMenuItem1 = new ToolStripMenuItem();
            clearAllToolStripMenuItem = new ToolStripMenuItem();
            helpToolStripMenuItem = new ToolStripMenuItem();
            textBox3 = new TextBox();
            textBox4 = new TextBox();
            txtInput2 = new TextBox();
            textBox2 = new TextBox();
            menuStrip1.SuspendLayout();
            SuspendLayout();
            // 
            // txtInput1
            // 
            txtInput1.Location = new Point(37, 104);
            txtInput1.Margin = new Padding(3, 4, 3, 4);
            txtInput1.Multiline = true;
            txtInput1.Name = "txtInput1";
            txtInput1.ScrollBars = ScrollBars.Vertical;
            txtInput1.Size = new Size(234, 313);
            txtInput1.TabIndex = 1;
            // 
            // txtOutput
            // 
            txtOutput.Location = new Point(601, 104);
            txtOutput.Margin = new Padding(3, 4, 3, 4);
            txtOutput.Multiline = true;
            txtOutput.Name = "txtOutput";
            txtOutput.ScrollBars = ScrollBars.Vertical;
            txtOutput.Size = new Size(234, 313);
            txtOutput.TabIndex = 2;
            // 
            // menuStrip1
            // 
            menuStrip1.ImageScalingSize = new Size(20, 20);
            menuStrip1.Items.AddRange(new ToolStripItem[] { fileToolStripMenuItem, projectToolStripMenuItem, helpToolStripMenuItem });
            menuStrip1.Location = new Point(0, 0);
            menuStrip1.Name = "menuStrip1";
            menuStrip1.Padding = new Padding(7, 3, 0, 3);
            menuStrip1.Size = new Size(875, 30);
            menuStrip1.TabIndex = 3;
            menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            fileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { openToolStripMenuItem, saveToolStripMenuItem, saveAsToolStripMenuItem });
            fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            fileToolStripMenuItem.Size = new Size(46, 24);
            fileToolStripMenuItem.Text = "File";
            // 
            // openToolStripMenuItem
            // 
            openToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { file1ToolStripMenuItem, file2ToolStripMenuItem });
            openToolStripMenuItem.Name = "openToolStripMenuItem";
            openToolStripMenuItem.Size = new Size(224, 26);
            openToolStripMenuItem.Text = "Open";

            // 
            // file1ToolStripMenuItem
            // 
            file1ToolStripMenuItem.Name = "file1ToolStripMenuItem";
            file1ToolStripMenuItem.Size = new Size(224, 26);
            file1ToolStripMenuItem.Text = "File1";
            file1ToolStripMenuItem.Click += file1ToolStripMenuItem_Click;
            // 
            // file2ToolStripMenuItem
            // 
            file2ToolStripMenuItem.Name = "file2ToolStripMenuItem";
            file2ToolStripMenuItem.Size = new Size(224, 26);
            file2ToolStripMenuItem.Text = "File2";
            file2ToolStripMenuItem.Click += file2ToolStripMenuItem_Click;
            // 
            // saveToolStripMenuItem
            // 
            saveToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { inputToolStripMenuItem, input2ToolStripMenuItem1, outputToolStripMenuItem });
            saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            saveToolStripMenuItem.Size = new Size(224, 26);
            saveToolStripMenuItem.Text = "Save";
            // 
            // inputToolStripMenuItem
            // 
            inputToolStripMenuItem.Name = "inputToolStripMenuItem";
            inputToolStripMenuItem.Size = new Size(138, 26);
            inputToolStripMenuItem.Text = "Input1";
            inputToolStripMenuItem.Click += SaveInput1ToolStripMenuItem_Click;
            // 
            // input2ToolStripMenuItem1
            // 
            input2ToolStripMenuItem1.Name = "input2ToolStripMenuItem1";
            input2ToolStripMenuItem1.Size = new Size(138, 26);
            input2ToolStripMenuItem1.Text = "Input2";
            input2ToolStripMenuItem1.Click += SaveInput2ToolStripMenuItem1_Click;
            // 
            // outputToolStripMenuItem
            // 
            outputToolStripMenuItem.Name = "outputToolStripMenuItem";
            outputToolStripMenuItem.Size = new Size(138, 26);
            outputToolStripMenuItem.Text = "Output";
            outputToolStripMenuItem.Click += SaveOutputToolStripMenuItem_Click;
            // 
            // saveAsToolStripMenuItem
            // 
            saveAsToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { inputToolStripMenuItem1, input2ToolStripMenuItem, outputToolStripMenuItem1 });
            saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            saveAsToolStripMenuItem.Size = new Size(224, 26);
            saveAsToolStripMenuItem.Text = "Save as";
            // 
            // inputToolStripMenuItem1
            // 
            inputToolStripMenuItem1.Name = "inputToolStripMenuItem1";
            inputToolStripMenuItem1.Size = new Size(138, 26);
            inputToolStripMenuItem1.Text = "Input1";
            inputToolStripMenuItem1.Click += SaveAsInput1ToolStripMenuItem1_Click;
            // 
            // input2ToolStripMenuItem
            // 
            input2ToolStripMenuItem.Name = "input2ToolStripMenuItem";
            input2ToolStripMenuItem.Size = new Size(138, 26);
            input2ToolStripMenuItem.Text = "Input2";
            input2ToolStripMenuItem.Click += SaveAsInput2ToolStripMenuItem_Click;
            // 
            // outputToolStripMenuItem1
            // 
            outputToolStripMenuItem1.Name = "outputToolStripMenuItem1";
            outputToolStripMenuItem1.Size = new Size(138, 26);
            outputToolStripMenuItem1.Text = "Output";
            outputToolStripMenuItem1.Click += SaveAsOutputToolStripMenuItem1_Click;
            // 
            // projectToolStripMenuItem
            // 
            projectToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { taskToolStripMenuItem, clearToolStripMenuItem });
            projectToolStripMenuItem.Name = "projectToolStripMenuItem";
            projectToolStripMenuItem.Size = new Size(69, 24);
            projectToolStripMenuItem.Text = "Project";
            // 
            // taskToolStripMenuItem
            // 
            taskToolStripMenuItem.Name = "taskToolStripMenuItem";
            taskToolStripMenuItem.Size = new Size(126, 26);
            taskToolStripMenuItem.Text = "Task";
            taskToolStripMenuItem.Click += taskToolStripMenuItem_Click;
            // 
            // clearToolStripMenuItem
            // 
            clearToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { clearInput1ToolStripMenuItem1, clearInput2ToolStripMenuItem1, clearOutputToolStripMenuItem1, clearAllToolStripMenuItem });
            clearToolStripMenuItem.Name = "clearToolStripMenuItem";
            clearToolStripMenuItem.Size = new Size(126, 26);
            clearToolStripMenuItem.Text = "Clear";
            // 
            // clearInput1ToolStripMenuItem1
            // 
            clearInput1ToolStripMenuItem1.Name = "clearInput1ToolStripMenuItem1";
            clearInput1ToolStripMenuItem1.Size = new Size(138, 26);
            clearInput1ToolStripMenuItem1.Text = "Input1";
            clearInput1ToolStripMenuItem1.Click += clearInput1ToolStripMenuItem1_Click;
            // 
            // clearInput2ToolStripMenuItem1
            // 
            clearInput2ToolStripMenuItem1.Name = "clearInput2ToolStripMenuItem1";
            clearInput2ToolStripMenuItem1.Size = new Size(138, 26);
            clearInput2ToolStripMenuItem1.Text = "Input2";
            clearInput2ToolStripMenuItem1.Click += clearInput2ToolStripMenuItem1_Click;
            // 
            // clearOutputToolStripMenuItem1
            // 
            clearOutputToolStripMenuItem1.Name = "clearOutputToolStripMenuItem1";
            clearOutputToolStripMenuItem1.Size = new Size(138, 26);
            clearOutputToolStripMenuItem1.Text = "Output";
            clearOutputToolStripMenuItem1.Click += clearOutputToolStripMenuItem1_Click;
            // 
            // clearAllToolStripMenuItem
            // 
            clearAllToolStripMenuItem.Name = "clearAllToolStripMenuItem";
            clearAllToolStripMenuItem.Size = new Size(138, 26);
            clearAllToolStripMenuItem.Text = "All";
            clearAllToolStripMenuItem.Click += clearAllToolStripMenuItem_Click;
            // 
            // helpToolStripMenuItem
            // 
            helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            helpToolStripMenuItem.Size = new Size(55, 24);
            helpToolStripMenuItem.Text = "Help";
            helpToolStripMenuItem.Click += helpToolStripMenuItem_Click;
            // 
            // textBox3
            // 
            textBox3.BackColor = SystemColors.Control;
            textBox3.BorderStyle = BorderStyle.None;
            textBox3.Location = new Point(86, 75);
            textBox3.Margin = new Padding(3, 4, 3, 4);
            textBox3.Name = "textBox3";
            textBox3.Size = new Size(114, 20);
            textBox3.TabIndex = 4;
            textBox3.Text = "Input1";
            textBox3.TextAlign = HorizontalAlignment.Center;
            // 
            // textBox4
            // 
            textBox4.BackColor = SystemColors.Control;
            textBox4.BorderStyle = BorderStyle.None;
            textBox4.Location = new Point(665, 75);
            textBox4.Margin = new Padding(3, 4, 3, 4);
            textBox4.Name = "textBox4";
            textBox4.Size = new Size(114, 20);
            textBox4.TabIndex = 5;
            textBox4.Text = "Output";
            textBox4.TextAlign = HorizontalAlignment.Center;
            // 
            // txtInput2
            // 
            txtInput2.Location = new Point(319, 104);
            txtInput2.Margin = new Padding(3, 4, 3, 4);
            txtInput2.Multiline = true;
            txtInput2.Name = "txtInput2";
            txtInput2.ScrollBars = ScrollBars.Vertical;
            txtInput2.Size = new Size(234, 313);
            txtInput2.TabIndex = 6;
            // 
            // textBox2
            // 
            textBox2.BackColor = SystemColors.Control;
            textBox2.BorderStyle = BorderStyle.None;
            textBox2.Location = new Point(374, 75);
            textBox2.Margin = new Padding(3, 4, 3, 4);
            textBox2.Name = "textBox2";
            textBox2.Size = new Size(114, 20);
            textBox2.TabIndex = 7;
            textBox2.Text = "Input2";
            textBox2.TextAlign = HorizontalAlignment.Center;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(875, 533);
            Controls.Add(textBox2);
            Controls.Add(txtInput2);
            Controls.Add(textBox4);
            Controls.Add(textBox3);
            Controls.Add(txtOutput);
            Controls.Add(txtInput1);
            Controls.Add(menuStrip1);
            MainMenuStrip = menuStrip1;
            Margin = new Padding(3, 4, 3, 4);
            Name = "Form1";
            Text = "GUI-application";
            menuStrip1.ResumeLayout(false);
            menuStrip1.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private TextBox txtInput1;
        private TextBox txtOutput;
        private MenuStrip menuStrip1;
        private ToolStripMenuItem fileToolStripMenuItem;
        private ToolStripMenuItem projectToolStripMenuItem;
        private ToolStripMenuItem helpToolStripMenuItem;
        private TextBox textBox3;
        private TextBox textBox4;
        private ToolStripMenuItem taskToolStripMenuItem;
        private ToolStripMenuItem clearToolStripMenuItem;
        private ToolStripMenuItem openToolStripMenuItem;
        private ToolStripMenuItem saveToolStripMenuItem;
        private ToolStripMenuItem inputToolStripMenuItem;
        private ToolStripMenuItem outputToolStripMenuItem;
        private ToolStripMenuItem saveAsToolStripMenuItem;
        private ToolStripMenuItem inputToolStripMenuItem1;
        private ToolStripMenuItem outputToolStripMenuItem1;
        private TextBox txtInput2;
        private TextBox textBox2;
        private ToolStripMenuItem input2ToolStripMenuItem1;
        private ToolStripMenuItem input2ToolStripMenuItem;
        private ToolStripMenuItem clearInput1ToolStripMenuItem1;
        private ToolStripMenuItem clearInput2ToolStripMenuItem1;
        private ToolStripMenuItem clearOutputToolStripMenuItem1;
        private ToolStripMenuItem clearAllToolStripMenuItem;
        private ToolStripMenuItem file1ToolStripMenuItem;
        private ToolStripMenuItem file2ToolStripMenuItem;
    }
}