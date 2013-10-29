using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;

namespace BulletDotNet
{
    internal static partial class Imports
    {
        [DllImport(Imports.DLLName)]
        public static extern IntPtr biCreateDiscreteDynamicsWorld();
        [DllImport(Imports.DLLName)]
        public static extern void biDestroyDiscreteDynamicsWorld(HandleRef worldHandle);

        [DllImport(Imports.DLLName)]
        public static extern void biAddRigidBody(HandleRef worldHandle, HandleRef rigidBodyHandle);
        [DllImport(Imports.DLLName)]
        public static extern void biRemoveRigidBody(HandleRef worldHandle, HandleRef rigidBodyHandle);

        [DllImport(Imports.DLLName)]
        public static extern void biDynamicsWorldSetGravity(HandleRef worldHandle, Vector3 gravity);
        [DllImport(Imports.DLLName)]
        public static extern int biDynamicsWorldGetObjectsCount(HandleRef worldHandle);

        [DllImport(Imports.DLLName)]
        public static extern void biStepSimulation3(HandleRef worldHandle, float timeStep, int maxSubSteps, float fixedTimeStep);
    }

    public class DiscreteDynamicsWorld
    {
        internal IntPtr m_handle;
        IList<RigidBody> m_rigidBodies;

        public DiscreteDynamicsWorld()
        {
            m_handle = Imports.biCreateDiscreteDynamicsWorld();
            m_rigidBodies = new List<RigidBody>();
        }

        ~DiscreteDynamicsWorld()
        {
            Imports.biDestroyDiscreteDynamicsWorld(new HandleRef(this, m_handle));
            m_handle = IntPtr.Zero;
        }

        public Vector3 Gravity
        {
            set { Imports.biDynamicsWorldSetGravity(new HandleRef(this, m_handle), value); }
        }

        public int Count
        {
            get { return Imports.biDynamicsWorldGetObjectsCount(new HandleRef(this, m_handle)); }
        }

        public void AddRigidBody(RigidBody rigidBody)
        {
            if (m_rigidBodies.Contains(rigidBody))
            {
                throw new ArgumentException("RigidBody already added");
            }
            Imports.biAddRigidBody(new HandleRef(this, m_handle), new HandleRef(rigidBody, rigidBody.m_handle));
            m_rigidBodies.Add(rigidBody);
        }

        public void RemoveRigidBody(RigidBody rigidBody)
        {
            if (!m_rigidBodies.Contains(rigidBody))
            {
                throw new ArgumentException("RigidBody was not added");
            }
            m_rigidBodies.Remove(rigidBody);
            Imports.biRemoveRigidBody(new HandleRef(this, m_handle), new HandleRef(rigidBody, rigidBody.m_handle));
        }

        public void StepSimulation(float timeStep, int maxSubSteps = 1, float fixedTimeStep = 1.0f / 60.0f)
        {
            Imports.biStepSimulation3(new HandleRef(this, m_handle), timeStep, maxSubSteps, fixedTimeStep);
        }
    }
}
