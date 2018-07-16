using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Threading;

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
        Modes mode = Modes.CompInfo;

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
            // Check com status
            if (serialPort.IsOpen)
                Console.WriteLine("Success!\n");
            else
            {
                Console.WriteLine("Fail.\n");
                Environment.Exit(1);
            }

            // Clear screen
            ClearScreen();

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
    }
}
