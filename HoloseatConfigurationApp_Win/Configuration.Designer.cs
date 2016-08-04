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
            this.WalkKey = new System.Windows.Forms.TextBox();
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
            ((System.ComponentModel.ISupportInitialize)(this.TriggerSteps)).BeginInit();
            this.SuspendLayout();
            // 
            // WalkKey
            // 
            this.WalkKey.Location = new System.Drawing.Point(81, 127);
            this.WalkKey.Name = "WalkKey";
            this.WalkKey.Size = new System.Drawing.Size(173, 20);
            this.WalkKey.TabIndex = 1;
            this.WalkKey.TextChanged += new System.EventHandler(this.WalkKey_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 127);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Walk Key";
            // 
            // TriggerSteps
            // 
            this.TriggerSteps.Location = new System.Drawing.Point(81, 153);
            this.TriggerSteps.Maximum = 120;
            this.TriggerSteps.Name = "TriggerSteps";
            this.TriggerSteps.Size = new System.Drawing.Size(173, 45);
            this.TriggerSteps.TabIndex = 2;
            this.TriggerSteps.Scroll += new System.EventHandler(this.TriggerSteps_Scroll);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 153);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(66, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Trigger Rate";
            // 
            // TriggerStepsNumber
            // 
            this.TriggerStepsNumber.Location = new System.Drawing.Point(12, 178);
            this.TriggerStepsNumber.Name = "TriggerStepsNumber";
            this.TriggerStepsNumber.ReadOnly = true;
            this.TriggerStepsNumber.Size = new System.Drawing.Size(57, 20);
            this.TriggerStepsNumber.TabIndex = 4;
            this.TriggerStepsNumber.TabStop = false;
            // 
            // UpdateHoloseat
            // 
            this.UpdateHoloseat.Location = new System.Drawing.Point(12, 307);
            this.UpdateHoloseat.Name = "UpdateHoloseat";
            this.UpdateHoloseat.Size = new System.Drawing.Size(75, 43);
            this.UpdateHoloseat.TabIndex = 5;
            this.UpdateHoloseat.Text = "Update Holoseat";
            this.UpdateHoloseat.UseVisualStyleBackColor = true;
            this.UpdateHoloseat.Click += new System.EventHandler(this.UpdateHoloseat_Click);
            // 
            // CloseForm
            // 
            this.CloseForm.Location = new System.Drawing.Point(179, 307);
            this.CloseForm.Name = "CloseForm";
            this.CloseForm.Size = new System.Drawing.Size(75, 43);
            this.CloseForm.TabIndex = 6;
            this.CloseForm.Text = "Close";
            this.CloseForm.UseVisualStyleBackColor = true;
            this.CloseForm.Click += new System.EventHandler(this.Close_Click);
            // 
            // Result
            // 
            this.Result.Location = new System.Drawing.Point(12, 229);
            this.Result.Name = "Result";
            this.Result.ReadOnly = true;
            this.Result.Size = new System.Drawing.Size(242, 20);
            this.Result.TabIndex = 7;
            this.Result.TabStop = false;
            // 
            // UpdateDefaults
            // 
            this.UpdateDefaults.Location = new System.Drawing.Point(93, 307);
            this.UpdateDefaults.Name = "UpdateDefaults";
            this.UpdateDefaults.Size = new System.Drawing.Size(75, 43);
            this.UpdateDefaults.TabIndex = 8;
            this.UpdateDefaults.Text = "Update Defaults";
            this.UpdateDefaults.UseVisualStyleBackColor = true;
            this.UpdateDefaults.Click += new System.EventHandler(this.UpdateDefaults_Click);
            // 
            // UploadResult
            // 
            this.UploadResult.AcceptsReturn = true;
            this.UploadResult.Location = new System.Drawing.Point(13, 281);
            this.UploadResult.Name = "UploadResult";
            this.UploadResult.ReadOnly = true;
            this.UploadResult.Size = new System.Drawing.Size(241, 20);
            this.UploadResult.TabIndex = 9;
            this.UploadResult.TabStop = false;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 213);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(65, 13);
            this.label3.TabIndex = 10;
            this.label3.Text = "Save Result";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(9, 265);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(74, 13);
            this.label4.TabIndex = 11;
            this.label4.Text = "Upload Result";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(10, 55);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(55, 13);
            this.label5.TabIndex = 13;
            this.label5.Text = "Serial Port";
            // 
            // SerialPortList
            // 
            this.SerialPortList.FormattingEnabled = true;
            this.SerialPortList.Location = new System.Drawing.Point(81, 47);
            this.SerialPortList.Name = "SerialPortList";
            this.SerialPortList.Size = new System.Drawing.Size(173, 21);
            this.SerialPortList.TabIndex = 14;
            // 
            // SerialOutput
            // 
            this.SerialOutput.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.SerialOutput.Location = new System.Drawing.Point(298, 79);
            this.SerialOutput.Multiline = true;
            this.SerialOutput.Name = "SerialOutput";
            this.SerialOutput.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.SerialOutput.Size = new System.Drawing.Size(213, 217);
            this.SerialOutput.TabIndex = 15;
            // 
            // EnableHoloseat
            // 
            this.EnableHoloseat.AutoSize = true;
            this.EnableHoloseat.Checked = true;
            this.EnableHoloseat.CheckState = System.Windows.Forms.CheckState.Checked;
            this.EnableHoloseat.Location = new System.Drawing.Point(12, 104);
            this.EnableHoloseat.Name = "EnableHoloseat";
            this.EnableHoloseat.Size = new System.Drawing.Size(104, 17);
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
            this.HardwareType.Location = new System.Drawing.Point(81, 79);
            this.HardwareType.Name = "HardwareType";
            this.HardwareType.Size = new System.Drawing.Size(121, 21);
            this.HardwareType.TabIndex = 18;
            this.HardwareType.Text = "Leo";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(9, 87);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(53, 13);
            this.label7.TabIndex = 19;
            this.label7.Text = "Hardware";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(298, 55);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(68, 13);
            this.label6.TabIndex = 20;
            this.label6.Text = "Serial Output";
            this.label6.Click += new System.EventHandler(this.label6_Click);
            // 
            // Configuration
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(545, 375);
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
            this.Controls.Add(this.WalkKey);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Configuration";
            this.Text = "Holoseat Configuration";
            ((System.ComponentModel.ISupportInitialize)(this.TriggerSteps)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox WalkKey;
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
    }
}