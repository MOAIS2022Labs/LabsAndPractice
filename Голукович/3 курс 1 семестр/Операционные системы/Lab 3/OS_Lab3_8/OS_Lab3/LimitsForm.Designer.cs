namespace OS_Lab3
{
    partial class LimitsForm
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
            this.buttonOK = new System.Windows.Forms.Button();
            this.labelProcesses = new System.Windows.Forms.Label();
            this.labelHeaps = new System.Windows.Forms.Label();
            this.textBoxProcesses = new System.Windows.Forms.TextBox();
            this.textBoxHeaps = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // buttonOK
            // 
            this.buttonOK.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            this.buttonOK.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.buttonOK.Font = new System.Drawing.Font("Microsoft Sans Serif", 19.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonOK.Location = new System.Drawing.Point(12, 232);
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.Size = new System.Drawing.Size(215, 85);
            this.buttonOK.TabIndex = 0;
            this.buttonOK.Text = "OK";
            this.buttonOK.UseVisualStyleBackColor = false;
            this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
            // 
            // labelProcesses
            // 
            this.labelProcesses.AutoSize = true;
            this.labelProcesses.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelProcesses.Location = new System.Drawing.Point(57, 19);
            this.labelProcesses.Name = "labelProcesses";
            this.labelProcesses.Size = new System.Drawing.Size(127, 29);
            this.labelProcesses.TabIndex = 1;
            this.labelProcesses.Text = "Processes";
            this.labelProcesses.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // labelHeaps
            // 
            this.labelHeaps.AutoSize = true;
            this.labelHeaps.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelHeaps.Location = new System.Drawing.Point(75, 124);
            this.labelHeaps.Name = "labelHeaps";
            this.labelHeaps.Size = new System.Drawing.Size(83, 29);
            this.labelHeaps.TabIndex = 2;
            this.labelHeaps.Text = "Heaps";
            this.labelHeaps.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // textBoxProcesses
            // 
            this.textBoxProcesses.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.textBoxProcesses.Location = new System.Drawing.Point(12, 51);
            this.textBoxProcesses.Name = "textBoxProcesses";
            this.textBoxProcesses.Size = new System.Drawing.Size(215, 34);
            this.textBoxProcesses.TabIndex = 3;
            // 
            // textBoxHeaps
            // 
            this.textBoxHeaps.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.textBoxHeaps.Location = new System.Drawing.Point(12, 156);
            this.textBoxHeaps.Name = "textBoxHeaps";
            this.textBoxHeaps.Size = new System.Drawing.Size(215, 34);
            this.textBoxHeaps.TabIndex = 4;
            // 
            // LimitsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDark;
            this.ClientSize = new System.Drawing.Size(239, 331);
            this.Controls.Add(this.textBoxHeaps);
            this.Controls.Add(this.textBoxProcesses);
            this.Controls.Add(this.labelHeaps);
            this.Controls.Add(this.labelProcesses);
            this.Controls.Add(this.buttonOK);
            this.Name = "LimitsForm";
            this.Text = "LimitsForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonOK;
        private System.Windows.Forms.Label labelProcesses;
        private System.Windows.Forms.Label labelHeaps;
        public System.Windows.Forms.TextBox textBoxProcesses;
        public System.Windows.Forms.TextBox textBoxHeaps;
    }
}