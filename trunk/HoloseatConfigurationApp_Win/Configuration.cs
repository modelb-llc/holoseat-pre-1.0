using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.IO.Ports;

namespace HoloSeatConfig
{
    public partial class Configuration : Form

    {
        private HoloseatConfigurationFile HoloConfig = new HoloseatConfigurationFile(); 
        public Configuration()
        {
            InitializeComponent();
            WalkKey.Text = HoloConfig.WalkCommandChar.ToString();
            TriggerSteps.Value = Convert.ToInt16(HoloConfig.TriggerStepsPerMin);
            TriggerStepsNumber.Text = TriggerSteps.Value.ToString();
            int x = 1;

            foreach (string s in SerialPort.GetPortNames())
            {
                SerialPortList.Items.Add(s);
                if (x==1)  
                    SerialPortList.SelectedItem = s;

            }
            if (HoloConfig.SerialPort != "COM0")
            {
                SerialPortList.SelectedValue = HoloConfig.SerialPort;
            }
            else
            {
                HoloConfig.SerialPort = SerialPortList.SelectedItem.ToString();
            }


        }

        private void TriggerSteps_Scroll(object sender, EventArgs e)
        {
            TriggerStepsNumber.Text = TriggerSteps.Value.ToString();
        }



        private void UpdateHoloseat_Click(object sender, EventArgs e)
        {           
            HoloConfig.TriggerStepsPerMin = TriggerSteps.Value;
            HoloConfig.WalkCommandChar = Convert.ToChar(WalkKey.Text);
            HoloConfig.SerialPort = SerialPortList.SelectedItem.ToString();
            HoloConfig.HardwareType = HardwareType.SelectedItem.ToString();
            SerialOutput.Text = HoloConfig.SendConfig();
            //Original code which executed a reprogram.  Being replaced with code to talk to the serial port.
            //Result.Text = HoloConfig.WriteConfiguration();
            //UpdateResult = HoloConfig.UpdateHoloseat();
            //switch (UpdateResult)
            //{
            //    case 0:
            //        UploadResult.Text = "Success";
            //        break;
            //    default:
            //        UploadResult.Text = "Failed to upload(Error code:" + UpdateResult.ToString() + ").";
            //        break;
            //}
        }

        private void UpdateDefaults_Click(object sender, EventArgs e)
        {
            Result.Text = "";
            UploadResult.Text = "";
            int UpdateResult;
            HoloConfig.TriggerStepsPerMin = TriggerSteps.Value;
            HoloConfig.WalkCommandChar = Convert.ToChar(WalkKey.Text);
            HoloConfig.SerialPort = SerialPortList.SelectedItem.ToString();
            HoloConfig.HardwareType = HardwareType.SelectedItem.ToString();
            string SaveResult;
            SaveResult = HoloConfig.WriteConfiguration();
            UpdateResult = HoloConfig.UpdateHoloseat();
            switch (UpdateResult)
            {
                case 0:
                    UploadResult.Text="Success";
                    break;
                default:
                    UploadResult.Text="Failed to upload(Error code:"+ UpdateResult.ToString()+").";
                    break;
            }
            Result.Text = SaveResult;

        }

        private void WalkKey_TextChanged(object sender, EventArgs e)
        {
            if (WalkKey.TextLength>1)
                WalkKey.Text=WalkKey.Text.Substring(1,1);

        }

        private void Close_Click(object sender, EventArgs e)
        {
            ActiveForm.Close();
        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void EnableHoloseat_CheckedChanged(object sender, EventArgs e)
        {
            if (EnableHoloseat.Checked)
            {
                HoloConfig.HoloSeatOn = true;
            }
            else
            {
                HoloConfig.HoloSeatOn = false;
            }
        }
    }
}
