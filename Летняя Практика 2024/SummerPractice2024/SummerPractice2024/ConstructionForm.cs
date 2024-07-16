using System.Media;

namespace SummerPractice2024
{
    public partial class ConstructionForm : Form
    {
        private enum ActionResults
        {
            BFG9000,
            Success,
            Unluck,
            Destroy
        }
        Dictionary<ActionResults, string> soundPaths = new()
        {
            { ActionResults.BFG9000, @"..\..\..\Sounds\annihilator_doom.wav" },
            { ActionResults.Success, @"..\..\..\Sounds\success.wav" },
            { ActionResults.Unluck, @"..\..\..\Sounds\unluck.wav" },
            { ActionResults.Destroy, @"..\..\..\Sounds\destroy.wav" }
        };
        private ScalableDetail _currentScalableDetail = null;
        private Point _currentFirstPoint;
        private DetailType _currentDetailType = DetailType.None;
        private Color _currentColor = Color.Green;
        private Color CurrentColor
        {
            get => _currentColor;
            set
            {
                _currentColor = value;
                colorPictureBox.BackColor = value;
            }
        }
        private bool _isDrawing = false;
        private readonly Construction _construction;
        public ConstructionForm()
        {
            InitializeComponent();
            CenterToScreen();
            _construction = new Construction();
        }
        private void blockButton_Click(object sender, EventArgs e)
        {
            if (_isDrawing && _currentDetailType == DetailType.Block)
            {
                SetDefaults();
                return;
            }
            currentDetailTypeLabel.Text = "Блок";
            this.Cursor = new Cursor(@"..\..\..\bass.cur");
            _currentDetailType = DetailType.Block;
        }

        private void SetDefaults()
        {
            _currentDetailType = DetailType.None;
            _isDrawing = false;
            this.Cursor = Cursors.Default;
            currentDetailTypeLabel.Text = "Не выбрано";
        }

        private void BFG9000Button_Click(object sender, EventArgs e)
        {
            if (_isDrawing && _currentDetailType == DetailType.BFG9000)
            {
                SetDefaults();
                return;
            }
            currentDetailTypeLabel.Text = "BFG9000";
            this.Cursor = new Cursor(@"..\..\..\bass.cur");
            _currentDetailType = DetailType.BFG9000;
        }

        private void resetButton_Click(object sender, EventArgs e)
        {
            if (_construction.Destroy())
            {
                var soundDoom = new SoundPlayer(soundPaths[ActionResults.Destroy]);
                soundDoom.Play();
                soundDoom.Dispose();
            }           
            SetDefaults();           
            constructionPictureBox.Refresh();
        }

        private void colorButton_Click(object sender, EventArgs e)
        {
            var colorDialog = new ColorDialog();
            colorDialog.FullOpen = true;
            colorDialog.Color = this.BackColor;
            colorDialog.SolidColorOnly = true;
            if (colorDialog.ShowDialog() == DialogResult.OK)
            {
                CurrentColor = colorDialog.Color;
            }
        }

        private void constructionPictureBox_MouseDown(object sender, MouseEventArgs e)
        {
            if (_currentDetailType == DetailType.None) return;
            _currentFirstPoint = e.Location;
            _isDrawing = true;
            if (_currentDetailType == DetailType.Block)
            {
                _currentScalableDetail = new Block(_currentFirstPoint, CurrentColor);
            }
            else if (_currentDetailType == DetailType.Window)
            {
                _currentScalableDetail = new Window(_currentFirstPoint, CurrentColor);
            }
        }

        private void constructionPictureBox_MouseUp(object sender, MouseEventArgs e)
        {
            if (_currentDetailType == DetailType.None) return;
            AddNewDetail(e);
            constructionPictureBox.Refresh();
        }

