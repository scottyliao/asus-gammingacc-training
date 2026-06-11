using System;
using System.Collections.Generic;
using System.Text;

namespace Topic10_11_ReadWriteIniAndJsonFiles
{
    internal class ConfigDocument
    {
        public Dictionary<string, Dictionary<string, string>> Sections { get; } = new();
    }
}
