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
            this.buttonInfo = new System.Windows.Forms.Button();
            this.buttonLimits = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonStart
            // 
            this.buttonStart.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            this.buttonStart.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.buttonStart.Font = new System.Drawing.Font("Microsoft Sans Serif", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonStart.Location = new System.Drawing.Point(512, 12);
            this.buttonStart.Name = "buttonStart";
            this.buttonStart.Size = new System.Drawing.Size(139, 139);
            this.buttonStart.TabIndex = 0;
            this.buttonStart.Text = "Start";
            this.buttonStart.UseVisualStyleBackColor = false;
            this.buttonStart.Click += new System.EventHandler(this.buttonStart_Click);
            // 
            // richTextBoxProcesses
            // 
            this.richTextBoxProcesses.BackColor = System.Drawing.Color.White;
            this.richTextBoxProcesses.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.richTextBoxProcesses.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.richTextBoxProcesses.Location = new System.Drawing.Point(12, 12);
            this.richTextBoxProcesses.Name = "richTextBoxProcesses";
            this.richTextBoxProcesses.ReadOnly = true;
            this.richTextBoxProcesses.Size = new System.Drawing.Size(480, 490);
            this.richTextBoxProcesses.TabIndex = 1;
            this.richTextBoxProcesses.Text = "";
            this.richTextBoxProcesses.WordWrap = false;
            // 
            // buttonInfo
            // 
            this.buttonInfo.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(255)))));
            this.buttonInfo.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.buttonInfo.Font = new System.Drawing.Font("Microsoft Sans Serif", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonInfo.Location = new System.Drawing.Point(512, 187);
            this.buttonInfo.Name = "buttonInfo";
            this.buttonInfo.Size = new System.Drawing.Size(139, 139);
            this.buttonInfo.TabIndex = 2;
            this.buttonInfo.Text = "Info";
            this.buttonInfo.UseVisualStyleBackColor = false;
            this.buttonInfo.Click += new System.EventHandler(this.buttonInfo_Click);
            // 
            // buttonLimits
            // 
            this.buttonLimits.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(128)))));
            this.buttonLimits.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.buttonLimits.Font = new System.Drawing.Font("Microsoft Sans Serif", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonLimits.Location = new System.Drawing.Point(512, 363);
            this.buttonLimits.Name = "buttonLimits";
            this.buttonLimits.Size = new System.Drawing.Size(139, 139);
            this.buttonLimits.TabIndex = 5;
            this.buttonLimits.Text = "Set limits";
            this.buttonLimits.UseVisualStyleBackColor = false;
            this.buttonLimits.Click += new System.EventHandler(this.buttonLimits_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDark;
            this.ClientSize = new System.Drawing.Size(663, 514);
            this.Controls.Add(this.buttonLimits);
            this.Controls.Add(this.buttonInfo);
            this.Controls.Add(this.richTextBoxProcesses);
            this.Controls.Add(this.buttonStart);
            this.Name = "Form1";
            this.Text = "Form";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonStart;
        private System.Windows.Forms.RichTextBox richTextBoxProcesses;
        private System.Windows.Forms.Button buttonInfo;
        private System.Windows.Forms.Button buttonLimits;
    }
}

