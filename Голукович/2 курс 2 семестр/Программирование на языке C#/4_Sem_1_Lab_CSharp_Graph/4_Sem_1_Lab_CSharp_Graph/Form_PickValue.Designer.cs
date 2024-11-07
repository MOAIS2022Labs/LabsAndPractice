namespace _4_Sem_1_Lab_CSharp_Graph
{
    partial class Form_PickValue
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
            this.textBox_PickValue_Message = new System.Windows.Forms.TextBox();
            this.textBox_PickValue_Input = new System.Windows.Forms.TextBox();
            this.button_PickValue_OK = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // textBox_PickValue_Message
            // 
            this.textBox_PickValue_Message.ForeColor = System.Drawing.SystemColors.WindowText;
            this.textBox_PickValue_Message.Location = new System.Drawing.Point(12, 12);
            this.textBox_PickValue_Message.Multiline = true;
            this.textBox_PickValue_Message.Name = "textBox_PickValue_Message";
            this.textBox_PickValue_Message.ReadOnly = true;
            this.textBox_PickValue_Message.Size = new System.Drawing.Size(160, 69);
            this.textBox_PickValue_Message.TabIndex = 0;
            // 
            // textBox_PickValue_Input
            // 
            this.textBox_PickValue_Input.Location = new System.Drawing.Point(12, 87);
            this.textBox_PickValue_Input.Name = "textBox_PickValue_Input";
            this.textBox_PickValue_Input.Size = new System.Drawing.Size(160, 27);
            this.textBox_PickValue_Input.TabIndex = 1;
            this.textBox_PickValue_Input.TextChanged += new System.EventHandler(this.textBox_PickValue_Input_TextChanged);
            // 
            // button_PickValue_OK
            // 
            this.button_PickValue_OK.Location = new System.Drawing.Point(187, 12);
            this.button_PickValue_OK.Name = "button_PickValue_OK";
            this.button_PickValue_OK.Size = new System.Drawing.Size(69, 102);
            this.button_PickValue_OK.TabIndex = 2;
            this.button_PickValue_OK.Text = "OK";
            this.button_PickValue_OK.UseVisualStyleBackColor = true;
            this.button_PickValue_OK.Click += new System.EventHandler(this.button_PickValue_OK_Click);
            // 
            // Form_PickValue
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(268, 126);
            this.Controls.Add(this.button_PickValue_OK);
            this.Controls.Add(this.textBox_PickValue_Input);
            this.Controls.Add(this.textBox_PickValue_Message);
            this.Name = "Form_PickValue";
            this.Text = "Pick value";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private TextBox textBox_PickValue_Message;
        private TextBox textBox_PickValue_Input;
        private Button button_PickValue_OK;
    }
}