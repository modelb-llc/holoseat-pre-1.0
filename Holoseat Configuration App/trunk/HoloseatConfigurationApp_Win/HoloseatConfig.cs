using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace HoloSeatConfig
{
    class HoloseatConfigurationFile
    {
        //Publically accessible variables for the number of steps constant and the walk command constant
        public double TriggerStepsPerMin;
        public char WalkCommandChar;
        public string SerialPort;


        //Location of the configuration file
        private const string ConstantsFile = @".\holoseat_firmware\holoseat_constants.h";
        private const string HoloseatFirmware= @".\holoseat_firmware\holoseat_firmware.ino";
        private const string Arguments = " --board arduino:avr:leonardo --port ";
        private const string ArduinoInstallLocation = @".\Arduino\arduino.exe";

        private const Boolean NoArduino = false;

        //Contructor for the class.  Searches the holoseat_firmware directory under where the program is stored to get the current settings
        //If the settings are found it sets them into the variables.  If they're missing it instead sets them to defaults of 75 steps per minute
        //and W.
        public HoloseatConfigurationFile()
        {
            try
            {
                using (StreamReader FileLine = new StreamReader(ConstantsFile))
                    while (FileLine.Peek() >= 0)
                    {
                        string CurrentLine = FileLine.ReadLine();
                        int EqualsPosition = CurrentLine.IndexOf("=");
                        if (EqualsPosition != -1)
                            switch (CurrentLine.Substring(0, EqualsPosition))
                            {
                                case "const float TriggerStepsPerMin ":
                                    {
                                        TriggerStepsPerMin = Convert.ToDouble(CurrentLine.Split('=')[1].Replace(';', ' ').Trim());
                                        break;
                                    }
                                case "const char WalkCommandChar ":
                                    {
                                        WalkCommandChar = Convert.ToChar(CurrentLine.Split('=')[1].Replace(';', ' ').Replace('\'',' ').Trim());
                                        break;
                                    }
                                case "//Serial Port ":
                                    {
                                        SerialPort=Convert.ToString(CurrentLine.Split('=')[1].Replace(';',' ').Trim());
                                        break;
                                    }
                            }
                    }
            }
            catch
            {
                TriggerStepsPerMin = 75;
                WalkCommandChar = 'W';
                SerialPort="COM0";
            }

        }
        
        //Update the configuration file specified in the constant above based on the current contents of TriggerStepsPerMin and WalkCommandchar.
        public string WriteConfiguration()
        {
            if (File.Exists(ConstantsFile))
            {
                File.Delete(ConstantsFile);
            }
            try
            {
                using (StreamWriter ConfigFile = new StreamWriter(ConstantsFile))
                {
                    ConfigFile.WriteLine("#ifndef holoseat_constants_h");
                    ConfigFile.WriteLine("#define holoseat_constants_h");
                    ConfigFile.WriteLine("const float TriggerStepsPerMin = " + TriggerStepsPerMin.ToString() + ";");
                    ConfigFile.WriteLine("const char WalkCommandChar = '" + WalkCommandChar.ToString() + "';");
                    ConfigFile.WriteLine("//Serial Port = " + SerialPort + ";");
                    ConfigFile.WriteLine("#endif");
                }
                return "Success";
            }
            catch(Exception e)
            {
                return e.ToString();
            }
        }

        //Pushes the configuration file to the Lenoardo so the settings are updated.
        public int UpdateHoloseat()
        {
            
            System.Diagnostics.Process ArduinoUpload = new System.Diagnostics.Process();
            ArduinoUpload.StartInfo.FileName = ArduinoInstallLocation;
            if (NoArduino==true)
            {
                ArduinoUpload.StartInfo.Arguments = "--verify ." + HoloseatFirmware;
            }
            else
            {
                ArduinoUpload.StartInfo.Arguments = Arguments + SerialPort + " " + "--upload ." + HoloseatFirmware;
            }
            ArduinoUpload.StartInfo.UseShellExecute = false;
            ArduinoUpload.StartInfo.RedirectStandardOutput = true;
            ArduinoUpload.Start();
            
            ArduinoUpload.WaitForExit();
            return ArduinoUpload.ExitCode;
        }
    }
}






