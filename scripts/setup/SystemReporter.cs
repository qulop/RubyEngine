namespace Trg.Setup;

public class SystemReporter
{
    private SystemReporter() 
    {}


    public static void PrintIntro(SystemInfo systemInfo)
    {
        Console.WriteLine(@"            
     _______   _                         ______             _                  __  ____        _ _     _             
    |__   __| (_)                       |  ____|           (_)                / / |  _ \      (_) |   | |            
       | |_ __ _  __ _  __ _  ___ _ __  | |__   _ __   __ _ _ _ __   ___     / /  | |_) |_   _ _| | __| | ___ _ __   
       | | '__| |/ _` |/ _` |/ _ \ '__| |  __| | '_ \ / _` | | '_ \ / _ \   / /   |  _ <| | | | | |/ _` |/ _ \ '__|  
       | | |  | | (_| | (_| |  __/ |    | |____| | | | (_| | | | | |  __/  / /    | |_) | |_| | | | (_| |  __/ |     
       |_|_|  |_|\__, |\__, |\___|_|    |______|_| |_|\__, |_|_| |_|\___| /_/     |____/ \__,_|_|_|\__,_|\___|_|     
                  __/ | __/ |                          __/ |                                                         
     ______ _____|___/_|___/____ ______ ______ ______ |___/_ ______ ______ ______ ______ ______ ______ ______ ______ 
    |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|                                              
        ");

        Console.WriteLine($"-- OS: X{systemInfo.OSBitDepth} {systemInfo.OSName}");
        Console.WriteLine($"-- OS Version: {systemInfo.OSVersion}");
        Console.WriteLine($"-- CPU Architecture: {systemInfo.CpuArchitecture}");
        Console.WriteLine($"-- Logical Processors: {systemInfo.CpuThreadsCount}");
    }
}
