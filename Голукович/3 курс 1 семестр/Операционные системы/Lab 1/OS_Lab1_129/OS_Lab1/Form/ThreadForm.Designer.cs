namespace OS_Lab1;

partial class ThreadForm
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
            this.richTextBox_tasksOutput = new System.Windows.Forms.RichTextBox();
            this.button_start = new System.Windows.Forms.Button();
            this.textBox_4_bufferMaxSizeInput = new System.Windows.Forms.TextBox();
            this.textBox_3_bufferMaxSizeInput = new System.Windows.Forms.TextBox();
            this.textBox_2_bufferMaxSizeInput = new System.Windows.Forms.TextBox();
            this.textBox_1_bufferMaxSizeInput = new System.Windows.Forms.TextBox();
            this.textBox_0_bufferMaxSizeInput = new System.Windows.Forms.TextBox();
            this.label_0_buffer = new System.Windows.Forms.Label();
            this.label_1_buffer = new System.Windows.Forms.Label();
            this.label_2_buffer = new System.Windows.Forms.Label();
            this.label_3_buffer = new System.Windows.Forms.Label();
            this.label_4_buffer = new System.Windows.Forms.Label();
            this.textBox_0_tasksElemsCountInput = new System.Windows.Forms.TextBox();
            this.textBox_1_tasksElemsCountInput = new System.Windows.Forms.TextBox();
            this.textBox_2_tasksElemsCountInput = new System.Windows.Forms.TextBox();
            this.textBox_3_tasksElemsCountInput = new System.Windows.Forms.TextBox();
            this.textBox_4_tasksElemsCountInput = new System.Windows.Forms.TextBox();
            this.button_info = new System.Windows.Forms.Button();
            this.button_app_info = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // richTextBox_tasksOutput
            // 
            this.richTextBox_tasksOutput.BackColor = System.Drawing.SystemColors.ControlDark;
            this.richTextBox_tasksOutput.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.richTextBox_tasksOutput.Location = new System.Drawing.Point(12, 96);
            this.richTextBox_tasksOutput.Name = "richTextBox_tasksOutput";
            this.richTextBox_tasksOutput.ReadOnly = true;
            this.richTextBox_tasksOutput.Size = new System.Drawing.Size(501, 475);
            this.richTextBox_tasksOutput.TabIndex = 11;
            this.richTextBox_tasksOutput.Text = "";
            // 
            // button_start
            // 
            this.button_start.BackColor = System.Drawing.Color.Green;
            this.button_start.FlatAppearance.BorderColor = System.Drawing.Color.Black;
            this.button_start.FlatAppearance.BorderSize = 0;
            this.button_start.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button_start.Location = new System.Drawing.Point(12, 20);
            this.button_start.Name = "button_start";
            this.button_start.Size = new System.Drawing.Size(114, 70);
            this.button_start.TabIndex = 12;
            this.button_start.Text = "Запуск";
            this.button_start.UseVisualStyleBackColor = false;
            this.button_start.Click += new System.EventHandler(this.button_start_Click);
            // 
            // textBox_4_bufferMaxSizeInput
            // 
            this.textBox_4_bufferMaxSizeInput.BackColor = System.Drawing.SystemColors.ControlDark;
            this.textBox_4_bufferMaxSizeInput.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox_4_bufferMaxSizeInput.Location = new System.Drawing.Point(535, 476);
            this.textBox_4_bufferMaxSizeInput.Name = "textBox_4_bufferMaxSizeInput";
            this.textBox_4_bufferMaxSizeInput.Size = new System.Drawing.Size(39, 27);
            this.textBox_4_bufferMaxSizeInput.TabIndex = 15;
            // 
            // textBox_3_bufferMaxSizeInput
            // 
            this.textBox_3_bufferMaxSizeInput.BackColor = System.Drawing.SystemColors.ControlDark;
            this.textBox_3_bufferMaxSizeInput.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox_3_bufferMaxSizeInput.Location = new System.Drawing.Point(535, 362);
            this.textBox_3_bufferMaxSizeInput.Name = "textBox_3_bufferMaxSizeInput";
            this.textBox_3_bufferMaxSizeInput.Size = new System.Drawing.Size(39, 27);
            this.textBox_3_bufferMaxSizeInput.TabIndex = 16;
            // 
            // textBox_2_bufferMaxSizeInput
            // 
            this.textBox_2_bufferMaxSizeInput.BackColor = System.Drawing.SystemColors.ControlDark;
            this.textBox_2_bufferMaxSizeInput.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox_2_bufferMaxSizeInput.Location = new System.Drawing.Point(535, 248);
            this.textBox_2_bufferMaxSizeInput.Name = "textBox_2_bufferMaxSizeInput";
            this.textBox_2_bufferMaxSizeInput.Size = new System.Drawing.Size(39, 27);
            this.textBox_2_bufferMaxSizeInput.TabIndex = 17;
            // 
            // textBox_1_bufferMaxSizeInput
            // 
            this.textBox_1_bufferMaxSizeInput.BackColor = System.Drawing.SystemColors.ControlDark;
            this.textBox_1_bufferMaxSizeInput.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox_1_bufferMaxSizeInput.Location = new System.Drawing.Point(535, 134);
            this.textBox_1_bufferMaxSizeInput.Name = "textBox_1_bufferMaxSizeInput";
            this.textBox_1_bufferMaxSizeInput.Size = new System.Drawing.Size(39, 27);
            this.textBox_1_bufferMaxSizeInput.TabIndex = 18;
            // 
            // textBox_0_bufferMaxSizeInput
            // 
            this.textBox_0_bufferMaxSizeInput.BackColor = System.Drawing.SystemColors.ControlDark;
            this.textBox_0_bufferMaxSizeInput.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox_0_bufferMaxSizeInput.Location = new System.Drawing.Point(535, 20);
            this.textBox_0_bufferMaxSizeInput.Name = "textBox_0_bufferMaxSizeInput";
            this.textBox_0_bufferMaxSizeInput.Size = new System.Drawing.Size(39, 27);
            this.textBox_0_bufferMaxSizeInput.TabIndex = 19;
            // 
            // label_0_buffer
            // 
            this.label_0_buffer.AutoSize = true;
            this.label_0_buffer.BackColor = System.Drawing.Color.Red;
            this.label_0_buffer.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label_0_buffer.Location = new System.Drawing.Point(535, 54);
            this.label_0_buffer.MinimumSize = new System.Drawing.Size(78, 62);
            this.label_0_buffer.Name = "label_0_buffer";
            this.label_0_buffer.Size = new System.Drawing.Size(78, 62);
            this.label_0_buffer.TabIndex = 20;
            this.label_0_buffer.Text = "Буффер 0";
            this.label_0_buffer.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label_0_buffer.Click += new System.EventHandler(this.label_0_buffer_Click);
            // 
            // label_1_buffer
            // 
            this.label_1_buffer.AutoSize = true;
            this.label_1_buffer.BackColor = System.Drawing.Color.Red;
            this.label_1_buffer.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label_1_buffer.Location = new System.Drawing.Point(535, 168);
            this.label_1_buffer.MinimumSize = new System.Drawing.Size(78, 62);
            this.label_1_buffer.Name = "label_1_buffer";
            this.label_1_buffer.Size = new System.Drawing.Size(78, 62);
            this.label_1_buffer.TabIndex = 21;
            this.label_1_buffer.Text = "Буффер 1";
            this.label_1_buffer.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label_1_buffer.Click += new System.EventHandler(this.label_1_buffer_Click);
            // 
            // label_2_buffer
            // 
            this.label_2_buffer.AutoSize = true;
            this.label_2_buffer.BackColor = System.Drawing.Color.Red;
            this.label_2_buffer.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label_2_buffer.Location = new System.Drawing.Point(535, 282);
            this.label_2_buffer.MinimumSize = new System.Drawing.Size(78, 62);
            this.label_2_buffer.Name = "label_2_buffer";
            this.label_2_buffer.Size = new System.Drawing.Size(78, 62);
            this.label_2_buffer.TabIndex = 22;
            this.label_2_buffer.Text = "Буффер 2";
            this.label_2_buffer.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label_2_buffer.Click += new System.EventHandler(this.label_2_buffer_Click);
            // 
            // label_3_buffer
            // 
            this.label_3_buffer.AutoSize = true;
            this.label_3_buffer.BackColor = System.Drawing.Color.Red;
            this.label_3_buffer.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label_3_buffer.Location = new System.Drawing.Point(535, 396);
            this.label_3_buffer.MinimumSize = new System.Drawing.Size(78, 62);
            this.label_3_buffer.Name = "label_3_buffer";
            this.label_3_buffer.Size = new System.Drawing.Size(78, 62);
            this.label_3_buffer.TabIndex = 23;
            this.label_3_buffer.Text = "Буффер 3";
            this.label_3_buffer.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label_3_buffer.Click += new System.EventHandler(this.label_3_buffer_Click);
            // 
            // label_4_buffer
            // 
            this.label_4_buffer.AutoSize = true;
            this.label_4_buffer.BackColor = System.Drawing.Color.Red;
            this.label_4_buffer.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label_4_buffer.Location = new System.Drawing.Point(535, 510);
            this.label_4_buffer.MinimumSize = new System.Drawing.Size(78, 62);
            this.label_4_buffer.Name = "label_4_buffer";
            this.label_4_buffer.Size = new System.Drawing.Size(78, 62);
            this.label_4_buffer.TabIndex = 24;
            this.label_4_buffer.Text = "Буффер 4";
            this.label_4_buffer.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label_4_buffer.Click += new System.EventHandler(this.label_4_buffer_Click);
            // 
            // textBox_0_tasksElemsCountInput
            // 
            this.textBox_0_tasksElemsCountInput.BackColor = System.Drawing.SystemColors.ControlDark;
            this.textBox_0_tasksElemsCountInput.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox_0_tasksElemsCountInput.Location = new System.Drawing.Point(574, 20);
            this.textBox_0_tasksElemsCountInput.Name = "textBox_0_tasksElemsCountInput";
            this.textBox_0_tasksElemsCountInput.Size = new System.Drawing.Size(39, 27);
            this.textBox_0_tasksElemsCountInput.TabIndex = 25;
            // 
            // textBox_1_tasksElemsCountInput
            // 
            this.textBox_1_tasksElemsCountInput.BackColor = System.Drawing.SystemColors.ControlDark;
            this.textBox_1_tasksElemsCountInput.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox_1_tasksElemsCountInput.Location = new System.Drawing.Point(574, 134);
            this.textBox_1_tasksElemsCountInput.Name = "textBox_1_tasksElemsCountInput";
            this.textBox_1_tasksElemsCountInput.Size = new System.Drawing.Size(39, 27);
            this.textBox_1_tasksElemsCountInput.TabIndex = 26;
            // 
            // textBox_2_tasksElemsCountInput
            // 
            this.textBox_2_tasksElemsCountInput.BackColor = System.Drawing.SystemColors.ControlDark;
            this.textBox_2_tasksElemsCountInput.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox_2_tasksElemsCountInput.Location = new System.Drawing.Point(574, 248);
            this.textBox_2_tasksElemsCountInput.Name = "textBox_2_tasksElemsCountInput";
            this.textBox_2_tasksElemsCountInput.Size = new System.Drawing.Size(39, 27);
            this.textBox_2_tasksElemsCountInput.TabIndex = 27;
            // 
            // textBox_3_tasksElemsCountInput
            // 
            this.textBox_3_tasksElemsCountInput.BackColor = System.Drawing.SystemColors.ControlDark;
            this.textBox_3_tasksElemsCountInput.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox_3_tasksElemsCountInput.Location = new System.Drawing.Point(574, 362);
            this.textBox_3_tasksElemsCountInput.Name = "textBox_3_tasksElemsCountInput";
            this.textBox_3_tasksElemsCountInput.Size = new System.Drawing.Size(39, 27);
            this.textBox_3_tasksElemsCountInput.TabIndex = 28;
            // 
            // textBox_4_tasksElemsCountInput
            // 
            this.textBox_4_tasksElemsCountInput.BackColor = System.Drawing.SystemColors.ControlDark;
            this.textBox_4_tasksElemsCountInput.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox_4_tasksElemsCountInput.Location = new System.Drawing.Point(574, 476);
            this.textBox_4_tasksElemsCountInput.Name = "textBox_4_tasksElemsCountInput";
            this.textBox_4_tasksElemsCountInput.Size = new System.Drawing.Size(39, 27);
            this.textBox_4_tasksElemsCountInput.TabIndex = 29;
            // 
            // button_info
            // 
            this.button_info.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.button_info.FlatAppearance.BorderSize = 0;
            this.button_info.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button_info.Location = new System.Drawing.Point(367, 20);
            this.button_info.Name = "button_info";
            this.button_info.Size = new System.Drawing.Size(146, 70);
            this.button_info.TabIndex = 30;
            this.button_info.Text = "Условие задачи";
            this.button_info.UseVisualStyleBackColor = false;
            this.button_info.Click += new System.EventHandler(this.button_info_Click);
            // 
            // button_app_info
            // 
            this.button_app_info.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.button_app_info.FlatAppearance.BorderColor = System.Drawing.Color.Gray;
            this.button_app_info.FlatAppearance.BorderSize = 0;
            this.button_app_info.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button_app_info.Location = new System.Drawing.Point(215, 20);
            this.button_app_info.Name = "button_app_info";
            this.button_app_info.Size = new System.Drawing.Size(146, 70);
            this.button_app_info.TabIndex = 31;
            this.button_app_info.Text = "Как работает";
            this.button_app_info.UseVisualStyleBackColor = false;
            this.button_app_info.Click += new System.EventHandler(this.button_app_info_Click);
            // 
            // ThreadForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.ClientSize = new System.Drawing.Size(625, 581);
            this.Controls.Add(this.button_app_info);
            this.Controls.Add(this.button_info);
            this.Controls.Add(this.textBox_4_tasksElemsCountInput);
            this.Controls.Add(this.textBox_3_tasksElemsCountInput);
            this.Controls.Add(this.textBox_2_tasksElemsCountInput);
            this.Controls.Add(this.textBox_1_tasksElemsCountInput);
            this.Controls.Add(this.textBox_0_tasksElemsCountInput);
            this.Controls.Add(this.label_4_buffer);
            this.Controls.Add(this.label_3_buffer);
            this.Controls.Add(this.label_2_buffer);
            this.Controls.Add(this.label_1_buffer);
            this.Controls.Add(this.label_0_buffer);
            this.Controls.Add(this.textBox_0_bufferMaxSizeInput);
            this.Controls.Add(this.textBox_1_bufferMaxSizeInput);
            this.Controls.Add(this.textBox_2_bufferMaxSizeInput);
            this.Controls.Add(this.textBox_3_bufferMaxSizeInput);
            this.Controls.Add(this.textBox_4_bufferMaxSizeInput);
            this.Controls.Add(this.button_start);
            this.Controls.Add(this.richTextBox_tasksOutput);
            this.Name = "ThreadForm";
            this.ShowIcon = false;
            this.Text = "Задача поставщика и потребителя";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ThreadForm_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

    }

    #endregion
    private RichTextBox richTextBox_tasksOutput;
    private Button button_start;
    private TextBox textBox_4_bufferMaxSizeInput;
    private TextBox textBox_3_bufferMaxSizeInput;
    private TextBox textBox_2_bufferMaxSizeInput;
    private TextBox textBox_1_bufferMaxSizeInput;
    private TextBox textBox_0_bufferMaxSizeInput;
    private Label label_0_buffer;
    private Label label_1_buffer;
    private Label label_2_buffer;
    private Label label_3_buffer;
    private Label label_4_buffer;
    private TextBox textBox_0_tasksElemsCountInput;
    private TextBox textBox_1_tasksElemsCountInput;
    private TextBox textBox_2_tasksElemsCountInput;
    private TextBox textBox_3_tasksElemsCountInput;
    private TextBox textBox_4_tasksElemsCountInput;
    private Button button_info;
    private Button button_app_info;
}