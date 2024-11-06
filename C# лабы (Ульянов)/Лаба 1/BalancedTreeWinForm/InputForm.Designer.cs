namespace BalancedTreeWinForm
{
    partial class InputForm<T>
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
            textBoxInput = new TextBox();
            buttonOK = new Button();
            buttonCancel = new Button();
            SuspendLayout();
            // 
            // textBoxInput
            // 
            textBoxInput.Location = new Point(28, 12);
            textBoxInput.Multiline = true;
            textBoxInput.Name = "textBoxInput";
            textBoxInput.RightToLeft = RightToLeft.No;
            textBoxInput.ScrollBars = ScrollBars.Both;
            textBoxInput.Size = new Size(311, 209);
            textBoxInput.TabIndex = 0;
            textBoxInput.WordWrap = false;
            textBoxInput.KeyPress += textBoxInput_KeyPress;
            // 
            // buttonOK
            // 
            buttonOK.BackColor = SystemColors.Control;
            buttonOK.Location = new Point(28, 248);
            buttonOK.Name = "buttonOK";
            buttonOK.Size = new Size(61, 29);
            buttonOK.TabIndex = 1;
            buttonOK.Text = "OK";
            buttonOK.UseVisualStyleBackColor = false;
            buttonOK.Click += buttonOK_Click;
            buttonOK.MouseLeave += buttonOK_MouseLeave;
            buttonOK.MouseMove += buttonOK_MouseMove;
            // 
            // buttonCancel
            // 
            buttonCancel.BackColor = SystemColors.Control;
            buttonCancel.Location = new Point(245, 248);
            buttonCancel.Name = "buttonCancel";
            buttonCancel.Size = new Size(94, 29);
            buttonCancel.TabIndex = 2;
            buttonCancel.Text = "Cancel";
            buttonCancel.UseVisualStyleBackColor = false;
            buttonCancel.Click += buttonCancel_Click;
            buttonCancel.MouseLeave += buttonCancel_MouseLeave;
            buttonCancel.MouseMove += buttonCancel_MouseMove;
            // 
            // InputForm
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(369, 301);
            Controls.Add(buttonCancel);
            Controls.Add(buttonOK);
            Controls.Add(textBoxInput);
            Name = "InputForm";
            Text = "InputForm";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private TextBox textBoxInput;
        private Button buttonOK;
        private Button buttonCancel;
    }
}