using System;
using System.Runtime.InteropServices;

namespace BulletDotNet.Shapes
{
    internal static partial class Imports
    {
        [DllImport(BulletDotNet.Imports.DLLName)]
        public static extern IntPtr biCreateBoxShape(Vector3 boxHalfExtents);
    }

    public class BoxShape : CollisionShape
    {
        public BoxShape(Vector3 boxHalfExtents)
            : base(Imports.biCreateBoxShape(boxHalfExtents))
        {

        }
    }
}
