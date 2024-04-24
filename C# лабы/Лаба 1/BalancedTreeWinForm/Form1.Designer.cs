namespace BalancedTreeWinForm
{
    partial class BalancedTreeForm
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
            menuStrip1 = new MenuStrip();
            toolStripMenuItem1 = new ToolStripMenuItem();
            linkedTreeToolStripMenuItem = new ToolStripMenuItem();
            intLinkedToolStripMenuItem = new ToolStripMenuItem();
            stringLinkedToolStripMenuItem = new ToolStripMenuItem();
            arrayTreeToolStripMenuItem = new ToolStripMenuItem();
            intArrayToolStripMenuItem = new ToolStripMenuItem();
            stringArrayToolStripMenuItem = new ToolStripMenuItem();
            очиститьToolStripMenuItem = new ToolStripMenuItem();
            добавитьToolStripMenuItem = new ToolStripMenuItem();
            удалитьToolStripMenuItem = new ToolStripMenuItem();
            содержитсяЛиToolStripMenuItem = new ToolStripMenuItem();
            утилитыToolStripMenuItem = new ToolStripMenuItem();
            intУтилитыToolStripMenuItem = new ToolStripMenuItem();
            существуетЛиЧетноеToolStripMenuItem = new ToolStripMenuItem();
            существуетЛиЧетноеToolStripMenuItem1 = new ToolStripMenuItem();
            увеличитьВсеВ2РазаToolStripMenuItem = new ToolStripMenuItem();
            всеПростыеToolStripMenuItem = new ToolStripMenuItem();
            stringУтилитыToolStripMenuItem = new ToolStripMenuItem();
            существуетСтрокаИзОдинаковыхСимволовToolStripMenuItem = new ToolStripMenuItem();
            найтиВсеНачинающиесяСЗаданнойБуквыToolStripMenuItem = new ToolStripMenuItem();
            перевестиВВерхнийРегистрToolStripMenuItem = new ToolStripMenuItem();
            всеНечетнойДлиныToolStripMenuItem = new ToolStripMenuItem();
            textBoxVizualizer = new TextBox();
            label1 = new Label();
            radioButtonUnmutable = new RadioButton();
            radioButtonMutable = new RadioButton();
            buttonInfo = new Button();
            menuStrip1.SuspendLayout();
            SuspendLayout();
            // 
            // menuStrip1
            // 
            menuStrip1.ImageScalingSize = new Size(20, 20);
            menuStrip1.Items.AddRange(new ToolStripItem[] { toolStripMenuItem1, очиститьToolStripMenuItem, добавитьToolStripMenuItem, удалитьToolStripMenuItem, содержитсяЛиToolStripMenuItem, утилитыToolStripMenuItem });
            menuStrip1.Location = new Point(0, 0);
            menuStrip1.Name = "menuStrip1";
            menuStrip1.Size = new Size(835, 28);
            menuStrip1.TabIndex = 0;
            menuStrip1.Text = "menuStrip1";
            // 
            // toolStripMenuItem1
            // 
            toolStripMenuItem1.DropDownItems.AddRange(new ToolStripItem[] { linkedTreeToolStripMenuItem, arrayTreeToolStripMenuItem });
            toolStripMenuItem1.Name = "toolStripMenuItem1";
            toolStripMenuItem1.Size = new Size(78, 24);
            toolStripMenuItem1.Text = "Создать";
            // 
            // linkedTreeToolStripMenuItem
            // 
            linkedTreeToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { intLinkedToolStripMenuItem, stringLinkedToolStripMenuItem });
            linkedTreeToolStripMenuItem.Name = "linkedTreeToolStripMenuItem";
            linkedTreeToolStripMenuItem.Size = new Size(163, 26);
            linkedTreeToolStripMenuItem.Text = "LinkedTree";
            // 
            // intLinkedToolStripMenuItem
            // 
            intLinkedToolStripMenuItem.Name = "intLinkedToolStripMenuItem";
            intLinkedToolStripMenuItem.Size = new Size(129, 26);
            intLinkedToolStripMenuItem.Text = "int";
            intLinkedToolStripMenuItem.Click += intLinkedToolStripMenuItem_Click;
            // 
            // stringLinkedToolStripMenuItem
            // 
            stringLinkedToolStripMenuItem.Name = "stringLinkedToolStripMenuItem";
            stringLinkedToolStripMenuItem.Size = new Size(129, 26);
            stringLinkedToolStripMenuItem.Text = "string";
            stringLinkedToolStripMenuItem.Click += stringLinkedToolStripMenuItem_Click;
            // 
            // arrayTreeToolStripMenuItem
            // 
            arrayTreeToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { intArrayToolStripMenuItem, stringArrayToolStripMenuItem });
            arrayTreeToolStripMenuItem.Name = "arrayTreeToolStripMenuItem";
            arrayTreeToolStripMenuItem.Size = new Size(163, 26);
            arrayTreeToolStripMenuItem.Text = "ArrayTree";
            // 
            // intArrayToolStripMenuItem
            // 
            intArrayToolStripMenuItem.Name = "intArrayToolStripMenuItem";
            intArrayToolStripMenuItem.Size = new Size(129, 26);
            intArrayToolStripMenuItem.Text = "int";
            intArrayToolStripMenuItem.Click += intArrayToolStripMenuItem_Click;
            // 
            // stringArrayToolStripMenuItem
            // 
            stringArrayToolStripMenuItem.Name = "stringArrayToolStripMenuItem";
            stringArrayToolStripMenuItem.Size = new Size(129, 26);
            stringArrayToolStripMenuItem.Text = "string";
            stringArrayToolStripMenuItem.Click += stringArrayToolStripMenuItem_Click;
            // 
            // очиститьToolStripMenuItem
            // 
            очиститьToolStripMenuItem.Name = "очиститьToolStripMenuItem";
            очиститьToolStripMenuItem.Size = new Size(87, 24);
            очиститьToolStripMenuItem.Text = "Очистить";
            очиститьToolStripMenuItem.Click += очиститьToolStripMenuItem_Click;
            // 
            // добавитьToolStripMenuItem
            // 
            добавитьToolStripMenuItem.Name = "добавитьToolStripMenuItem";
            добавитьToolStripMenuItem.Size = new Size(90, 24);
            добавитьToolStripMenuItem.Text = "Добавить";
            добавитьToolStripMenuItem.Click += добавитьToolStripMenuItem_Click;
            // 
            // удалитьToolStripMenuItem
            // 
            удалитьToolStripMenuItem.Name = "удалитьToolStripMenuItem";
            удалитьToolStripMenuItem.Size = new Size(79, 24);
            удалитьToolStripMenuItem.Text = "Удалить";
            удалитьToolStripMenuItem.Click += удалитьToolStripMenuItem_Click;
            // 
            // содержитсяЛиToolStripMenuItem
            // 
            содержитсяЛиToolStripMenuItem.Name = "содержитсяЛиToolStripMenuItem";
            содержитсяЛиToolStripMenuItem.Size = new Size(128, 24);
            содержитсяЛиToolStripMenuItem.Text = "Содержится ли";
            содержитсяЛиToolStripMenuItem.Click += содержитсяЛиToolStripMenuItem_Click;
            // 
            // утилитыToolStripMenuItem
            // 
            утилитыToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { intУтилитыToolStripMenuItem, stringУтилитыToolStripMenuItem });
            утилитыToolStripMenuItem.Name = "утилитыToolStripMenuItem";
            утилитыToolStripMenuItem.Size = new Size(81, 24);
            утилитыToolStripMenuItem.Text = "Утилиты";
            // 
            // intУтилитыToolStripMenuItem
            // 
            intУтилитыToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { существуетЛиЧетноеToolStripMenuItem, существуетЛиЧетноеToolStripMenuItem1, увеличитьВсеВ2РазаToolStripMenuItem, всеПростыеToolStripMenuItem });
            intУтилитыToolStripMenuItem.Name = "intУтилитыToolStripMenuItem";
            intУтилитыToolStripMenuItem.Size = new Size(224, 26);
            intУтилитыToolStripMenuItem.Text = "int";
            // 
            // существуетЛиЧетноеToolStripMenuItem
            // 
            существуетЛиЧетноеToolStripMenuItem.Name = "существуетЛиЧетноеToolStripMenuItem";
            существуетЛиЧетноеToolStripMenuItem.Size = new Size(252, 26);
            существуетЛиЧетноеToolStripMenuItem.Text = "Существует ли четное";
            существуетЛиЧетноеToolStripMenuItem.Click += существуетЛиЧетноеToolStripMenuItem_Click;
            // 
            // существуетЛиЧетноеToolStripMenuItem1
            // 
            существуетЛиЧетноеToolStripMenuItem1.Name = "существуетЛиЧетноеToolStripMenuItem1";
            существуетЛиЧетноеToolStripMenuItem1.Size = new Size(252, 26);
            существуетЛиЧетноеToolStripMenuItem1.Text = "Найти все двузначные";
            существуетЛиЧетноеToolStripMenuItem1.Click += найтиВсеДвузначныеToolStripMenuItem1_Click;
            // 
            // увеличитьВсеВ2РазаToolStripMenuItem
            // 
            увеличитьВсеВ2РазаToolStripMenuItem.Name = "увеличитьВсеВ2РазаToolStripMenuItem";
            увеличитьВсеВ2РазаToolStripMenuItem.Size = new Size(252, 26);
            увеличитьВсеВ2РазаToolStripMenuItem.Text = "Увеличить все в 2 раза";
            увеличитьВсеВ2РазаToolStripMenuItem.Click += увеличитьВсеВ2РазаToolStripMenuItem_Click;
            // 
            // всеПростыеToolStripMenuItem
            // 
            всеПростыеToolStripMenuItem.Name = "Все делятся на 3";
            всеПростыеToolStripMenuItem.Size = new Size(252, 26);
            всеПростыеToolStripMenuItem.Text = "Все делятся на 3";
            всеПростыеToolStripMenuItem.Click += всеДелятсяНа3ToolStripMenuItem_Click;
            // 
            // stringУтилитыToolStripMenuItem
            // 
            stringУтилитыToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { существуетСтрокаИзОдинаковыхСимволовToolStripMenuItem, найтиВсеНачинающиесяСЗаданнойБуквыToolStripMenuItem, перевестиВВерхнийРегистрToolStripMenuItem, всеНечетнойДлиныToolStripMenuItem });
            stringУтилитыToolStripMenuItem.Name = "stringУтилитыToolStripMenuItem";
            stringУтилитыToolStripMenuItem.Size = new Size(224, 26);
            stringУтилитыToolStripMenuItem.Text = "string";
            // 
            // существуетСтрокаИзОдинаковыхСимволовToolStripMenuItem
            // 
            существуетСтрокаИзОдинаковыхСимволовToolStripMenuItem.Name = "существуетСтрокаИзОдинаковыхСимволовToolStripMenuItem";
            существуетСтрокаИзОдинаковыхСимволовToolStripMenuItem.Size = new Size(425, 26);
            существуетСтрокаИзОдинаковыхСимволовToolStripMenuItem.Text = "Существует строка из одинаковых символов";
            существуетСтрокаИзОдинаковыхСимволовToolStripMenuItem.Click += существуетСтрокаИзОдинаковыхСимволовToolStripMenuItem_Click;
            // 
            // найтиВсеНачинающиесяСЗаданнойБуквыToolStripMenuItem
            // 
            найтиВсеНачинающиесяСЗаданнойБуквыToolStripMenuItem.Name = "найтиВсеНачинающиесяСЗаглавнойБуквыToolStripMenuItem";
            найтиВсеНачинающиесяСЗаданнойБуквыToolStripMenuItem.Size = new Size(425, 26);
            найтиВсеНачинающиесяСЗаданнойБуквыToolStripMenuItem.Text = "Найти все начинающиеся с заглавной латинской буквы";
            найтиВсеНачинающиесяСЗаданнойБуквыToolStripMenuItem.Click += найтиВсеНачинающиесяСЗаглавнойБуквыToolStripMenuItem_Click;
            // 
            // перевестиВВерхнийРегистрToolStripMenuItem
            // 
            перевестиВВерхнийРегистрToolStripMenuItem.Name = "перевернутьСтрокуToolStripMenuItem";
            перевестиВВерхнийРегистрToolStripMenuItem.Size = new Size(425, 26);
            перевестиВВерхнийРегистрToolStripMenuItem.Text = "Перевернуть строку";
            перевестиВВерхнийРегистрToolStripMenuItem.Click += перевернутьСтрокуToolStripMenuItem_Click;
            // 
            // всеНечетнойДлиныToolStripMenuItem
            // 
            всеНечетнойДлиныToolStripMenuItem.Name = "всеНечетнойДлиныToolStripMenuItem";
            всеНечетнойДлиныToolStripMenuItem.Size = new Size(425, 26);
            всеНечетнойДлиныToolStripMenuItem.Text = "Все нечетной длины";
            всеНечетнойДлиныToolStripMenuItem.Click += всеНечетнойДлиныToolStripMenuItem_Click;
            // 
            // textBoxVizualizer
            // 
            textBoxVizualizer.Location = new Point(166, 65);
            textBoxVizualizer.Multiline = true;
            textBoxVizualizer.Name = "textBoxVizualizer";
            textBoxVizualizer.ReadOnly = true;
            textBoxVizualizer.ScrollBars = ScrollBars.Both;
            textBoxVizualizer.Size = new Size(657, 411);
            textBoxVizualizer.TabIndex = 1;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(415, 42);
            label1.Name = "label1";
            label1.Size = new Size(160, 20);
            label1.TabIndex = 2;
            label1.Text = "Визуализация дерева";
            // 
            // radioButtonUnmutable
            // 
            radioButtonUnmutable.AutoSize = true;
            radioButtonUnmutable.Location = new Point(12, 157);
            radioButtonUnmutable.Name = "radioButtonUnmutable";
            radioButtonUnmutable.Size = new Size(137, 24);
            radioButtonUnmutable.TabIndex = 3;
            radioButtonUnmutable.Text = "Неизменяемое";
            radioButtonUnmutable.UseVisualStyleBackColor = true;
            // 
            // radioButtonMutable
            // 
            radioButtonMutable.AutoSize = true;
            radioButtonMutable.Checked = true;
            radioButtonMutable.Location = new Point(12, 112);
            radioButtonMutable.Name = "radioButtonMutable";
            radioButtonMutable.Size = new Size(120, 24);
            radioButtonMutable.TabIndex = 4;
            radioButtonMutable.TabStop = true;
            radioButtonMutable.Text = "Изменяемое";
            radioButtonMutable.UseVisualStyleBackColor = true;
            radioButtonMutable.CheckedChanged += radioButtonMutable_CheckedChanged;
            // 
            // buttonInfo
            // 
            buttonInfo.BackColor = Color.PaleTurquoise;
            buttonInfo.Location = new Point(12, 228);
            buttonInfo.Name = "buttonInfo";
            buttonInfo.Size = new Size(137, 72);
            buttonInfo.TabIndex = 5;
            buttonInfo.Text = "Информация \r\nо дереве";
            buttonInfo.UseVisualStyleBackColor = false;
            buttonInfo.Click += buttonInfo_Click;
            buttonInfo.MouseLeave += buttonInfo_MouseLeave;
            buttonInfo.MouseMove += buttonInfo_MouseMove;
            // 
            // BalancedTreeForm
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(835, 487);
            Controls.Add(buttonInfo);
            Controls.Add(radioButtonMutable);
            Controls.Add(radioButtonUnmutable);
            Controls.Add(label1);
            Controls.Add(textBoxVizualizer);
            Controls.Add(menuStrip1);
            MainMenuStrip = menuStrip1;
            Name = "BalancedTreeForm";
            Text = "BalancedTreeForm";
            menuStrip1.ResumeLayout(false);
            menuStrip1.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private MenuStrip menuStrip1;
        private ToolStripMenuItem добавитьToolStripMenuItem;
        private ToolStripMenuItem удалитьToolStripMenuItem;
        private ToolStripMenuItem содержитсяЛиToolStripMenuItem;
        private ToolStripMenuItem toolStripMenuItem1;
        private ToolStripMenuItem linkedTreeToolStripMenuItem;
        private ToolStripMenuItem arrayTreeToolStripMenuItem;
        private ToolStripMenuItem утилитыToolStripMenuItem;
        private TextBox textBoxVizualizer;
        private Label label1;
        private ToolStripMenuItem очиститьToolStripMenuItem;
        private RadioButton radioButtonUnmutable;
        private RadioButton radioButtonMutable;
        private Button buttonInfo;
        private ToolStripMenuItem intLinkedToolStripMenuItem;
        private ToolStripMenuItem stringLinkedToolStripMenuItem;
        private ToolStripMenuItem intArrayToolStripMenuItem;
        private ToolStripMenuItem stringArrayToolStripMenuItem;
        private ToolStripMenuItem intУтилитыToolStripMenuItem;
        private ToolStripMenuItem stringУтилитыToolStripMenuItem;
        private ToolStripMenuItem существуетЛиЧетноеToolStripMenuItem;
        private ToolStripMenuItem существуетЛиЧетноеToolStripMenuItem1;
        private ToolStripMenuItem увеличитьВсеВ2РазаToolStripMenuItem;
        private ToolStripMenuItem существуетСтрокаИзОдинаковыхСимволовToolStripMenuItem;
        private ToolStripMenuItem найтиВсеНачинающиесяСЗаданнойБуквыToolStripMenuItem;
        private ToolStripMenuItem перевестиВВерхнийРегистрToolStripMenuItem;
        private ToolStripMenuItem всеНечетнойДлиныToolStripMenuItem;
        private ToolStripMenuItem всеПростыеToolStripMenuItem;
    }
}
