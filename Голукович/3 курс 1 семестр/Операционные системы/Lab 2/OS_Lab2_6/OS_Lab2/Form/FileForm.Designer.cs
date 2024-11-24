namespace OS_Lab2
{
    partial class FileForm
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.button_Check = new System.Windows.Forms.Button();
            this.openFileDialog_First = new System.Windows.Forms.OpenFileDialog();
            this.openFileDialog_Second = new System.Windows.Forms.OpenFileDialog();
            this.label_FirstPath = new System.Windows.Forms.Label();
            this.label_SecondPath = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // button_Check
            // 
            this.button_Check.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.button_Check.Location = new System.Drawing.Point(647, 28);
            this.button_Check.Name = "button_Check";
            this.button_Check.Size = new System.Drawing.Size(141, 74);
            this.button_Check.TabIndex = 0;
            this.button_Check.Text = "Проверить";
            this.button_Check.UseVisualStyleBackColor = true;
            this.button_Check.Click += new System.EventHandler(this.button_Check_Click);
            // 
            // openFileDialog_First
            // 
            this.openFileDialog_First.CheckFileExists = false;
            this.openFileDialog_First.Title = "Выберите каталог";
            // 
            // openFileDialog_Second
            // 
            this.openFileDialog_Second.CheckFileExists = false;
            this.openFileDialog_Second.Title = "Выберите каталог";
            // 
            // label_FirstPath
            // 
            this.label_FirstPath.AutoSize = true;
            this.label_FirstPath.BackColor = System.Drawing.SystemColors.ControlDark;
            this.label_FirstPath.Location = new System.Drawing.Point(30, 28);
            this.label_FirstPath.Margin = new System.Windows.Forms.Padding(3, 3, 3, 0);
            this.label_FirstPath.MaximumSize = new System.Drawing.Size(580, 24);
            this.label_FirstPath.MinimumSize = new System.Drawing.Size(580, 24);
            this.label_FirstPath.Name = "label_FirstPath";
            this.label_FirstPath.Size = new System.Drawing.Size(580, 24);
            this.label_FirstPath.TabIndex = 1;
            this.label_FirstPath.Click += new System.EventHandler(this.labelFirstPath_Click);
            // 
            // label_SecondPath
            // 
            this.label_SecondPath.AutoSize = true;
            this.label_SecondPath.BackColor = System.Drawing.SystemColors.ControlDark;
            this.label_SecondPath.Location = new System.Drawing.Point(30, 78);
            this.label_SecondPath.MaximumSize = new System.Drawing.Size(580, 24);
            this.label_SecondPath.MinimumSize = new System.Drawing.Size(580, 24);
            this.label_SecondPath.Name = "label_SecondPath";
            this.label_SecondPath.Size = new System.Drawing.Size(580, 24);
            this.label_SecondPath.TabIndex = 2;
            this.label_SecondPath.Click += new System.EventHandler(this.labelSecondPath_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(30, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(70, 16);
            this.label1.TabIndex = 3;
            this.label1.Text = "Каталог 1";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(30, 60);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(70, 16);
            this.label2.TabIndex = 4;
            this.label2.Text = "Каталог 2";
            // 
            // FileForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 129);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label_SecondPath);
            this.Controls.Add(this.label_FirstPath);
            this.Controls.Add(this.button_Check);
            this.Name = "FileForm";
            this.Text = "FileForm";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FileForm_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button_Check;
        private System.Windows.Forms.OpenFileDialog openFileDialog_First;
        private System.Windows.Forms.OpenFileDialog openFileDialog_Second;
        private System.Windows.Forms.Label label_FirstPath;
        private System.Windows.Forms.Label label_SecondPath;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}

