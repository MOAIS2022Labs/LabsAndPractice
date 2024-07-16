namespace SummerPractice2024
{
    partial class ConstructionForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ConstructionForm));
            toughnessLabel = new Label();
            speedLabel = new Label();
            damageLabel = new Label();
            priceLabel = new Label();
            constructionPictureBox = new PictureBox();
            toughnessValueLabel = new Label();
            damageValueLabel = new Label();
            priceValueLabel = new Label();
            speedValueLabel = new Label();
            blockButton = new Button();
            windowButton = new Button();
            wheelButton = new Button();
            legButton = new Button();
            BFG9000Button = new Button();
            rocketButton = new Button();
            wrathOfPoseidonButton = new Button();
            basukhaButton = new Button();
            flashlightButton = new Button();
            bumperButton = new Button();
            resetButton = new Button();
            colorButton = new Button();
            wingButton = new Button();
            frameLabel = new Label();
            movingPartLabel = new Label();
            weaponsLabel = new Label();
            decorativeElementsLabel = new Label();
            helpButton = new Button();
            colorPictureBox = new PictureBox();
            currentDetailTypeLabel = new Label();
            ((System.ComponentModel.ISupportInitialize)constructionPictureBox).BeginInit();
            ((System.ComponentModel.ISupportInitialize)colorPictureBox).BeginInit();
            SuspendLayout();
            // 
            // toughnessLabel
            // 
            toughnessLabel.AutoSize = true;
            toughnessLabel.Font = new Font("Segoe UI", 11F);
            toughnessLabel.Location = new Point(12, 478);
            toughnessLabel.Name = "toughnessLabel";
            toughnessLabel.Size = new Size(88, 20);
            toughnessLabel.TabIndex = 1;
            toughnessLabel.Text = "Прочность:";
            // 
            // speedLabel
            // 
            speedLabel.AutoSize = true;
            speedLabel.Font = new Font("Segoe UI", 11F);
            speedLabel.Location = new Point(152, 478);
            speedLabel.Name = "speedLabel";
            speedLabel.Size = new Size(76, 20);
            speedLabel.TabIndex = 3;
            speedLabel.Text = "Скорость:";
            // 
            // damageLabel
            // 
            damageLabel.AutoSize = true;
            damageLabel.Font = new Font("Segoe UI", 11F);
            damageLabel.Location = new Point(280, 478);
            damageLabel.Name = "damageLabel";
            damageLabel.Size = new Size(48, 20);
            damageLabel.TabIndex = 5;
            damageLabel.Text = "Урон:";
            // 
            // priceLabel
            // 
            priceLabel.AutoSize = true;
            priceLabel.Font = new Font("Segoe UI", 11F);
            priceLabel.Location = new Point(370, 478);
            priceLabel.Name = "priceLabel";
            priceLabel.Size = new Size(86, 20);
            priceLabel.TabIndex = 7;
            priceLabel.Text = "Стоимость:";
            // 
            // constructionPictureBox
            // 
            constructionPictureBox.BackColor = Color.White;
            constructionPictureBox.BorderStyle = BorderStyle.FixedSingle;
            constructionPictureBox.Location = new Point(12, 26);
            constructionPictureBox.Name = "constructionPictureBox";
            constructionPictureBox.Size = new Size(693, 424);
            constructionPictureBox.TabIndex = 9;
            constructionPictureBox.TabStop = false;
            constructionPictureBox.Paint += constructionPictureBox_Paint;
            constructionPictureBox.MouseDown += constructionPictureBox_MouseDown;
            constructionPictureBox.MouseMove += constructionPictureBox_MouseMove;
            constructionPictureBox.MouseUp += constructionPictureBox_MouseUp;
            // 
            // toughnessValueLabel
            // 
            toughnessValueLabel.AutoSize = true;
            toughnessValueLabel.Font = new Font("Segoe UI", 11F);
            toughnessValueLabel.Location = new Point(102, 478);
            toughnessValueLabel.Name = "toughnessValueLabel";
            toughnessValueLabel.Size = new Size(17, 20);
            toughnessValueLabel.TabIndex = 10;
            toughnessValueLabel.Text = "0";
            // 
            // damageValueLabel
            // 
            damageValueLabel.AutoSize = true;
            damageValueLabel.Font = new Font("Segoe UI", 11F);
            damageValueLabel.Location = new Point(330, 478);
            damageValueLabel.Name = "damageValueLabel";
            damageValueLabel.Size = new Size(17, 20);
            damageValueLabel.TabIndex = 12;
            damageValueLabel.Text = "0";
            // 
            // priceValueLabel
            // 
            priceValueLabel.AutoSize = true;
            priceValueLabel.Font = new Font("Segoe UI", 11F);
            priceValueLabel.Location = new Point(458, 478);
            priceValueLabel.Name = "priceValueLabel";
            priceValueLabel.Size = new Size(17, 20);
            priceValueLabel.TabIndex = 13;
            priceValueLabel.Text = "0";
            // 
            // speedValueLabel
            // 
            speedValueLabel.AutoSize = true;
            speedValueLabel.Font = new Font("Segoe UI", 11F);
            speedValueLabel.Location = new Point(230, 478);
            speedValueLabel.Name = "speedValueLabel";
            speedValueLabel.Size = new Size(17, 20);
            speedValueLabel.TabIndex = 11;
            speedValueLabel.Text = "0";
            // 
            // blockButton
            // 
            blockButton.Font = new Font("Segoe UI", 11F);
            blockButton.Location = new Point(781, 54);
            blockButton.Name = "blockButton";
            blockButton.Size = new Size(108, 32);
            blockButton.TabIndex = 14;
            blockButton.Text = "Блок";
            blockButton.UseVisualStyleBackColor = true;
            blockButton.Click += blockButton_Click;
            // 
            // windowButton
            // 
            windowButton.Font = new Font("Segoe UI", 11F);
            windowButton.Location = new Point(919, 54);
            windowButton.Name = "windowButton";
            windowButton.Size = new Size(86, 32);
            windowButton.TabIndex = 15;
            windowButton.Text = "Окно";
            windowButton.UseVisualStyleBackColor = true;
            windowButton.Click += windowButton_Click;
            // 
            // wheelButton
            // 
            wheelButton.Font = new Font("Segoe UI", 11F);
            wheelButton.Location = new Point(781, 130);
            wheelButton.Name = "wheelButton";
            wheelButton.Size = new Size(108, 32);
            wheelButton.TabIndex = 16;
            wheelButton.Text = "Колесо";
            wheelButton.UseVisualStyleBackColor = true;
            wheelButton.Click += wheelButton_Click;
            // 
            // legButton
            // 
            legButton.Font = new Font("Segoe UI", 11F);
            legButton.Location = new Point(917, 130);
            legButton.Name = "legButton";
            legButton.Size = new Size(86, 32);
            legButton.TabIndex = 17;
            legButton.Text = "Нога";
            legButton.UseVisualStyleBackColor = true;
            legButton.Click += legButton_Click;
            // 
            // BFG9000Button
            // 
            BFG9000Button.Font = new Font("Segoe UI", 11F);
            BFG9000Button.Location = new Point(781, 205);
            BFG9000Button.Name = "BFG9000Button";
            BFG9000Button.Size = new Size(108, 32);
            BFG9000Button.TabIndex = 18;
            BFG9000Button.Text = "BFG9000";
            BFG9000Button.UseVisualStyleBackColor = true;
            BFG9000Button.Click += BFG9000Button_Click;
            // 
            // rocketButton
            // 
            rocketButton.Font = new Font("Segoe UI", 11F);
            rocketButton.Location = new Point(917, 205);
            rocketButton.Name = "rocketButton";
            rocketButton.Size = new Size(86, 32);
            rocketButton.TabIndex = 19;
            rocketButton.Text = "Ракета";
            rocketButton.UseVisualStyleBackColor = true;
            rocketButton.Click += rocketButton_Click;
            // 
            // wrathOfPoseidonButton
            // 
            wrathOfPoseidonButton.Font = new Font("Segoe UI", 11F);
            wrathOfPoseidonButton.Location = new Point(781, 259);
            wrathOfPoseidonButton.Name = "wrathOfPoseidonButton";
            wrathOfPoseidonButton.Size = new Size(108, 60);
            wrathOfPoseidonButton.TabIndex = 20;
            wrathOfPoseidonButton.Text = "Гнев Посейдона";
            wrathOfPoseidonButton.UseVisualStyleBackColor = true;
            wrathOfPoseidonButton.Click += wrathOfPoseidonButton_Click;
            // 
            // basukhaButton
            // 
            basukhaButton.Font = new Font("Segoe UI", 11F);
            basukhaButton.Location = new Point(919, 259);
            basukhaButton.Name = "basukhaButton";
            basukhaButton.Size = new Size(86, 32);
            basukhaButton.TabIndex = 21;
            basukhaButton.Text = "Басуха";
            basukhaButton.UseVisualStyleBackColor = true;
            basukhaButton.Click += basukhaButton_Click;
            // 
            // flashlightButton
            // 
            flashlightButton.Font = new Font("Segoe UI", 11F);
            flashlightButton.Location = new Point(781, 350);
            flashlightButton.Name = "flashlightButton";
            flashlightButton.Size = new Size(108, 32);
            flashlightButton.TabIndex = 22;
            flashlightButton.Text = "Фонарь";
            flashlightButton.UseVisualStyleBackColor = true;
            flashlightButton.Click += flashlightButton_Click;
            // 
            // bumperButton
            // 
            bumperButton.Font = new Font("Segoe UI", 11F);
            bumperButton.Location = new Point(917, 350);
            bumperButton.Name = "bumperButton";
            bumperButton.Size = new Size(86, 32);
            bumperButton.TabIndex = 23;
            bumperButton.Text = "Бампер";
            bumperButton.UseVisualStyleBackColor = true;
            bumperButton.Click += bumperButton_Click;
            // 
            // resetButton
            // 
            resetButton.Font = new Font("Segoe UI", 11F);
            resetButton.Location = new Point(625, 472);
            resetButton.Name = "resetButton";
            resetButton.Size = new Size(86, 32);
            resetButton.TabIndex = 24;
            resetButton.Text = "Сброс";
            resetButton.UseVisualStyleBackColor = true;
            resetButton.Click += resetButton_Click;
            // 
            // colorButton
            // 
            colorButton.Font = new Font("Segoe UI", 11F);
            colorButton.Location = new Point(781, 446);
            colorButton.Name = "colorButton";
            colorButton.Size = new Size(91, 59);
            colorButton.TabIndex = 25;
            colorButton.Text = "Настроить цвета";
            colorButton.UseVisualStyleBackColor = true;
            colorButton.Click += colorButton_Click;
            // 
            // wingButton
            // 
            wingButton.Font = new Font("Segoe UI", 11F);
            wingButton.Location = new Point(842, 404);
            wingButton.Name = "wingButton";
            wingButton.Size = new Size(107, 32);
            wingButton.TabIndex = 26;
            wingButton.Text = "Антикрыло";
            wingButton.UseVisualStyleBackColor = true;
            wingButton.Click += wingButton_Click;
            // 
            // frameLabel
            // 
            frameLabel.AutoSize = true;
            frameLabel.Font = new Font("Segoe UI", 11.25F, FontStyle.Italic, GraphicsUnit.Point, 204);
            frameLabel.Location = new Point(864, 26);
            frameLabel.Name = "frameLabel";
            frameLabel.Size = new Size(56, 20);
            frameLabel.TabIndex = 27;
            frameLabel.Text = "Корпус";
            // 
            // movingPartLabel
            // 
            movingPartLabel.AutoSize = true;
            movingPartLabel.Font = new Font("Segoe UI", 11.25F, FontStyle.Italic, GraphicsUnit.Point, 204);
            movingPartLabel.Location = new Point(842, 102);
            movingPartLabel.Name = "movingPartLabel";
            movingPartLabel.Size = new Size(113, 20);
            movingPartLabel.TabIndex = 28;
            movingPartLabel.Text = "Ходовая часть";
            // 
            // weaponsLabel
            // 
            weaponsLabel.AutoSize = true;
            weaponsLabel.Font = new Font("Segoe UI", 11.25F, FontStyle.Italic, GraphicsUnit.Point, 204);
            weaponsLabel.Location = new Point(862, 177);
            weaponsLabel.Name = "weaponsLabel";
            weaponsLabel.Size = new Size(58, 20);
            weaponsLabel.TabIndex = 29;
            weaponsLabel.Text = "Орудия";
            // 
            // decorativeElementsLabel
            // 
            decorativeElementsLabel.AutoSize = true;
            decorativeElementsLabel.Font = new Font("Segoe UI", 11.25F, FontStyle.Italic, GraphicsUnit.Point, 204);
            decorativeElementsLabel.Location = new Point(808, 322);
            decorativeElementsLabel.Name = "decorativeElementsLabel";
            decorativeElementsLabel.Size = new Size(185, 20);
            decorativeElementsLabel.TabIndex = 30;
            decorativeElementsLabel.Text = "Декоративные элементы";
            // 
            // helpButton
            // 
            helpButton.BackColor = SystemColors.Info;
            helpButton.Font = new Font("Segoe UI", 11F);
            helpButton.Location = new Point(919, 471);
            helpButton.Name = "helpButton";
            helpButton.Size = new Size(84, 33);
            helpButton.TabIndex = 31;
            helpButton.Text = "Помощь";
            helpButton.UseVisualStyleBackColor = false;
            helpButton.Click += helpButton_Click;
            // 
            // colorPictureBox
            // 
            colorPictureBox.BackColor = Color.Green;
            colorPictureBox.Location = new Point(870, 447);
            colorPictureBox.Name = "colorPictureBox";
            colorPictureBox.Size = new Size(19, 57);
            colorPictureBox.TabIndex = 32;
            colorPictureBox.TabStop = false;
            // 
            // currentDetailTypeLabel
            // 
            currentDetailTypeLabel.AutoSize = true;
            currentDetailTypeLabel.Font = new Font("Segoe UI", 11.25F, FontStyle.Italic, GraphicsUnit.Point, 204);
            currentDetailTypeLabel.Location = new Point(318, 3);
            currentDetailTypeLabel.Name = "currentDetailTypeLabel";
            currentDetailTypeLabel.Size = new Size(89, 20);
            currentDetailTypeLabel.TabIndex = 33;
            currentDetailTypeLabel.Text = "Не выбрано";
            // 
            // ConstructionForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1017, 517);
            Controls.Add(currentDetailTypeLabel);
            Controls.Add(colorPictureBox);
            Controls.Add(helpButton);
            Controls.Add(decorativeElementsLabel);
            Controls.Add(weaponsLabel);
            Controls.Add(movingPartLabel);
            Controls.Add(frameLabel);
            Controls.Add(wingButton);
            Controls.Add(colorButton);
            Controls.Add(resetButton);
            Controls.Add(bumperButton);
            Controls.Add(flashlightButton);
            Controls.Add(basukhaButton);
            Controls.Add(wrathOfPoseidonButton);
            Controls.Add(rocketButton);
            Controls.Add(BFG9000Button);
            Controls.Add(legButton);
            Controls.Add(wheelButton);
            Controls.Add(windowButton);
            Controls.Add(blockButton);
            Controls.Add(priceValueLabel);
            Controls.Add(damageValueLabel);
            Controls.Add(speedValueLabel);
            Controls.Add(toughnessValueLabel);
            Controls.Add(constructionPictureBox);
            Controls.Add(priceLabel);
            Controls.Add(damageLabel);
            Controls.Add(speedLabel);
            Controls.Add(toughnessLabel);
            FormBorderStyle = FormBorderStyle.FixedToolWindow;
            Icon = (Icon)resources.GetObject("$this.Icon");
            KeyPreview = true;
            Name = "ConstructionForm";
            Text = "Задача на графику C# | 6C";
            KeyDown += ConstructionForm_KeyDown;
            ((System.ComponentModel.ISupportInitialize)constructionPictureBox).EndInit();
            ((System.ComponentModel.ISupportInitialize)colorPictureBox).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion
        private Label toughnessLabel;
        private Label speedLabel;
        private Label damageLabel;
        private Label priceLabel;
        private PictureBox constructionPictureBox;
        private Label toughnessValueLabel;
        private Label label1;
        private Label damageValueLabel;
        private Label priceValueLabel;
        private Label speedValueLabel;
        private Button blockButton;
        private Button windowButton;
        private Button wheelButton;
        private Button legButton;
        private Button BFG9000Button;
        private Button rocketButton;
        private Button wrathOfPoseidonButton;
        private Button basukhaButton;
        private Button flashlightButton;
        private Button bumperButton;
        private Button resetButton;
        private Button colorButton;
        private Button wingButton;
        private Label frameLabel;
        private Label movingPartButton;
        private Label label4;
        private Label decorativeElementsLabel;
        Label movingPartLabel;
        Label weaponsLabel;
        private Button helpButton;
        private PictureBox colorPictureBox;
        private Label currentDetailTypeLabel;
    }
}
