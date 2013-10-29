using System.Runtime.InteropServices;

namespace BulletDotNet
{
    internal static partial class Imports
    {
#if DEBUG
        public const string DLLName = "BulletInterfaceDebug";
#else
        public const string DLLName = "BulletInterfaceRelease";
#endif
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct Vector3
    {
        public float X, Y, Z;

        public static readonly Vector3 Zero = new Vector3(0.0f, 0.0f, 0.0f);
        public static readonly Vector3 One = new Vector3(1.0f, 1.0f, 1.0f);

        public Vector3(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public override string ToString()
        {
            return string.Format("{0}, {1}, {2}", X, Y, Z);
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct Quaternion
    {
        public float X, Y, Z, W;

        public static readonly Quaternion Identity = new Quaternion(0.0f, 0.0f, 0.0f, 1.0f);

        public Quaternion(float x, float y, float z, float w)
        {
            X = x;
            Y = y;
            Z = z;
            W = w;
        }

        public override string ToString()
        {
            return string.Format("{0}, {1}, {2}, {3}", X, Y, Z, W);
        }
    }
}