        private void AddNewDetail(MouseEventArgs e)
        {
            Detail detail;
            switch (_currentDetailType)
            {
                case DetailType.Block:
                    {
                        var block = new Block(_currentFirstPoint, CurrentColor)
                        {
                            SecondPoint = e.Location
                        };
                        detail = block;
                        _currentScalableDetail = null;
                        break;
                    }

                case DetailType.Window:
                    {
                        var window = new Window(_currentFirstPoint, CurrentColor)
                        {
                            SecondPoint = e.Location
                        };
                        detail = window;
                        _currentScalableDetail = null;
                        break;
                    }

                case DetailType.Wheel:
                    {
                        detail = new Wheel(_currentFirstPoint, CurrentColor);
                        break;
                    }

                case DetailType.Leg:
                    {
                        detail = new Leg(_currentFirstPoint, CurrentColor);
                        break;
                    }

                case DetailType.BFG9000:
                    {
                        detail = new BFG9000(_currentFirstPoint, CurrentColor);
                        break;
                    }

                case DetailType.Rocket:
                    {
                        detail = new Rocket(_currentFirstPoint, CurrentColor);
                        break;
                    }

                case DetailType.WrathOfPoseidon:
                    {
                        detail = new WrathOfPoseidon(_currentFirstPoint, CurrentColor);
                        break;
                    }

                case DetailType.Basukha:
                    {
                        detail = new Basukha(_currentFirstPoint, CurrentColor);
                        break;
                    }

                case DetailType.Flashlight:
                    {
                        detail = new Flashlight(_currentFirstPoint, CurrentColor);
                        break;
                    }

                case DetailType.Bumper:
                    {
                        detail = new Bumper(_currentFirstPoint, CurrentColor);
                        break;
                    }

                default: // Антикрыло
                    {
                        detail = new Wing(_currentFirstPoint, CurrentColor);
                        break;
                    }
            }
            if (_currentDetailType == DetailType.Block)
            {
                if (!_construction.IntersectWith(detail))
                {
                    var soundDoom = new SoundPlayer(soundPaths[ActionResults.Success]);
                    soundDoom.Play();
                    soundDoom.Dispose();
                    _construction.Add(detail);
                }
                else
                {
                    var soundDoom = new SoundPlayer(soundPaths[ActionResults.Unluck]);
                    soundDoom.Play();
                    soundDoom.Dispose();
                }
            }
            else
            {
                bool blockIntersected = false;
                foreach (var d in _construction)
                {
                    if (d.IntersectWith(detail))
                    {
                        if (d is Block)
                            blockIntersected = true;
                        else
                        {
                            var soundDoom = new SoundPlayer(soundPaths[ActionResults.Unluck]);
                            soundDoom.Play();
                            soundDoom.Dispose();
                            return;
                        }
                    }
                }
                if (blockIntersected)
                {
                    var soundDoom = new SoundPlayer(soundPaths[
                        _currentDetailType == DetailType.BFG9000
                        ? ActionResults.BFG9000
                        : ActionResults.Success]);
                    soundDoom.Play();
                    soundDoom.Dispose();
                    _construction.Add(detail);
                }
                else
                {
                    var soundDoom = new SoundPlayer(soundPaths[ActionResults.Unluck]);
                    soundDoom.Play();
                    soundDoom.Dispose();
                }
            }
        }

        private void constructionPictureBox_Paint(object sender, PaintEventArgs e)
        {
            if (!_isDrawing) return;
            foreach (var detail in _construction)
                detail?.Draw(e.Graphics);
            _currentScalableDetail?.Draw(e.Graphics);
            toughnessValueLabel.Text = _construction.Toughness.ToString();
            speedValueLabel.Text = _construction.Speed.ToString();
            damageValueLabel.Text = _construction.Damage.ToString();
            priceValueLabel.Text = _construction.Price.ToString();
        }

        private void constructionPictureBox_MouseMove(object sender, MouseEventArgs e)
        {
            if (Control.MouseButtons != MouseButtons.Left || !_isDrawing
                || !(_currentDetailType == DetailType.Block
                || _currentDetailType == DetailType.Window)) return;
            _currentScalableDetail.SecondPoint = e.Location;
            constructionPictureBox.Refresh();
        }

