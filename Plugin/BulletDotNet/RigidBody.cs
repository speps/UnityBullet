using System;
using System.Runtime.InteropServices;

namespace BulletDotNet
{
    internal static partial class Imports
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct biRigidBodyConstructionInfo
        {
            public float m_mass;
            public IntPtr m_collisionShape;
            public float m_linearDamping;
            public float m_angularDamping;
            public float m_friction;
            public float m_rollingFriction;
            public float m_restitution;
            public float m_linearSleepingThreshold;
            public float m_angularSleepingThreshold;
        }

        public delegate void biMotionStateGetTransform(IntPtr userData, ref Vector3 outPosition, ref Quaternion outRotation);
        public delegate void biMotionStateSetTransform(IntPtr userData, Vector3 inPosition, Quaternion inRotation);

        [DllImport(Imports.DLLName)]
        public static extern IntPtr biCreateRigidBody(ref biRigidBodyConstructionInfo info, IntPtr userData, IntPtr get, IntPtr set);
        [DllImport(Imports.DLLName)]
        public static extern void biDestroyRigidBody(HandleRef rigidBodyHandle);

        [DllImport(Imports.DLLName)]
        public static extern void biActivateRigidBody(HandleRef rigidBodyHandle);
    }

    public struct RigidBodyConstructionInfo
    {
        public float Mass;
        public Shapes.CollisionShape CollisionShape;
        public Vector3 CenterOfMass;
        public float LinearDamping;
        public float AngularDamping;
        public float Friction;
        public float RollingFriction;
        public float Restitution;
        public float LinearSleepingThreshold;
        public float AngularSleepingThreshold;
    }

    public class RigidBody
    {
        internal IntPtr m_handle;
        private RigidBodyConstructionInfo m_info;
        private Imports.biMotionStateGetTransform m_getDelegate;
        private Imports.biMotionStateSetTransform m_setDelegate;

        public RigidBody(RigidBodyConstructionInfo info, RigidBody.GetTransformDelegate get, RigidBody.SetTransformDelegate set)
        {
            m_info = info;
            OnGetTransform = get;
            OnSetTransform = set;

            var biInfo = new Imports.biRigidBodyConstructionInfo();
            biInfo.m_mass = m_info.Mass;
            biInfo.m_collisionShape = m_info.CollisionShape.m_handle;
            biInfo.m_linearDamping = m_info.LinearDamping;
            biInfo.m_angularDamping = m_info.AngularDamping;
            biInfo.m_friction = m_info.Friction;
            biInfo.m_rollingFriction = m_info.RollingFriction;
            biInfo.m_restitution = m_info.Restitution;
            biInfo.m_linearSleepingThreshold = m_info.LinearSleepingThreshold;
            biInfo.m_angularSleepingThreshold = m_info.AngularSleepingThreshold;

            m_getDelegate = MotionStateGetTransform;
            m_setDelegate = MotionStateSetTransform;

            m_handle = Imports.biCreateRigidBody(ref biInfo, IntPtr.Zero, Marshal.GetFunctionPointerForDelegate(m_getDelegate), Marshal.GetFunctionPointerForDelegate(m_setDelegate));
        }

        ~RigidBody()
        {
            Imports.biDestroyRigidBody(new HandleRef(this, m_handle));
            m_handle = IntPtr.Zero;
        }

        public void Activate()
        {
            Imports.biActivateRigidBody(new HandleRef(this, m_handle));
        }

        public delegate void GetTransformDelegate(out Vector3 position, out Quaternion rotation);
        public delegate void SetTransformDelegate(Vector3 position, Quaternion rotation);

        public GetTransformDelegate OnGetTransform;
        public SetTransformDelegate OnSetTransform;

        private void MotionStateGetTransform(IntPtr userData, ref Vector3 outPosition, ref Quaternion outRotation)
        {
            if (OnGetTransform != null)
            {
                Vector3 position;
                Quaternion rotation;
                OnGetTransform(out position, out rotation);
                outPosition = position;
                outRotation = rotation;
            }
        }

        private void MotionStateSetTransform(IntPtr userData, Vector3 position, Quaternion rotation)
        {
            if (OnSetTransform != null)
            {
                OnSetTransform(position, rotation);
            }
        }
    }
}
