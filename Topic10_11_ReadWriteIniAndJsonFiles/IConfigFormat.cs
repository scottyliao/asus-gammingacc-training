namespace Topic10_11_ReadWriteIniAndJsonFiles
{
    internal interface IConfigFormat
    {
        ConfigDocument Read(string path);
        void Write(string path, ConfigDocument document);
    }
}