        private void windowButton_Click(object sender, EventArgs e)
        {
            if (_isDrawing && _currentDetailType == DetailType.Window)
            {
                SetDefaults();
                return;
            }
            currentDetailTypeLabel.Text = "Окно";
            this.Cursor = new Cursor(@"..\..\..\bass.cur");
            _currentDetailType = DetailType.Window;
        }

        private void wheelButton_Click(object sender, EventArgs e)
        {
            if (_isDrawing && _currentDetailType == DetailType.Wheel)
            {
                SetDefaults();
                return;
            }
            currentDetailTypeLabel.Text = "Колесо";
            this.Cursor = new Cursor(@"..\..\..\bass.cur");
            _currentDetailType = DetailType.Wheel;
        }

        private void legButton_Click(object sender, EventArgs e)
        {
            if (_isDrawing && _currentDetailType == DetailType.Leg)
            {
                SetDefaults();
                return;
            }
            currentDetailTypeLabel.Text = "Нога";
            this.Cursor = new Cursor(@"..\..\..\bass.cur");
            _currentDetailType = DetailType.Leg;
        }

        private void flashlightButton_Click(object sender, EventArgs e)
        {
            if (_isDrawing && _currentDetailType == DetailType.Flashlight)
            {
                SetDefaults();
                return;
            }
            currentDetailTypeLabel.Text = "Фонарь";
            this.Cursor = new Cursor(@"..\..\..\bass.cur");
            _currentDetailType = DetailType.Flashlight;
        }

        private void bumperButton_Click(object sender, EventArgs e)
        {
            if (_isDrawing && _currentDetailType == DetailType.Bumper)
            {
                SetDefaults();
                return;
            }
            currentDetailTypeLabel.Text = "Бампер";
            this.Cursor = new Cursor(@"..\..\..\bass.cur");
            _currentDetailType = DetailType.Bumper;
        }

        private void wingButton_Click(object sender, EventArgs e)
        {
            if (_isDrawing && _currentDetailType == DetailType.Wing)
            {
                SetDefaults();
                return;
            }
            currentDetailTypeLabel.Text = "Антикрыло";
            this.Cursor = new Cursor(@"..\..\..\bass.cur");
            _currentDetailType = DetailType.Wing;
        }

        private void ConstructionForm_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Control && e.KeyCode == Keys.Z && !_construction.Empty())
            {
                _construction.PopBack();
                var soundDoom = new SoundPlayer(soundPaths[ActionResults.Destroy]);
                soundDoom.Play();
                soundDoom.Dispose();
                Refresh();
            }
        }

        private void helpButton_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Для добавления блока или окна зажмите левую кнопку мыши и протяните до ожидаемого правого нижнего угла.\n" +
                "Чтобы удалить последнюю добавленную деталь, нажмите комбинцию клавиш Ctrl-Z.\n" +
                "Чтобы закончить добавлять выбранную деталь ещё раз нажмите на кнопку.\n" +
                "Кнопка \"Настроить цвета\" позволяет выбрать цвет для следующей добавленной детали.", "Справка", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void rocketButton_Click(object sender, EventArgs e)
        {
            if (_isDrawing && _currentDetailType == DetailType.Rocket)
            {
                SetDefaults();
                return;
            }
            currentDetailTypeLabel.Text = "Ракета";
            this.Cursor = new Cursor(@"..\..\..\bass.cur");
            _currentDetailType = DetailType.Rocket;
        }

        private void wrathOfPoseidonButton_Click(object sender, EventArgs e)
        {
            if (_isDrawing && _currentDetailType == DetailType.WrathOfPoseidon)
            {
                SetDefaults();
                return;
            }
            currentDetailTypeLabel.Text = "Гнев Посейдона";
            this.Cursor = new Cursor(@"..\..\..\bass.cur");
            _currentDetailType = DetailType.WrathOfPoseidon;
        }

        private void basukhaButton_Click(object sender, EventArgs e)
        {
            if (_isDrawing && _currentDetailType == DetailType.Basukha)
            {
                SetDefaults();
                return;
            }
            currentDetailTypeLabel.Text = "Басуха";
            this.Cursor = new Cursor(@"..\..\..\bass.cur");
            _currentDetailType = DetailType.Basukha;
        }
    }
}
