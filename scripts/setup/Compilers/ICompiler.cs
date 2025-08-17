namespace Trg.Setup.Compilers;


public interface ICompiler
{
    public bool IsAvailable();

    public int? GetMajorVersion();

    public string? GetVersion();
}
