using System;
using System.IO;
//using System.IO.Ports;
using RJCP.IO.Ports;

namespace HoloSeatConfig
{
    class HoloseatConfigurationFile
    {
        //Publically accessible variables for the number of steps constant and the walk command constant
        public double TriggerStepsPerMin;
        public char WalkCommandChar;
        public string SerialPort;
        public string HardwareType; //Valid types as of this version are "feather" for the Adafruit feather boards or "leo" for the Arduino Leonardo board
        public string SerialLog;
        public Boolean HoloSeatOn;

        //Location of the configuration file
        private const string ConstantsFile = @".\holoseat_firmware\holoseat_constants.h";
        private const string HoloseatFirmware= @".\holoseat_firmware\holoseat_firmware.ino";
        private string Arguments = " --board arduino:avr:leonardo --port ";
        private const string ArduinoInstallLocation = @".\Arduino\arduino.exe";
        private const int DebugEnable = 0;
        private const int DebugRate = 10;

        private const Boolean NoArduino = false;

        //Contructor for the class.  Searches the holoseat_firmware directory under where the program is stored to get the current settings
        //If the settings are found it sets them into the variables.  If they're missing it instead sets them to defaults of 75 steps per minute
        //and W.
        public HoloseatConfigurationFile()
        {           
            TriggerStepsPerMin = 75;
            WalkCommandChar = 'W';
            SerialPort = "COM0";
            HardwareType = "leo";
            using (StreamReader FileLine = new StreamReader(ConstantsFile))
                while (FileLine.Peek() >= 0)
                {
                    string CurrentLine = FileLine.ReadLine();
                    int EqualsPosition = CurrentLine.IndexOf("=");
                    if (EqualsPosition != -1)
                        switch (CurrentLine.Substring(0, EqualsPosition))
                        {
                            case "const unsigned int DefaultTriggerCadence ":
                                {
                                    TriggerStepsPerMin = Convert.ToDouble(CurrentLine.Split('=')[1].Replace(';', ' ').Trim());
                                    break;
                                }
                            case "const char DefaultWalkCharacter ":
                                {
                                    WalkCommandChar = Convert.ToChar(CurrentLine.Split('=')[1].Replace(';', ' ').Replace('\'', ' ').Trim());
                                    break;
                                }
                            case "//Serial Port ":
                                {
                                    SerialPort = Convert.ToString(CurrentLine.Split('=')[1].Replace(';', ' ').Trim());
                                    break;
                                }
                            case "//Hardware Type ":
                                {
                                    HardwareType = Convert.ToString(CurrentLine.Split('=')[1].Replace(';', ' ').Trim());
                                    break;
                                }

                        }
                }
           SetArguments();
            if (Arguments == "Invalid" & HardwareType!="") {
                System.Windows.Forms.MessageBox.Show("Unknown hardware.  Closing program.", "Unsupported Hardware");
                Configuration.ActiveForm.Close();
            }
            HoloSeatOn = true;
        }
        //Set the arguments string based on the available hardware types
        private void SetArguments()
        {
            switch (HardwareType)
            {
                case "feather":
                    {
                        Arguments = " --board adafruit:avr:feather32u4 --port ";
                        break;
                    }
                case "leo":
                    {
                        Arguments = " --board arduino:avr:leonardo --port ";
                        break;
                    }
                default:
                    {

                        Arguments = "Invalid";
                        break;
                    }               
            }
        }
        
        //send an update to the holoseat through serial to change settings.
        public string SendConfig()
        {
            String ConfigString;
            Boolean SendCommandResult;
            // String format <WC>,<E>,<TC>,<L>,<LI> - example: S t,0,60,0,20
            ConfigString = "S " + WalkCommandChar + "," + HoloSeatEnable() + "," + TriggerStepsPerMin + "," + DebugEnable + "," + DebugRate;
            SendCommandResult = SendCommandToSerial(ConfigString);
            return SerialLog;
        }

