namespace Lab7
{
    partial class StudentForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            textBoxFIO = new TextBox();
            label1 = new Label();
            label2 = new Label();
            textBoxGroup = new TextBox();
            label3 = new Label();
            label4 = new Label();
            academPerfomanceGrid = new DataGridView();
            Column1 = new DataGridViewTextBoxColumn();
            Column2 = new DataGridViewTextBoxColumn();
            Column3 = new DataGridViewTextBoxColumn();
            Column4 = new DataGridViewTextBoxColumn();
            label5 = new Label();
            panel1 = new Panel();
            radioButton4 = new RadioButton();
            radioButton3 = new RadioButton();
            radioButton2 = new RadioButton();
            radioButton1 = new RadioButton();
            panel2 = new Panel();
            radioButtonContract = new RadioButton();
            radioButtonBudget = new RadioButton();
            saveButton = new Button();
            cancelButton = new Button();
            ((System.ComponentModel.ISupportInitialize)academPerfomanceGrid).BeginInit();
            panel1.SuspendLayout();
            panel2.SuspendLayout();
            SuspendLayout();
            // 
            // textBoxFIO
            // 
            textBoxFIO.Location = new Point(111, 33);
            textBoxFIO.Margin = new Padding(3, 4, 3, 4);
            textBoxFIO.Name = "textBoxFIO";
            textBoxFIO.Size = new Size(324, 27);
            textBoxFIO.TabIndex = 1;
            textBoxFIO.TextAlign = HorizontalAlignment.Center;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(240, 9);
            label1.Name = "label1";
            label1.Size = new Size(105, 20);
            label1.TabIndex = 0;
            label1.Text = "ФИО студента";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(14, 44);
            label2.Name = "label2";
            label2.Size = new Size(41, 20);
            label2.TabIndex = 3;
            label2.Text = "Курс";
            // 
            // textBoxGroup
            // 
            textBoxGroup.Location = new Point(522, 40);
            textBoxGroup.Margin = new Padding(3, 4, 3, 4);
            textBoxGroup.MaxLength = 2;
            textBoxGroup.Name = "textBoxGroup";
            textBoxGroup.Size = new Size(41, 27);
            textBoxGroup.TabIndex = 4;
            textBoxGroup.KeyPress += textBox1_KeyPress;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(442, 44);
            label3.Name = "label3";
            label3.Size = new Size(58, 20);
            label3.TabIndex = 5;
            label3.Text = "Группа";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(442, 84);
            label4.Name = "label4";
            label4.Size = new Size(76, 40);
            label4.TabIndex = 7;
            label4.Text = "Форма \r\nобучения";
            // 
            // academPerfomanceGrid
            // 
            academPerfomanceGrid.AllowUserToAddRows = false;
            academPerfomanceGrid.BackgroundColor = SystemColors.Control;
            academPerfomanceGrid.BorderStyle = BorderStyle.None;
            academPerfomanceGrid.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            academPerfomanceGrid.Columns.AddRange(new DataGridViewColumn[] { Column1, Column2, Column3, Column4 });
            academPerfomanceGrid.Location = new Point(14, 153);
            academPerfomanceGrid.Margin = new Padding(3, 4, 3, 4);
            academPerfomanceGrid.Name = "academPerfomanceGrid";
            academPerfomanceGrid.RowHeadersVisible = false;
            academPerfomanceGrid.RowHeadersWidth = 51;
            academPerfomanceGrid.RowTemplate.Height = 25;
            academPerfomanceGrid.ScrollBars = ScrollBars.Vertical;
            academPerfomanceGrid.SelectionMode = DataGridViewSelectionMode.CellSelect;
            academPerfomanceGrid.Size = new Size(605, 337);
            academPerfomanceGrid.TabIndex = 8;
            // 
            // Column1
            // 
            Column1.HeaderText = "№ курса";
            Column1.MinimumWidth = 6;
            Column1.Name = "Column1";
            Column1.ReadOnly = true;
            Column1.Width = 80;
            // 
            // Column2
            // 
            Column2.HeaderText = "№ сессии";
            Column2.MinimumWidth = 6;
            Column2.Name = "Column2";
            Column2.ReadOnly = true;
            Column2.Width = 80;
            // 
            // Column3
            // 
            Column3.HeaderText = "Название предмета";
            Column3.MinimumWidth = 6;
            Column3.Name = "Column3";
            Column3.Width = 370;
            // 
            // Column4
            // 
            Column4.HeaderText = "Оценка";
            Column4.MinimumWidth = 6;
            Column4.Name = "Column4";
            Column4.Width = 80;
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(240, 121);
            label5.Name = "label5";
            label5.Size = new Size(79, 20);
            label5.TabIndex = 9;
            label5.Text = "Экзамены";
            // 
            // panel1
            // 
            panel1.Controls.Add(radioButton4);
            panel1.Controls.Add(radioButton3);
            panel1.Controls.Add(radioButton2);
            panel1.Controls.Add(radioButton1);
            panel1.Location = new Point(58, 44);
            panel1.Margin = new Padding(3, 4, 3, 4);
            panel1.Name = "panel1";
            panel1.Size = new Size(46, 108);
            panel1.TabIndex = 10;
            // 
            // radioButton4
            // 
            radioButton4.AutoSize = true;
            radioButton4.Location = new Point(7, 80);
            radioButton4.Margin = new Padding(3, 4, 3, 4);
            radioButton4.Name = "radioButton4";
            radioButton4.Size = new Size(38, 24);
            radioButton4.TabIndex = 14;
            radioButton4.TabStop = true;
            radioButton4.Text = "4";
            radioButton4.UseVisualStyleBackColor = true;
            radioButton4.CheckedChanged += radioButton_CheckedChanged;
            // 
            // radioButton3
            // 
            radioButton3.AutoSize = true;
            radioButton3.Location = new Point(7, 55);
            radioButton3.Margin = new Padding(3, 4, 3, 4);
            radioButton3.Name = "radioButton3";
            radioButton3.Size = new Size(38, 24);
            radioButton3.TabIndex = 13;
            radioButton3.TabStop = true;
            radioButton3.Text = "3";
            radioButton3.UseVisualStyleBackColor = true;
            radioButton3.CheckedChanged += radioButton_CheckedChanged;
            // 
            // radioButton2
            // 
            radioButton2.AutoSize = true;
            radioButton2.Location = new Point(7, 29);
            radioButton2.Margin = new Padding(3, 4, 3, 4);
            radioButton2.Name = "radioButton2";
            radioButton2.Size = new Size(38, 24);
            radioButton2.TabIndex = 12;
            radioButton2.TabStop = true;
            radioButton2.Text = "2";
            radioButton2.UseVisualStyleBackColor = true;
            radioButton2.CheckedChanged += radioButton_CheckedChanged;
            // 
            // radioButton1
            // 
            radioButton1.AutoSize = true;
            radioButton1.Location = new Point(7, 4);
            radioButton1.Margin = new Padding(3, 4, 3, 4);
            radioButton1.Name = "radioButton1";
            radioButton1.Size = new Size(38, 24);
            radioButton1.TabIndex = 11;
            radioButton1.TabStop = true;
            radioButton1.Text = "1";
            radioButton1.UseVisualStyleBackColor = true;
            radioButton1.CheckedChanged += radioButton_CheckedChanged;
            // 
            // panel2
            // 
            panel2.Controls.Add(radioButtonContract);
            panel2.Controls.Add(radioButtonBudget);
            panel2.Location = new Point(518, 84);
            panel2.Margin = new Padding(3, 4, 3, 4);
            panel2.Name = "panel2";
            panel2.Size = new Size(101, 65);
            panel2.TabIndex = 11;
            // 
            // radioButtonContract
            // 
            radioButtonContract.AutoSize = true;
            radioButtonContract.Location = new Point(3, 37);
            radioButtonContract.Margin = new Padding(3, 4, 3, 4);
            radioButtonContract.Name = "radioButtonContract";
            radioButtonContract.Size = new Size(90, 24);
            radioButtonContract.TabIndex = 1;
            radioButtonContract.TabStop = true;
            radioButtonContract.Text = "Договор";
            radioButtonContract.UseVisualStyleBackColor = true;
            // 
            // radioButtonBudget
            // 
            radioButtonBudget.AutoSize = true;
            radioButtonBudget.Location = new Point(3, 4);
            radioButtonBudget.Margin = new Padding(3, 4, 3, 4);
            radioButtonBudget.Name = "radioButtonBudget";
            radioButtonBudget.Size = new Size(84, 24);
            radioButtonBudget.TabIndex = 0;
            radioButtonBudget.TabStop = true;
            radioButtonBudget.Text = "Бюджет";
            radioButtonBudget.UseVisualStyleBackColor = true;
            // 
            // saveButton
            // 
            saveButton.Location = new Point(18, 508);
            saveButton.Margin = new Padding(3, 4, 3, 4);
            saveButton.Name = "saveButton";
            saveButton.Size = new Size(93, 31);
            saveButton.TabIndex = 12;
            saveButton.Text = "Сохранить";
            saveButton.UseVisualStyleBackColor = true;
            saveButton.Click += saveButton_Click;
            // 
            // cancelButton
            // 
            cancelButton.Location = new Point(533, 508);
            cancelButton.Margin = new Padding(3, 4, 3, 4);
            cancelButton.Name = "cancelButton";
            cancelButton.Size = new Size(86, 31);
            cancelButton.TabIndex = 13;
            cancelButton.Text = "Отмена";
            cancelButton.UseVisualStyleBackColor = true;
            cancelButton.Click += cancelButton_Click;
            // 
            // StudentForm
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(647, 587);
            Controls.Add(cancelButton);
            Controls.Add(saveButton);
            Controls.Add(panel2);
            Controls.Add(panel1);
            Controls.Add(label5);
            Controls.Add(academPerfomanceGrid);
            Controls.Add(label4);
            Controls.Add(label3);
            Controls.Add(textBoxGroup);
            Controls.Add(label2);
            Controls.Add(textBoxFIO);
            Controls.Add(label1);
            Margin = new Padding(3, 4, 3, 4);
            Name = "StudentForm";
            Text = "Student Form";
            Load += StudentForm_Load;
            ((System.ComponentModel.ISupportInitialize)academPerfomanceGrid).EndInit();
            panel1.ResumeLayout(false);
            panel1.PerformLayout();
            panel2.ResumeLayout(false);
            panel2.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private TextBox textBoxFIO;
        private Label label2;
        private TextBox textBoxGroup;
        private Label label3;
        private Label label4;
        private DataGridView academPerfomanceGrid;
        private Label label5;
        private Panel panel1;
        private RadioButton radioButton4;
        private RadioButton radioButton3;
        private RadioButton radioButton2;
        private RadioButton radioButton1;
        private Panel panel2;
        private RadioButton radioButtonContract;
        private RadioButton radioButtonBudget;
        private Button saveButton;
        private Button cancelButton;
        private DataGridViewTextBoxColumn Column1;
        private DataGridViewTextBoxColumn Column2;
        private DataGridViewTextBoxColumn Column3;
        private DataGridViewTextBoxColumn Column4;
    }
}