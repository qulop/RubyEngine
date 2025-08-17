using Trg.Setup.Utility;


namespace Trg.Setup;

public class CMake
{
    public static bool IsInstalled()
        => CLI.RunCommandSilently("cmake", "--version") == 0;


    public static bool Install(string osNmae)
    {
        return false;
    }
}
