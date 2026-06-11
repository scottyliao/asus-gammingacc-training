using System.Runtime.InteropServices;

namespace Topic09_CallbackFunctionWithNumericDllLibrary
{
    internal class Program
    {
        // Define a delegate that matches the signature of the callback function
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate double function(double x);

        // Import the integrate function from the NumericLib.dll
        [DllImport("NumericLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double integrate(function f, double a, double b, int count);
        static void Main(string[] args)
        {
            function f = (x) => x * x; // Define the function to integrate (f(x) = x^2)

            // Calulate the area of f(x) from 0 to 3
            double area = integrate(f, 0.0, 3.0, 1000);
            Console.WriteLine($"The integration is {area}");
        }
    }
}