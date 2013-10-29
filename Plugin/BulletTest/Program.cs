using System;
using BulletDotNet;

namespace BulletTest
{
    class Program
    {
        static Vector3 rbPosition0 = Vector3.Zero;
        static Quaternion rbRotation0 = Quaternion.Identity;
        static Vector3 rbPosition1 = new Vector3(1.9f, -2.0f, 0.0f);
        static Quaternion rbRotation1 = Quaternion.Identity;

        static void OnGetTransform0(out Vector3 position, out Quaternion rotation)
        {
            position = rbPosition0;
            rotation = rbRotation0;
        }

        static void OnSetTransform0(Vector3 position, Quaternion rotation)
        {
            rbPosition0 = position;
            rbRotation0 = rotation;
            Console.WriteLine("T {0} R {1}", position, rotation);
        }

        static void OnGetTransform1(out Vector3 position, out Quaternion rotation)
        {
            position = rbPosition1;
            rotation = rbRotation1;
        }

        static void OnSetTransform1(Vector3 position, Quaternion rotation)
        {
            rbPosition1 = position;
            rbRotation1 = rotation;
        }

        static void Main(string[] args)
        {
            {
                var world = new DiscreteDynamicsWorld();
                world.Gravity = new Vector3(0.0f, -10.0f, 0.0f);

                var info0 = new RigidBodyConstructionInfo();
                info0.Mass = 1.0f;
                info0.CollisionShape = new BulletDotNet.Shapes.BoxShape(Vector3.One);
                info0.CenterOfMass = Vector3.Zero;
                var rb0 = new RigidBody(info0, OnGetTransform0, OnSetTransform0);

                var info1 = new RigidBodyConstructionInfo();
                info1.Mass = 0.0f;
                info1.CollisionShape = new BulletDotNet.Shapes.BoxShape(Vector3.One);
                info1.CenterOfMass = Vector3.Zero;
                var rb1 = new RigidBody(info1, OnGetTransform1, OnSetTransform1);

                world.AddRigidBody(rb0);
                world.AddRigidBody(rb1);

                for (int i = 0; i < 100; i++)
                {
                    rb0.Activate();
                    world.StepSimulation(1.0f / 60.0f);
                }

                world.RemoveRigidBody(rb0);
                world.RemoveRigidBody(rb1);
            }

            GC.Collect();
            GC.WaitForPendingFinalizers();
        }
    }
}
