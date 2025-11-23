using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

class Program
{
    // ----------------- Win32 imports -----------------
    [DllImport("user32.dll")]
    static extern IntPtr GetForegroundWindow();

    [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
    static extern int GetWindowText(IntPtr hWnd, StringBuilder lpString, int nMaxCount);

    [DllImport("user32.dll", CharSet = CharSet.Auto)]
    static extern int GetWindowTextLength(IntPtr hWnd);

    [DllImport("user32.dll")]
    static extern uint GetWindowThreadProcessId(IntPtr hWnd, out uint pid);

    [DllImport("user32.dll")]
    static extern int GetClassName(IntPtr hWnd, StringBuilder lpClassName, int nMaxCount);

    static void Main()
    {
        string output = "";
        var task = Task.Run(() => GetActiveWindow()); //Create a get ctive window task
                                                      //Because if win32 API hangs, we may end current iteration

        if (task.Wait(1000)) // wait max 1 sec
        {
            output = task.Result;
        }
        else
        {
            // Timed out
            output = "";
        }

        Console.WriteLine(output);
        Console.Out.Flush(); // immediate flush for C++ pipe
                             // prevents console freezes
    }

    static string GetActiveWindow()
    {
        IntPtr hwnd = GetForegroundWindow();
        if (hwnd == IntPtr.Zero)
            return "";

        // Filter system/UWP windows by class name
        StringBuilder className = new StringBuilder(256);
        GetClassName(hwnd, className, className.Capacity);
        string cls = className.ToString();

        //Skip system processed
        if (cls == "ApplicationFrameWindow" ||
            cls == "Windows.UI.Core.CoreWindow" ||
            cls == "ImmersiveShell")
            return "";

        // Window title safely
        string title = "";
        try
        {
            int length = GetWindowTextLength(hwnd);
            if (length > 0)
            {
                StringBuilder sb = new StringBuilder(length + 1);
                GetWindowText(hwnd, sb, sb.Capacity);
                title = sb.ToString();
            }
        }
        catch { title = ""; }

        // Process name  (if possible)
        string procName = "";
        try
        {
            uint pid; // declare before
            //Get proccess by pid
            GetWindowThreadProcessId(hwnd, out pid);
            var proc = Process.GetProcessById((int)pid);
            procName = proc.ProcessName;
        }
        catch { procName = ""; }

        //Return with  "|" important so we can seperate in the c++ GetCurrentWindow.cpp while outputting
        return procName + "|" + title;
    }
}
