using System.Data;

namespace Trg.Setup.Utility;

public class CLI
{
    public static bool GetUserConfirmation(string prompt)
    {
        Console.Write($"{prompt} [y/n]: ");

        while (true)
        {
            string? res = Console.ReadLine();
            switch (res)
            {
                case "y": case "yes":
                    return true;
                case "n": case "no":
                    return false;
            }

            Console.Write("Incorrect input. Please, try again [y/n]: ");
        }
    }

    public static int RunCommandSilently(string cmd, string args)
    {
        var proc = new System.Diagnostics.Process();
        proc.StartInfo.FileName = cmd;
        proc.StartInfo.Arguments = args;
        proc.StartInfo.UseShellExecute = false;
        proc.StartInfo.RedirectStandardError = true;
        proc.StartInfo.RedirectStandardError = true;
        proc.StartInfo.CreateNoWindow = true;

        proc.Start();
        proc.WaitForExit();

        return proc.ExitCode;
    }
}
