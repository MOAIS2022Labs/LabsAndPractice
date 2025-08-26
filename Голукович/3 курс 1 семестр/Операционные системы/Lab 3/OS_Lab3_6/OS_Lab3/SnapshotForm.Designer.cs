namespace OS_Lab3
{
    partial class SnapshotForm
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
            this.buttonStart = new System.Windows.Forms.Button();
            this.richTextBoxProcesses = new System.Windows.Forms.RichTextBox();
            this.textBoxN = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // buttonStart
            // 
            this.buttonStart.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonStart.Location = new System.Drawing.Point(12, 12);
            this.buttonStart.Name = "buttonStart";
            this.buttonStart.Size = new System.Drawing.Size(177, 63);
            this.buttonStart.TabIndex = 0;
            this.buttonStart.Text = "Запуск";
            this.buttonStart.UseVisualStyleBackColor = true;
            this.buttonStart.Click += new System.EventHandler(this.buttonStart_Click);
            // 
            // richTextBoxProcesses
            // 
            this.richTextBoxProcesses.Location = new System.Drawing.Point(11, 93);
            this.richTextBoxProcesses.Name = "richTextBoxProcesses";
            this.richTextBoxProcesses.Size = new System.Drawing.Size(577, 345);
            this.richTextBoxProcesses.TabIndex = 1;
            this.richTextBoxProcesses.Text = "";
            // 
            // textBoxN
            // 
            this.textBoxN.Location = new System.Drawing.Point(410, 53);
            this.textBoxN.Name = "textBoxN";
            this.textBoxN.Size = new System.Drawing.Size(178, 22);
            this.textBoxN.TabIndex = 2;
            // 
            // SnapshotForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(600, 450);
            this.Controls.Add(this.textBoxN);
            this.Controls.Add(this.richTextBoxProcesses);
            this.Controls.Add(this.buttonStart);
            this.Name = "SnapshotForm";
            this.Text = "SnapshotForm";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.SnapshotForm_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonStart;
        private System.Windows.Forms.RichTextBox richTextBoxProcesses;
        private System.Windows.Forms.TextBox textBoxN;
    }
}

