namespace HoloSeatConfig
{
    partial class Configuration
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Configuration));
            this.WalkForwardKey = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.TriggerSteps = new System.Windows.Forms.TrackBar();
            this.label2 = new System.Windows.Forms.Label();
            this.TriggerStepsNumber = new System.Windows.Forms.TextBox();
            this.UpdateHoloseat = new System.Windows.Forms.Button();
            this.CloseForm = new System.Windows.Forms.Button();
            this.Result = new System.Windows.Forms.TextBox();
            this.UpdateDefaults = new System.Windows.Forms.Button();
            this.UploadResult = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.SerialPortList = new System.Windows.Forms.ComboBox();
            this.SerialOutput = new System.Windows.Forms.TextBox();
            this.EnableHoloseat = new System.Windows.Forms.CheckBox();
            this.HardwareType = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.WalkBackwardKey = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.TriggerSteps)).BeginInit();
            this.SuspendLayout();
            // 
            // WalkForwardKey
            // 
            this.WalkForwardKey.Location = new System.Drawing.Point(162, 202);
            this.WalkForwardKey.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.WalkForwardKey.Name = "WalkForwardKey";
            this.WalkForwardKey.Size = new System.Drawing.Size(342, 31);
            this.WalkForwardKey.TabIndex = 1;
            this.WalkForwardKey.TextChanged += new System.EventHandler(this.WalkKey_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(18, 202);
            this.label1.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(133, 25);
            this.label1.TabIndex = 1;
            this.label1.Text = "Forward Key";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // TriggerSteps
            // 
            this.TriggerSteps.Location = new System.Drawing.Point(162, 287);
            this.TriggerSteps.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.TriggerSteps.Maximum = 120;
            this.TriggerSteps.Name = "TriggerSteps";
            this.TriggerSteps.Size = new System.Drawing.Size(346, 90);
            this.TriggerSteps.TabIndex = 2;
            this.TriggerSteps.Scroll += new System.EventHandler(this.TriggerSteps_Scroll);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(18, 287);
            this.label2.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(131, 25);
            this.label2.TabIndex = 3;
            this.label2.Text = "Trigger Rate";
            // 
            // TriggerStepsNumber
            // 
            this.TriggerStepsNumber.Location = new System.Drawing.Point(24, 335);
            this.TriggerStepsNumber.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.TriggerStepsNumber.Name = "TriggerStepsNumber";
            this.TriggerStepsNumber.ReadOnly = true;
            this.TriggerStepsNumber.Size = new System.Drawing.Size(110, 31);
            this.TriggerStepsNumber.TabIndex = 4;
            this.TriggerStepsNumber.TabStop = false;
            // 
            // UpdateHoloseat
            // 
            this.UpdateHoloseat.Location = new System.Drawing.Point(24, 385);
            this.UpdateHoloseat.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.UpdateHoloseat.Name = "UpdateHoloseat";
            this.UpdateHoloseat.Size = new System.Drawing.Size(150, 83);
            this.UpdateHoloseat.TabIndex = 5;
            this.UpdateHoloseat.Text = "Update Holoseat";
            this.UpdateHoloseat.UseVisualStyleBackColor = true;
            this.UpdateHoloseat.Click += new System.EventHandler(this.UpdateHoloseat_Click);
            // 
            // CloseForm
            // 
            this.CloseForm.Location = new System.Drawing.Point(358, 385);
            this.CloseForm.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.CloseForm.Name = "CloseForm";
            this.CloseForm.Size = new System.Drawing.Size(150, 83);
            this.CloseForm.TabIndex = 6;
            this.CloseForm.Text = "Close";
            this.CloseForm.UseVisualStyleBackColor = true;
            this.CloseForm.Click += new System.EventHandler(this.Close_Click);
            // 
            // Result
            // 
            this.Result.Location = new System.Drawing.Point(602, 48);
            this.Result.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.Result.Name = "Result";
            this.Result.ReadOnly = true;
            this.Result.Size = new System.Drawing.Size(422, 31);
            this.Result.TabIndex = 7;
            this.Result.TabStop = false;
            // 
            // UpdateDefaults
            // 
            this.UpdateDefaults.Location = new System.Drawing.Point(186, 385);
            this.UpdateDefaults.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.UpdateDefaults.Name = "UpdateDefaults";
            this.UpdateDefaults.Size = new System.Drawing.Size(150, 83);
            this.UpdateDefaults.TabIndex = 8;
            this.UpdateDefaults.Text = "Update Defaults";
            this.UpdateDefaults.UseVisualStyleBackColor = true;
            this.UpdateDefaults.Click += new System.EventHandler(this.UpdateDefaults_Click);
            // 
            // UploadResult
            // 
            this.UploadResult.AcceptsReturn = true;
            this.UploadResult.Location = new System.Drawing.Point(604, 148);
            this.UploadResult.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.UploadResult.Name = "UploadResult";
            this.UploadResult.ReadOnly = true;
            this.UploadResult.Size = new System.Drawing.Size(420, 31);
            this.UploadResult.TabIndex = 9;
            this.UploadResult.TabStop = false;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(596, 17);
            this.label3.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(128, 25);
            this.label3.TabIndex = 10;
            this.label3.Text = "Save Result";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(596, 117);
            this.label4.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(147, 25);
            this.label4.TabIndex = 11;
            this.label4.Text = "Upload Result";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(20, 63);
            this.label5.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(112, 25);
            this.label5.TabIndex = 13;
            this.label5.Text = "Serial Port";
            // 
            // SerialPortList
            // 
            this.SerialPortList.FormattingEnabled = true;
            this.SerialPortList.Location = new System.Drawing.Point(162, 48);
            this.SerialPortList.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.SerialPortList.Name = "SerialPortList";
            this.SerialPortList.Size = new System.Drawing.Size(342, 33);
            this.SerialPortList.TabIndex = 14;
            // 
            // SerialOutput
            // 
            this.SerialOutput.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.SerialOutput.Location = new System.Drawing.Point(602, 256);
            this.SerialOutput.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.SerialOutput.Multiline = true;
            this.SerialOutput.Name = "SerialOutput";
            this.SerialOutput.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.SerialOutput.Size = new System.Drawing.Size(422, 121);
            this.SerialOutput.TabIndex = 15;
            // 
            // EnableHoloseat
            // 
            this.EnableHoloseat.AutoSize = true;
            this.EnableHoloseat.Checked = true;
            this.EnableHoloseat.CheckState = System.Windows.Forms.CheckState.Checked;
            this.EnableHoloseat.Location = new System.Drawing.Point(24, 158);
            this.EnableHoloseat.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.EnableHoloseat.Name = "EnableHoloseat";
            this.EnableHoloseat.Size = new System.Drawing.Size(202, 29);
            this.EnableHoloseat.TabIndex = 17;
            this.EnableHoloseat.Text = "Enable Holoseat";
            this.EnableHoloseat.UseVisualStyleBackColor = true;
            this.EnableHoloseat.CheckedChanged += new System.EventHandler(this.EnableHoloseat_CheckedChanged);
            // 
            // HardwareType
            // 
            this.HardwareType.DisplayMember = "Leo";
            this.HardwareType.FormattingEnabled = true;
            this.HardwareType.Items.AddRange(new object[] {
            "leo",
            "feather"});
            this.HardwareType.Location = new System.Drawing.Point(162, 110);
            this.HardwareType.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.HardwareType.Name = "HardwareType";
            this.HardwareType.Size = new System.Drawing.Size(238, 33);
            this.HardwareType.TabIndex = 18;
            this.HardwareType.Text = "feather";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(18, 125);
            this.label7.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(104, 25);
            this.label7.TabIndex = 19;
            this.label7.Text = "Hardware";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(596, 208);
            this.label6.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(137, 25);
            this.label6.TabIndex = 20;
            this.label6.Text = "Serial Output";
            this.label6.Click += new System.EventHandler(this.label6_Click);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(18, 244);
            this.label8.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(149, 25);
            this.label8.TabIndex = 21;
            this.label8.Text = "Backward Key";
            // 
            // WalkBackwardKey
            // 
            this.WalkBackwardKey.Location = new System.Drawing.Point(162, 244);
            this.WalkBackwardKey.Margin = new System.Windows.Forms.Padding(6);
            this.WalkBackwardKey.Name = "WalkBackwardKey";
            this.WalkBackwardKey.Size = new System.Drawing.Size(342, 31);
            this.WalkBackwardKey.TabIndex = 22;
            this.WalkBackwardKey.TextChanged += new System.EventHandler(this.WalkBackwardKey_TextChanged);
            // 
            // Configuration
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1058, 491);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.WalkBackwardKey);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.HardwareType);
            this.Controls.Add(this.EnableHoloseat);
            this.Controls.Add(this.SerialOutput);
            this.Controls.Add(this.SerialPortList);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.UploadResult);
            this.Controls.Add(this.UpdateDefaults);
            this.Controls.Add(this.Result);
            this.Controls.Add(this.CloseForm);
            this.Controls.Add(this.UpdateHoloseat);
            this.Controls.Add(this.TriggerStepsNumber);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.TriggerSteps);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.WalkForwardKey);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.Name = "Configuration";
            this.Text = "Holoseat Configuration";
            this.Load += new System.EventHandler(this.Configuration_Load);
            ((System.ComponentModel.ISupportInitialize)(this.TriggerSteps)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox WalkForwardKey;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TrackBar TriggerSteps;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox TriggerStepsNumber;
        private System.Windows.Forms.Button UpdateHoloseat;
        private System.Windows.Forms.Button CloseForm;
        private System.Windows.Forms.TextBox Result;
        private System.Windows.Forms.Button UpdateDefaults;
        private System.Windows.Forms.TextBox UploadResult;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox SerialPortList;
        private System.Windows.Forms.TextBox SerialOutput;
        private System.Windows.Forms.CheckBox EnableHoloseat;
        private System.Windows.Forms.ComboBox HardwareType;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox WalkBackwardKey;
    }
}