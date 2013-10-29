using System;
using System.Runtime.InteropServices;

namespace BulletDotNet.Shapes
{
    internal static partial class Imports
    {
        [DllImport(BulletDotNet.Imports.DLLName)]
        public static extern void biDestroyCollisionShape(HandleRef collisionShapeHandle);
    }

    public class CollisionShape
    {
        internal IntPtr m_handle;

        protected CollisionShape(IntPtr handle)
        {
            m_handle = handle;
        }

        ~CollisionShape()
        {
            Imports.biDestroyCollisionShape(new HandleRef(this, m_handle));
            m_handle = IntPtr.Zero;
        }
    }
}
