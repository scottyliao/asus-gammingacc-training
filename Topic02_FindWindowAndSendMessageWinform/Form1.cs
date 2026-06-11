using System.Runtime.InteropServices;

namespace Topic02_FindWindowAndSendMessageWinform
{
    public partial class Form1 : Form
    {
        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        private static extern IntPtr SendMessage(IntPtr hWnd, uint Msg, IntPtr wParam, ref COPYDATASTRUCT lParam);

        private const uint WM_COPYDATA = 0x004A;

        private string targetWindowTitle = "Node B";

        [StructLayout(LayoutKind.Sequential)]
        public struct COPYDATASTRUCT
        {
            public IntPtr dwData;
            public int cbData;
            public IntPtr lpData;
        }
        public Form1()
        {
            InitializeComponent();
            Text = "Node A";
            targetWindowTitle = "Node B";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string textToSend = textBox1.Text;
            if (string.IsNullOrEmpty(textToSend)) return;

            // 動態尋找目標（看現在誰是對方）
            IntPtr hwndTarget = FindWindow(null, targetWindowTitle);

            if (hwndTarget != IntPtr.Zero)
            {
                IntPtr lpszText = Marshal.StringToHGlobalUni(textToSend);
                int cbData = (textToSend.Length + 1) * 2;

                COPYDATASTRUCT cds;
                cds.dwData = (IntPtr)555;
                cds.cbData = cbData;
                cds.lpData = lpszText;

                SendMessage(hwndTarget, WM_COPYDATA, this.Handle, ref cds);
                Marshal.FreeHGlobal(lpszText);

                listBox1.Items.Add($"[發送] 傳給 {targetWindowTitle}: {textToSend}");
            }
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            Text = "Node A";
            targetWindowTitle = "Node B";
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            Text = "Node B";
            targetWindowTitle = "Node A";
        }

        protected override void WndProc(ref Message m)
        {
            if (m.Msg == WM_COPYDATA)
            {
                COPYDATASTRUCT cds = (COPYDATASTRUCT)Marshal.PtrToStructure(m.LParam, typeof(COPYDATASTRUCT));
                string receivedText = Marshal.PtrToStringUni(cds.lpData);

                // 顯示是誰傳給我的
                listBox1.Items.Add($"[接收] 來自 {targetWindowTitle}: {receivedText}");

                m.Result = (IntPtr)1;
                return;
            }
            base.WndProc(ref m);
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
