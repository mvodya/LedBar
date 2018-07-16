using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Threading;
using System.Diagnostics;

namespace LedbarService
{
    class Program
    {
        // Serial port
        static SerialPort serialPort;
        // Port for opening
        static string connectPort = "COM4";
        // Display modes
        enum Modes
        {
            CompInfo = 1
        }
        // Display mode
        static Modes mode = Modes.CompInfo;

        // Data
        static PerformanceCounter cpuCounter;
        static PerformanceCounter ramCounter;

        static void Main(string[] args)
        {
            // Greetings
            Console.WriteLine("LedBar Service");

            // Print all available ports
            Console.WriteLine("\nAvailable ports:");
            string[] ports = SerialPort.GetPortNames();
            foreach (string port in ports)
            {
                Console.WriteLine(port);
            }

            // Open serial port
            Console.WriteLine("\nOpening " + connectPort + "...");
            serialPort = new SerialPort(connectPort, 9600, Parity.None, 8, StopBits.One);
            serialPort.Open();
            //serialPort.DtrEnable = true;
            // Check com status
            if (serialPort.IsOpen)
                Console.WriteLine("Success!\n");
            else
            {
                Console.WriteLine("Fail.\n");
                Environment.Exit(1);
            }

            // Data loading
            DataLoad();

            // Clear screen and backlight
            ClearScreen();
            Backlight(true);
            

            // Start main loop
            ServiceLoop();

            // Pause (debug)
            Console.ReadKey();
        }

        // Main service loop
        static void ServiceLoop()
        {
            while (serialPort.IsOpen)
            {
                switch (mode)
                {
                    // Comp info
                    case Modes.CompInfo:
                        ModeCopmInfo();
                        break;
                }
                Thread.Sleep(50);
            }

            // Port closed
            Console.WriteLine("Port closed. Turn off service");
            serialPort.Close();
            Environment.Exit(0);
        }

        // Clear dispay screen
        static void ClearScreen()
        {
            serialPort.Write("CLSC;");
        }

        // Backlight control
        static void Backlight(bool state)
        {
            if (state)
            {
                serialPort.Write("BLCN;");
            }
            else
            {
                serialPort.Write("BLCF;");
            }
        }

        // Write screen
        static void WriteScreen(int pos, string message)
        {
            serialPort.Write("WRSC" + pos + message + ";");
        }

        static void DataLoad()
        {
            cpuCounter = new PerformanceCounter("Processor", "% Processor Time", "_Total");
            ramCounter = new PerformanceCounter("Memory", "Available MBytes");
        }

        // MODE CompInfo
        static void ModeCopmInfo()
        {
            string cpu = Convert.ToString(Convert.ToInt32(cpuCounter.NextValue()));
            if (cpu.Length == 2) cpu = " " + cpu;
            else if (cpu.Length == 1) cpu = "  " + cpu;

            WriteScreen(0, "CPU:" + cpu + "% RAM: " + Convert.ToString(Convert.ToInt32(ramCounter.NextValue())) + "M");
            string bar = "[";
            for (int i = 0; i < 18; i++)
            {
                if (i < (Convert.ToInt32(cpu) / 5))
                {
                    bar += "|";
                } else
                {
                    bar += " ";
                }
            }
            WriteScreen(1, bar + "]");
            WriteScreen(3, DateTime.Now.ToString("HH:mm:ss"));
            
            Thread.Sleep(1000);
        }
    }
}
