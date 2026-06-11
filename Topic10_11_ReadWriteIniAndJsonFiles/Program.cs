namespace Topic10_11_ReadWriteIniAndJsonFiles
{
    internal class Program
    {
        static void Main(string[] args)
        {
            ConfigConverter.Convert(
                "AnotherConfig.json",
                new JsonConfigFormat(),
                "AnotherConfig.ini",
                new IniConfigFormat()
                );
        }
    }
}