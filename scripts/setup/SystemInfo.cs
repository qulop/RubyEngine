using Microsoft.Win32;
using System.Runtime.InteropServices;


namespace Trg.Setup;


public struct SystemInfo(string osName, string osVersion, int osBitDepth, string cpuArch, int cpuThreadsCount)
{
    public string OSName { get; } = osName;
    public string OSVersion { get; } = osVersion;
    public int OSBitDepth { get; } = osBitDepth;
    public string CpuArchitecture { get; } = cpuArch;
    public int CpuThreadsCount { get; } = cpuThreadsCount;


    public static SystemInfo FetchInfo()
    {
        var osName = Environment.OSVersion.Platform.ToString();
        var osVersion = Environment.OSVersion.Version.ToString();
        int osBitDepth = Environment.Is64BitOperatingSystem ? 64 : 32;
        var cpuArch = RuntimeInformation.OSArchitecture.ToString();
        int cpuThreadsCount = Environment.ProcessorCount;


        return new SystemInfo(osName, osVersion, osBitDepth, cpuArch, cpuThreadsCount);
    }
}