using Trg.Setup.Utility;

namespace Trg.Setup;

class EngineSetup
{
    private const string NINJA_GENERATOR_NAME = "Ninja";

    private readonly SystemInfo _systemInfo;

    public static void AbortSetup()
    {
        Console.WriteLine("--- Setup was aborted due to error");
        System.Environment.Exit(1);
    }

    public EngineSetup()
    {
        _systemInfo = SystemInfo.FetchInfo();
        if (_systemInfo.OSBitDepth == 32)
        {
            Console.WriteLine("Sorry, but TrgEngine running only on 64-bit systems");
            AbortSetup();
        }

        SystemReporter.PrintIntro(_systemInfo);
    }

    public void CheckCMake()
    {
        Console.Write("-- Checking CMake for availability... ");
        if (CLI.RunCommandSilently("cmake", "--version") != 0)
        {
            Console.WriteLine("CMake isn't installed");
            AbortSetup();
        }

        Console.WriteLine("Ok");
    }

    public void CheckCompiler()
    {
        Console.Write("-- Trying to find a C++ compiler... ");
    }



    private string? SelectGenerator()
    {
        if (CLI.RunCommandSilently("ninja", "--version") == 0)
        {
            return NINJA_GENERATOR_NAME;
        }

        return null;
    }
}