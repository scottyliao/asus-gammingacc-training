using System.Runtime.InteropServices;

namespace Topic10_11_ReadWriteIniAndJsonFiles
{
    internal class IniConfigFormat : IConfigFormat
    {
        [DllImport("kernel32.dll", CharSet = CharSet.Unicode)]
        private static extern int GetPrivateProfileString(
            string? section,
            string? key,
            string? defaultValue,
            char[] returnValue,
            int size,
            string filePath);

        [DllImport("kernel32.dll", CharSet = CharSet.Unicode)]
        private static extern bool WritePrivateProfileString(
            string? section,
            string? key,
            string? value,
            string filePath);
        public ConfigDocument Read(string path)
        {
            path = Path.GetFullPath(path);

            var document = new ConfigDocument();

            char[] sectionBuffer = new char[32767];

            int sectionCount = GetPrivateProfileString(
                null,
                null,
                null,
                sectionBuffer,
                sectionBuffer.Length,
                path);

            string rawSections = new string(sectionBuffer, 0, sectionCount);

            string[] sections = rawSections.Split(
                '\0',
                StringSplitOptions.RemoveEmptyEntries);

            foreach (string section in sections)
            {
                document.Sections[section] = new Dictionary<string, string>();

                char[] keyBuffer = new char[32767];

                int keyCount = GetPrivateProfileString(
                    section,
                    null,
                    null,
                    keyBuffer,
                    keyBuffer.Length,
                    path);

                string rawKeys = new string(keyBuffer, 0, keyCount);

                string[] keys = rawKeys.Split(
                    '\0',
                    StringSplitOptions.RemoveEmptyEntries);

                foreach (string key in keys)
                {
                    char[] valueBuffer = new char[32767];

                    int valueCount = GetPrivateProfileString(
                        section,
                        key,
                        "",
                        valueBuffer,
                        valueBuffer.Length,
                        path);

                    string value = new string(valueBuffer, 0, valueCount);

                    document.Sections[section][key] = value;
                }
            }

            return document;
        }

        public void Write(string path, ConfigDocument document)
        {
            path = Path.GetFullPath(path);

            foreach (var section in document.Sections)
            {
                foreach (var item in section.Value)
                {
                    WritePrivateProfileString(section.Key, item.Key, item.Value, path);
                }
            }
        }
    }
}
