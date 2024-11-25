namespace Lab1_OS
{
    partial class ThreadingForm
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
            this.startButton = new System.Windows.Forms.Button();
            this.firstBufferRichTextBox = new System.Windows.Forms.RichTextBox();
            this.secondBufferRichTextBox = new System.Windows.Forms.RichTextBox();
            this.infoButton = new System.Windows.Forms.Button();
            this.Writer1PauseButton = new System.Windows.Forms.Button();
            this.capacityFirstBufferTextBox = new System.Windows.Forms.TextBox();
            this.capacitySecondBufferTextBox = new System.Windows.Forms.TextBox();
            this.firstBufferLabel = new System.Windows.Forms.Label();
            this.secondBufferLabel = new System.Windows.Forms.Label();
            this.capacityFirstBufferLabel = new System.Windows.Forms.Label();
            this.capacitySecondBufferLabel = new System.Windows.Forms.Label();
            this.Reader1PauseButton = new System.Windows.Forms.Button();
            this.Writer2PauseButton = new System.Windows.Forms.Button();
            this.Reader2PauseButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // startButton
            // 
            this.startButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            this.startButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.startButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.startButton.Location = new System.Drawing.Point(995, 48);
            this.startButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.startButton.Name = "startButton";
            this.startButton.Size = new System.Drawing.Size(151, 145);
            this.startButton.TabIndex = 0;
            this.startButton.Text = "Старт";
            this.startButton.UseVisualStyleBackColor = false;
            this.startButton.Click += new System.EventHandler(this.startButton_Click);
            // 
            // firstBufferRichTextBox
            // 
            this.firstBufferRichTextBox.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.firstBufferRichTextBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.firstBufferRichTextBox.Location = new System.Drawing.Point(12, 146);
            this.firstBufferRichTextBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.firstBufferRichTextBox.Name = "firstBufferRichTextBox";
            this.firstBufferRichTextBox.ReadOnly = true;
            this.firstBufferRichTextBox.Size = new System.Drawing.Size(295, 293);
            this.firstBufferRichTextBox.TabIndex = 1;
            this.firstBufferRichTextBox.Text = "";
            // 
            // secondBufferRichTextBox
            // 
            this.secondBufferRichTextBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.secondBufferRichTextBox.Location = new System.Drawing.Point(493, 146);
            this.secondBufferRichTextBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.secondBufferRichTextBox.Name = "secondBufferRichTextBox";
            this.secondBufferRichTextBox.ReadOnly = true;
            this.secondBufferRichTextBox.Size = new System.Drawing.Size(295, 293);
            this.secondBufferRichTextBox.TabIndex = 2;
            this.secondBufferRichTextBox.Text = "";
            // 
            // infoButton
            // 
            this.infoButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(255)))));
            this.infoButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.infoButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.infoButton.Location = new System.Drawing.Point(995, 244);
            this.infoButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.infoButton.Name = "infoButton";
            this.infoButton.Size = new System.Drawing.Size(151, 145);
            this.infoButton.TabIndex = 3;
            this.infoButton.Text = "О лабе";
            this.infoButton.UseVisualStyleBackColor = false;
            this.infoButton.Click += new System.EventHandler(this.infoButton_Click);
            // 
            // Writer1PauseButton
            // 
            this.Writer1PauseButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(128)))));
            this.Writer1PauseButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Writer1PauseButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Writer1PauseButton.Location = new System.Drawing.Point(326, 146);
            this.Writer1PauseButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Writer1PauseButton.Name = "Writer1PauseButton";
            this.Writer1PauseButton.Size = new System.Drawing.Size(151, 101);
            this.Writer1PauseButton.TabIndex = 4;
            this.Writer1PauseButton.Text = "Приостановка писателя";
            this.Writer1PauseButton.UseVisualStyleBackColor = false;
            this.Writer1PauseButton.Click += new System.EventHandler(this.Writer1PauseButton_Click);
            // 
            // capacityFirstBufferTextBox
            // 
            this.capacityFirstBufferTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.capacityFirstBufferTextBox.Location = new System.Drawing.Point(83, 97);
            this.capacityFirstBufferTextBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.capacityFirstBufferTextBox.Name = "capacityFirstBufferTextBox";
            this.capacityFirstBufferTextBox.Size = new System.Drawing.Size(135, 30);
            this.capacityFirstBufferTextBox.TabIndex = 5;
            // 
            // capacitySecondBufferTextBox
            // 
            this.capacitySecondBufferTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.capacitySecondBufferTextBox.Location = new System.Drawing.Point(567, 97);
            this.capacitySecondBufferTextBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.capacitySecondBufferTextBox.Name = "capacitySecondBufferTextBox";
            this.capacitySecondBufferTextBox.Size = new System.Drawing.Size(135, 30);
            this.capacitySecondBufferTextBox.TabIndex = 7;
            // 
            // firstBufferLabel
            // 
            this.firstBufferLabel.AutoSize = true;
            this.firstBufferLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.firstBufferLabel.Location = new System.Drawing.Point(47, 9);
            this.firstBufferLabel.Name = "firstBufferLabel";
            this.firstBufferLabel.Size = new System.Drawing.Size(232, 32);
            this.firstBufferLabel.TabIndex = 9;
            this.firstBufferLabel.Text = "Первый буффер";
            // 
            // secondBufferLabel
            // 
            this.secondBufferLabel.AutoSize = true;
            this.secondBufferLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.secondBufferLabel.Location = new System.Drawing.Point(528, 9);
            this.secondBufferLabel.Name = "secondBufferLabel";
            this.secondBufferLabel.Size = new System.Drawing.Size(225, 32);
            this.secondBufferLabel.TabIndex = 10;
            this.secondBufferLabel.Text = "Второй буффер";
            // 
            // capacityFirstBufferLabel
            // 
            this.capacityFirstBufferLabel.AutoSize = true;
            this.capacityFirstBufferLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.capacityFirstBufferLabel.Location = new System.Drawing.Point(106, 70);
            this.capacityFirstBufferLabel.Name = "capacityFirstBufferLabel";
            this.capacityFirstBufferLabel.Size = new System.Drawing.Size(84, 25);
            this.capacityFirstBufferLabel.TabIndex = 11;
            this.capacityFirstBufferLabel.Text = "Размер";
            // 
            // capacitySecondBufferLabel
            // 
            this.capacitySecondBufferLabel.AutoSize = true;
            this.capacitySecondBufferLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.capacitySecondBufferLabel.Location = new System.Drawing.Point(587, 70);
            this.capacitySecondBufferLabel.Name = "capacitySecondBufferLabel";
            this.capacitySecondBufferLabel.Size = new System.Drawing.Size(84, 25);
            this.capacitySecondBufferLabel.TabIndex = 12;
            this.capacitySecondBufferLabel.Text = "Размер";
            // 
            // Reader1PauseButton
            // 
            this.Reader1PauseButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(128)))));
            this.Reader1PauseButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Reader1PauseButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Reader1PauseButton.Location = new System.Drawing.Point(326, 332);
            this.Reader1PauseButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Reader1PauseButton.Name = "Reader1PauseButton";
            this.Reader1PauseButton.Size = new System.Drawing.Size(151, 107);
            this.Reader1PauseButton.TabIndex = 15;
            this.Reader1PauseButton.Text = "Приостановка читателя";
            this.Reader1PauseButton.UseVisualStyleBackColor = false;
            this.Reader1PauseButton.Click += new System.EventHandler(this.Reader1PauseButton_Click);
            // 
            // Writer2PauseButton
            // 
            this.Writer2PauseButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(128)))));
            this.Writer2PauseButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Writer2PauseButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Writer2PauseButton.Location = new System.Drawing.Point(806, 146);
            this.Writer2PauseButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Writer2PauseButton.Name = "Writer2PauseButton";
            this.Writer2PauseButton.Size = new System.Drawing.Size(151, 101);
            this.Writer2PauseButton.TabIndex = 16;
            this.Writer2PauseButton.Text = "Приостановка писателя";
            this.Writer2PauseButton.UseVisualStyleBackColor = false;
            this.Writer2PauseButton.Click += new System.EventHandler(this.Writer2PauseButton_Click);
            // 
            // Reader2PauseButton
            // 
            this.Reader2PauseButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(128)))));
            this.Reader2PauseButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Reader2PauseButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.Reader2PauseButton.Location = new System.Drawing.Point(806, 332);
            this.Reader2PauseButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Reader2PauseButton.Name = "Reader2PauseButton";
            this.Reader2PauseButton.Size = new System.Drawing.Size(151, 107);
            this.Reader2PauseButton.TabIndex = 17;
            this.Reader2PauseButton.Text = "Приостановка читателя";
            this.Reader2PauseButton.UseVisualStyleBackColor = false;
            this.Reader2PauseButton.Click += new System.EventHandler(this.Reader2PauseButton_Click);
            // 
            // ThreadingForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlLight;
            this.ClientSize = new System.Drawing.Size(1172, 450);
            this.Controls.Add(this.Reader2PauseButton);
            this.Controls.Add(this.Writer2PauseButton);
            this.Controls.Add(this.Reader1PauseButton);
            this.Controls.Add(this.capacitySecondBufferLabel);
            this.Controls.Add(this.capacityFirstBufferLabel);
            this.Controls.Add(this.secondBufferLabel);
            this.Controls.Add(this.firstBufferLabel);
            this.Controls.Add(this.capacitySecondBufferTextBox);
            this.Controls.Add(this.capacityFirstBufferTextBox);
            this.Controls.Add(this.Writer1PauseButton);
            this.Controls.Add(this.infoButton);
            this.Controls.Add(this.secondBufferRichTextBox);
            this.Controls.Add(this.firstBufferRichTextBox);
            this.Controls.Add(this.startButton);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "ThreadingForm";
            this.Text = "ThreadingForm";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ThreadingForm_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button startButton;
        private System.Windows.Forms.RichTextBox firstBufferRichTextBox;
        private System.Windows.Forms.RichTextBox secondBufferRichTextBox;
        private System.Windows.Forms.Button infoButton;
        private System.Windows.Forms.Button Writer1PauseButton;
        private System.Windows.Forms.TextBox capacityFirstBufferTextBox;
        private System.Windows.Forms.TextBox capacitySecondBufferTextBox;
        private System.Windows.Forms.Label firstBufferLabel;
        private System.Windows.Forms.Label secondBufferLabel;
        private System.Windows.Forms.Label capacityFirstBufferLabel;
        private System.Windows.Forms.Label capacitySecondBufferLabel;
        private System.Windows.Forms.Button Reader1PauseButton;
        private System.Windows.Forms.Button Writer2PauseButton;
        private System.Windows.Forms.Button Reader2PauseButton;
    }
}

