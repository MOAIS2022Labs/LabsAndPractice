namespace OS_lab1
{
    partial class ThreadForm
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
            this.richTextBoxBuffer = new System.Windows.Forms.RichTextBox();
            this.richTextBoxThreads = new System.Windows.Forms.RichTextBox();
            this.textBoxBuffer = new System.Windows.Forms.TextBox();
            this.textBoxThread0 = new System.Windows.Forms.TextBox();
            this.textBoxThread1 = new System.Windows.Forms.TextBox();
            this.textBoxThread2 = new System.Windows.Forms.TextBox();
            this.textBoxThread3 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.buttonPause = new System.Windows.Forms.Button();
            this.buttonStart = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // richTextBoxBuffer
            // 
            this.richTextBoxBuffer.BackColor = System.Drawing.SystemColors.ControlLight;
            this.richTextBoxBuffer.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.richTextBoxBuffer.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.richTextBoxBuffer.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.richTextBoxBuffer.Location = new System.Drawing.Point(422, 97);
            this.richTextBoxBuffer.Name = "richTextBoxBuffer";
            this.richTextBoxBuffer.ReadOnly = true;
            this.richTextBoxBuffer.Size = new System.Drawing.Size(366, 303);
            this.richTextBoxBuffer.TabIndex = 0;
            this.richTextBoxBuffer.Text = "";
            // 
            // richTextBoxThreads
            // 
            this.richTextBoxThreads.BackColor = System.Drawing.SystemColors.ControlLight;
            this.richTextBoxThreads.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.richTextBoxThreads.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.richTextBoxThreads.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.richTextBoxThreads.Location = new System.Drawing.Point(12, 97);
            this.richTextBoxThreads.Name = "richTextBoxThreads";
            this.richTextBoxThreads.ReadOnly = true;
            this.richTextBoxThreads.Size = new System.Drawing.Size(366, 303);
            this.richTextBoxThreads.TabIndex = 1;
            this.richTextBoxThreads.Text = "";
            // 
            // textBoxBuffer
            // 
            this.textBoxBuffer.Location = new System.Drawing.Point(458, 69);
            this.textBoxBuffer.Name = "textBoxBuffer";
            this.textBoxBuffer.Size = new System.Drawing.Size(82, 22);
            this.textBoxBuffer.TabIndex = 2;
            // 
            // textBoxThread0
            // 
            this.textBoxThread0.Location = new System.Drawing.Point(38, 69);
            this.textBoxThread0.Name = "textBoxThread0";
            this.textBoxThread0.Size = new System.Drawing.Size(51, 22);
            this.textBoxThread0.TabIndex = 3;
            // 
            // textBoxThread1
            // 
            this.textBoxThread1.Location = new System.Drawing.Point(131, 68);
            this.textBoxThread1.Name = "textBoxThread1";
            this.textBoxThread1.Size = new System.Drawing.Size(51, 22);
            this.textBoxThread1.TabIndex = 4;
            // 
            // textBoxThread2
            // 
            this.textBoxThread2.Location = new System.Drawing.Point(234, 68);
            this.textBoxThread2.Name = "textBoxThread2";
            this.textBoxThread2.Size = new System.Drawing.Size(48, 22);
            this.textBoxThread2.TabIndex = 5;
            // 
            // textBoxThread3
            // 
            this.textBoxThread3.Location = new System.Drawing.Point(331, 69);
            this.textBoxThread3.Name = "textBoxThread3";
            this.textBoxThread3.Size = new System.Drawing.Size(47, 22);
            this.textBoxThread3.TabIndex = 6;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(9, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(369, 32);
            this.label1.TabIndex = 7;
            this.label1.Text = "Потоки читатели-писатели";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(416, 20);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(124, 32);
            this.label2.TabIndex = 8;
            this.label2.Text = "Буффер";
            this.label2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // buttonPause
            // 
            this.buttonPause.Location = new System.Drawing.Point(664, 20);
            this.buttonPause.Name = "buttonPause";
            this.buttonPause.Size = new System.Drawing.Size(124, 69);
            this.buttonPause.TabIndex = 9;
            this.buttonPause.Text = "Приостановить";
            this.buttonPause.UseVisualStyleBackColor = true;
            this.buttonPause.Click += new System.EventHandler(this.buttonPause_Click);
            // 
            // buttonStart
            // 
            this.buttonStart.Location = new System.Drawing.Point(558, 21);
            this.buttonStart.Name = "buttonStart";
            this.buttonStart.Size = new System.Drawing.Size(100, 69);
            this.buttonStart.TabIndex = 10;
            this.buttonStart.Text = "Запуск";
            this.buttonStart.UseVisualStyleBackColor = true;
            this.buttonStart.Click += new System.EventHandler(this.buttonStart_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(15, 72);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(17, 16);
            this.label3.TabIndex = 11;
            this.label3.Text = "R";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(108, 71);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(17, 16);
            this.label4.TabIndex = 12;
            this.label4.Text = "R";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(211, 71);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(20, 16);
            this.label5.TabIndex = 13;
            this.label5.Text = "W";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(305, 71);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(20, 16);
            this.label6.TabIndex = 14;
            this.label6.Text = "W";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(419, 71);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(33, 16);
            this.label7.TabIndex = 15;
            this.label7.Text = "Size";
            // 
            // ThreadForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 412);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.buttonStart);
            this.Controls.Add(this.buttonPause);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBoxThread3);
            this.Controls.Add(this.textBoxThread2);
            this.Controls.Add(this.textBoxThread1);
            this.Controls.Add(this.textBoxThread0);
            this.Controls.Add(this.textBoxBuffer);
            this.Controls.Add(this.richTextBoxThreads);
            this.Controls.Add(this.richTextBoxBuffer);
            this.Name = "ThreadForm";
            this.Text = "ThreadForm";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ThreadForm_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RichTextBox richTextBoxBuffer;
        private System.Windows.Forms.RichTextBox richTextBoxThreads;
        private System.Windows.Forms.TextBox textBoxBuffer;
        private System.Windows.Forms.TextBox textBoxThread0;
        private System.Windows.Forms.TextBox textBoxThread1;
        private System.Windows.Forms.TextBox textBoxThread2;
        private System.Windows.Forms.TextBox textBoxThread3;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button buttonPause;
        private System.Windows.Forms.Button buttonStart;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
    }
}

