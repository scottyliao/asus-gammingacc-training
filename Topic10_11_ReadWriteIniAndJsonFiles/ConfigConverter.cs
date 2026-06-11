namespace Topic10_11_ReadWriteIniAndJsonFiles
{
    internal class ConfigConverter
    {
        public static void Convert(
            string sourcePath,
            IConfigFormat sourceFormat,
            string targetPath,
            IConfigFormat targetFormat)
        {
            ConfigDocument document = sourceFormat.Read(sourcePath);
            targetFormat.Write(targetPath, document);
            Console.WriteLine("Conversion completed successfully.");
        }
    }
}