        private int HoloSeatEnable()
        {
            if (HoloSeatOn) {
                return 1;
            }
            else{
                return 0;
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
                    ConfigFile.WriteLine("");
                    ConfigFile.WriteLine("// default parameter values for Holoseat");
                    ConfigFile.WriteLine("  // What key is sent to move the character in the game");                
                    ConfigFile.WriteLine("const char DefaultWalkCharacter = '" + WalkCommandChar.ToString() + "';");
                    ConfigFile.WriteLine("  // Is the Holoseat enabled by default?");
                    ConfigFile.WriteLine("const unsigned int DefaultHoloseatEnabled = " + HoloSeatEnable().ToString() + ";");
                    ConfigFile.WriteLine("  // How fast does the user need to pedal (in RPM) to trigger walking?");
                    ConfigFile.WriteLine("const unsigned int DefaultTriggerCadence = " + TriggerStepsPerMin.ToString() + ";");
                    ConfigFile.WriteLine("  // Is serial logging enabled by default?");
                    ConfigFile.WriteLine("const unsigned int DefaultLoggingEnabled = 0;");
                    ConfigFile.WriteLine("  // How long between messages in serial logging in deci-seconds (0.1 of a second)");
                    ConfigFile.WriteLine("const unsigned int DefaultLoggingInterval = 10;");
                    ConfigFile.WriteLine("");
                    ConfigFile.WriteLine("//Holoseat Configurator Variables");
                    ConfigFile.WriteLine("//Hardware Type = " + HardwareType + ";");
                    ConfigFile.WriteLine("//Serial Port = " + SerialPort + ";");
                    ConfigFile.WriteLine("");
                    ConfigFile.WriteLine("// other boot parameters");
                    ConfigFile.WriteLine("const unsigned int SerialBaudRate = 57600;");
                    ConfigFile.WriteLine("#endif");
                }
                return "Success";
            }
            catch(Exception e)
            {
                return e.ToString();
            }
        }
        private Boolean SendCommandToSerial(string CommandString)
        {
            string ReturnLine;
            string PortID = SerialPort;
            Boolean Result = true;
//            System.IO.Ports.SerialPort MyPort = new System.IO.Ports.SerialPort(PortID);
            SerialPortStream MyPort = new SerialPortStream();
            MyPort.PortName = PortID;
            MyPort.BaudRate = 9600;
            MyPort.DataBits = 8;
            MyPort.Parity = Parity.None;
            MyPort.StopBits = StopBits.One;
            MyPort.Handshake = Handshake.None;
            MyPort.ReadTimeout = 5000;
            MyPort.WriteTimeout = 5000;
            SerialLog = "Opening Port " + PortID + System.Environment.NewLine;
            MyPort.Open();
            //System.Threading.Thread.Sleep(1000);
            if (MyPort.IsOpen == true)
            {
                SerialLog = SerialLog + ("COM Port open" + System.Environment.NewLine);
                SerialLog = SerialLog + ("Asking Holoseat if it is ready" + System.Environment.NewLine);                   
                MyPort.WriteLine("?");
                System.Threading.Thread.Sleep(500);
                ReturnLine = MyPort.ReadExisting();
                SerialLog = SerialLog + (ReturnLine);
                if (ReturnLine.Length > 0)  //If nothing returns, holoseat not present on port
                {
                    if (ReturnLine.Substring(1, 1) != "R")
                    {
                        Result = false;

                    }
                    SerialLog = SerialLog + ("Sending selected output" + System.Environment.NewLine);
                    MyPort.WriteLine(CommandString);
                    System.Threading.Thread.Sleep(500);
                    ReturnLine = MyPort.ReadExisting();
                    SerialLog = SerialLog + (ReturnLine);
                    if (ReturnLine.Substring(1, 2) != "OK")
                    {
                        Result = false;
                    }
                }
                MyPort.Close();
                return Result;

            }
            else
            {
                return false;
            }
        }

        //Pushes the configuration file to the Lenoardo so the settings are updated.
        public int UpdateHoloseat()
        {
            SetArguments();
            WriteConfiguration();
            System.Diagnostics.Process ArduinoUpload = new System.Diagnostics.Process();
            ArduinoUpload.StartInfo.FileName = ArduinoInstallLocation;
            if (NoArduino==true)
            {
                ArduinoUpload.StartInfo.Arguments = "--verify ." + HoloseatFirmware;
            }
            else
            {
                ArduinoUpload.StartInfo.Arguments = Arguments + SerialPort + " " + "--upload " + HoloseatFirmware;
            }
            ArduinoUpload.StartInfo.UseShellExecute = false;
            ArduinoUpload.StartInfo.RedirectStandardOutput = true;
            ArduinoUpload.Start();
            
            ArduinoUpload.WaitForExit();
            return ArduinoUpload.ExitCode;
        }
    }
}






