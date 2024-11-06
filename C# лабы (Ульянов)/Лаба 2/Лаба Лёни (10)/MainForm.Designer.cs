namespace TransportationLab2
{
    partial class MainForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            mapPicture = new PictureBox();
            addClientButton = new Button();
            addVehicleButton = new Button();
            vehiclesLabel = new Label();
            clientsLabel = new Label();
            vehiclesListView = new ListView();
            clientsListView = new ListView();
            ((System.ComponentModel.ISupportInitialize)mapPicture).BeginInit();
            SuspendLayout();
            // 
            // mapPicture
            // 
            mapPicture.BackgroundImage = (Image)resources.GetObject("mapPicture.BackgroundImage");
            mapPicture.Location = new Point(246, 1);
            mapPicture.Name = "mapPicture";
            mapPicture.Size = new Size(939, 921);
            mapPicture.SizeMode = PictureBoxSizeMode.StretchImage;
            mapPicture.TabIndex = 0;
            mapPicture.TabStop = false;
            // 
            // addClientButton
            // 
            addClientButton.Font = new Font("Segoe UI", 13.8F, FontStyle.Regular, GraphicsUnit.Point, 204);
            addClientButton.Location = new Point(1, 547);
            addClientButton.Name = "addClientButton";
            addClientButton.Size = new Size(215, 66);
            addClientButton.TabIndex = 1;
            addClientButton.Text = "Add new client";
            addClientButton.UseVisualStyleBackColor = true;
            addClientButton.Click += addClientButton_Click;
            // 
            // addVehicleButton
            // 
            addVehicleButton.Font = new Font("Segoe UI", 13.8F, FontStyle.Regular, GraphicsUnit.Point, 204);
            addVehicleButton.Location = new Point(1, 12);
            addVehicleButton.Name = "addVehicleButton";
            addVehicleButton.Size = new Size(215, 66);
            addVehicleButton.TabIndex = 2;
            addVehicleButton.Text = "Add new vehicle";
            addVehicleButton.UseVisualStyleBackColor = true;
            addVehicleButton.Click += addVehicleButton_Click;
            // 
            // vehiclesLabel
            // 
            vehiclesLabel.AutoSize = true;
            vehiclesLabel.Font = new Font("Segoe UI", 16.2F, FontStyle.Regular, GraphicsUnit.Point, 204);
            vehiclesLabel.Location = new Point(1, 81);
            vehiclesLabel.Name = "vehiclesLabel";
            vehiclesLabel.Size = new Size(239, 38);
            vehiclesLabel.TabIndex = 4;
            vehiclesLabel.Text = "Available vehicles:";
            // 
            // clientsLabel
            // 
            clientsLabel.AutoSize = true;
            clientsLabel.Font = new Font("Segoe UI", 16.2F, FontStyle.Regular, GraphicsUnit.Point, 204);
            clientsLabel.Location = new Point(1, 616);
            clientsLabel.Name = "clientsLabel";
            clientsLabel.Size = new Size(220, 38);
            clientsLabel.TabIndex = 5;
            clientsLabel.Text = "Available clients:";
            // 
            // vehiclesListView
            // 
            vehiclesListView.Location = new Point(1, 134);
            vehiclesListView.Name = "vehiclesListView";
            vehiclesListView.Size = new Size(215, 230);
            vehiclesListView.TabIndex = 6;
            vehiclesListView.UseCompatibleStateImageBehavior = false;
            // 
            // clientsListView
            // 
            clientsListView.Location = new Point(1, 669);
            clientsListView.Name = "clientsListView";
            clientsListView.Size = new Size(215, 230);
            clientsListView.TabIndex = 7;
            clientsListView.UseCompatibleStateImageBehavior = false;
            // 
            // MainForm
            // 
            AutoScaleDimensions = new SizeF(11F, 28F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1184, 911);
            Controls.Add(clientsListView);
            Controls.Add(vehiclesListView);
            Controls.Add(clientsLabel);
            Controls.Add(vehiclesLabel);
            Controls.Add(addVehicleButton);
            Controls.Add(addClientButton);
            Controls.Add(mapPicture);
            Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 204);
            Icon = (Icon)resources.GetObject("$this.Icon");
            Margin = new Padding(4);
            MaximizeBox = false;
            Name = "MainForm";
            Text = "Shipment Menu";
            ((System.ComponentModel.ISupportInitialize)mapPicture).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private PictureBox mapPicture;
        private Button addClientButton;
        private Button addVehicleButton;
        private Label vehiclesLabel;
        private Label clientsLabel;
        private ListView vehiclesListView;
        private ListView clientsListView;
    }
}
