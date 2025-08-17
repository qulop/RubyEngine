using Trg.Setup;


Console.CancelKeyPress += (_, _) =>
{
    Console.WriteLine("\n\nSetup was interrupted - aborting...");
    EngineSetup.AbortSetup();
};


var engineSetup = new EngineSetup();
engineSetup.CheckCMake();



