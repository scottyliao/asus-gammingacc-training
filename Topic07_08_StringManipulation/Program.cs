using System.Text;
namespace Topic07_08_StringManipulation
{
    internal class Program
    {
        static void Main(string[] args)
        {
            // Register the code page for Big5 encoding
            Encoding.RegisterProvider(CodePagesEncodingProvider.Instance);

            // The ANSI byte array representing the string.
            // "Device:ROG Spatha|Firmware:v1.02.08|Light:目前燈效|Status:連線狀態".
            byte[] ansiBytes = {
                68, 101, 118, 105, 99,
                101, 58, 82, 79, 71,
                32, 83, 112, 97, 116,
                104, 97, 32, 88, 124,
                70, 105, 114, 109, 119,
                97, 114, 101, 58, 118,
                49, 46, 48, 50, 46, 48,
                56, 124, 76, 105, 103,
                104, 116, 58, 169, 73,
                167, 108, 191, 79, 124,
                83, 116, 97, 116, 117,
                115, 58, 164, 119, 179,
                115, 189, 117
            };

            // Decode the ANSI byte array to a Unicode string using Big5 encoding.
            string decodedString = Encoding.GetEncoding("big5").GetString(ansiBytes);

            Console.WriteLine("原本ANSI => Unicode字串：\n" + decodedString + "\n\n\n");

            // Due to the performance of string manipulation, 
            // use StringBuilder to form the string instead.
            StringBuilder sb = new StringBuilder();
            Dictionary<string, string> dict = new Dictionary<string, string>();
            dict.Add("Device", "裝置名稱");
            dict.Add("Firmware", "韌體版本");
            dict.Add("Light", "目前燈效");
            dict.Add("Status", "連線狀態");

            Console.WriteLine("透過Split和StringBuilder拼接後的字串：\n");
            sb.AppendLine("======= ASUS ROG 裝置狀態 =======");
            
            //Use '|' and ':' to split the string.
            foreach (string str in decodedString.Split('|'))
            {
                string[] splitWithColon = str.Split(':');
                sb.Append(dict[splitWithColon[0]]);
                sb.Append(" => ");
                sb.AppendLine(splitWithColon[1]);
            }
            sb.AppendLine("=================================");
            
            Console.WriteLine(sb.ToString());
        }
    }
}