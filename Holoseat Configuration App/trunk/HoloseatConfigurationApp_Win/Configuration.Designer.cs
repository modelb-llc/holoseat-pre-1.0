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
            this.Save = new System.Windows.Forms.Button();
            this.Cancel = new System.Windows.Forms.Button();
            this.Result = new System.Windows.Forms.TextBox();
            this.SaveClose = new System.Windows.Forms.Button();
            this.UploadResult = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.SerialPortList = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this.TriggerSteps)).BeginInit();
            this.SuspendLayout();
            // 
            // WalkKey
            // 
            this.WalkKey.Location = new System.Drawing.Point(81, 79);
            this.WalkKey.Name = "WalkKey";
            this.WalkKey.Size = new System.Drawing.Size(173, 20);
            this.WalkKey.TabIndex = 1;
            this.WalkKey.TextChanged += new System.EventHandler(this.WalkKey_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 79);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Walk Key";
            // 
            // TriggerSteps
            // 
            this.TriggerSteps.Location = new System.Drawing.Point(81, 105);
            this.TriggerSteps.Maximum = 120;
            this.TriggerSteps.Name = "TriggerSteps";
            this.TriggerSteps.Size = new System.Drawing.Size(173, 45);
            this.TriggerSteps.TabIndex = 2;
            this.TriggerSteps.Scroll += new System.EventHandler(this.TriggerSteps_Scroll);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 105);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(66, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Trigger Rate";
            // 
            // TriggerStepsNumber
            // 
            this.TriggerStepsNumber.Location = new System.Drawing.Point(12, 130);
            this.TriggerStepsNumber.Name = "TriggerStepsNumber";
            this.TriggerStepsNumber.ReadOnly = true;
            this.TriggerStepsNumber.Size = new System.Drawing.Size(57, 20);
            this.TriggerStepsNumber.TabIndex = 4;
            this.TriggerStepsNumber.TabStop = false;
            // 
            // Save
            // 
            this.Save.Location = new System.Drawing.Point(12, 259);
            this.Save.Name = "Save";
            this.Save.Size = new System.Drawing.Size(75, 43);
            this.Save.TabIndex = 5;
            this.Save.Text = "Save";
            this.Save.UseVisualStyleBackColor = true;
            this.Save.Click += new System.EventHandler(this.Save_Click);
            // 
            // Cancel
            // 
            this.Cancel.Location = new System.Drawing.Point(179, 259);
            this.Cancel.Name = "Cancel";
            this.Cancel.Size = new System.Drawing.Size(75, 43);
            this.Cancel.TabIndex = 6;
            this.Cancel.Text = "Cancel";
            this.Cancel.UseVisualStyleBackColor = true;
            this.Cancel.Click += new System.EventHandler(this.Cancel_Click);
            // 
            // Result
            // 
            this.Result.Location = new System.Drawing.Point(12, 181);
            this.Result.Name = "Result";
            this.Result.ReadOnly = true;
            this.Result.Size = new System.Drawing.Size(242, 20);
            this.Result.TabIndex = 7;
            this.Result.TabStop = false;
            // 
            // SaveClose
            // 
            this.SaveClose.Location = new System.Drawing.Point(93, 259);
            this.SaveClose.Name = "SaveClose";
            this.SaveClose.Size = new System.Drawing.Size(75, 43);
            this.SaveClose.TabIndex = 8;
            this.SaveClose.Text = "Save and Close";
            this.SaveClose.UseVisualStyleBackColor = true;
            this.SaveClose.Click += new System.EventHandler(this.SaveClose_Click);
            // 
            // UploadResult
            // 
            this.UploadResult.AcceptsReturn = true;
            this.UploadResult.Location = new System.Drawing.Point(13, 233);
            this.UploadResult.Name = "UploadResult";
            this.UploadResult.ReadOnly = true;
            this.UploadResult.Size = new System.Drawing.Size(241, 20);
            this.UploadResult.TabIndex = 9;
            this.UploadResult.TabStop = false;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 165);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(65, 13);
            this.label3.TabIndex = 10;
            this.label3.Text = "Save Result";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(9, 217);
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
            // Configuration
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 308);
            this.Controls.Add(this.SerialPortList);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.UploadResult);
            this.Controls.Add(this.SaveClose);
            this.Controls.Add(this.Result);
            this.Controls.Add(this.Cancel);
            this.Controls.Add(this.Save);
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
        private System.Windows.Forms.Button Save;
        private System.Windows.Forms.Button Cancel;
        private System.Windows.Forms.TextBox Result;
        private System.Windows.Forms.Button SaveClose;
        private System.Windows.Forms.TextBox UploadResult;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox SerialPortList;
    }
}