using System.Text.Json;

namespace Topic10_11_ReadWriteIniAndJsonFiles
{
    internal class JsonConfigFormat : IConfigFormat
    {
        public ConfigDocument Read(string path)
        {
            path = Path.GetFullPath(path);

            string json = File.ReadAllText(path);

            Dictionary<string, Dictionary<string, string>>? sections =
                JsonSerializer.Deserialize<Dictionary<string, Dictionary<string, string>>>(json);

            var document = new ConfigDocument();

            if (sections == null)
            {
                return document;
            }

            foreach (var section in sections)
            {
                document.Sections[section.Key] = section.Value;
            }

            return document;
        }

        public void Write(string path, ConfigDocument document)
        {
            path = Path.GetFullPath(path);

            var options = new JsonSerializerOptions
            {
                WriteIndented = true
            };

            string json = JsonSerializer.Serialize(document.Sections, options);

            File.WriteAllText(path, json);
        }
    }
}
