using BulletDotNet;
using UnityEngine;
using System.Diagnostics;

public class BulletWorld : MonoBehaviour
{
    DiscreteDynamicsWorld m_world = new DiscreteDynamicsWorld();
    Stopwatch m_timer = new Stopwatch();

    public DiscreteDynamicsWorld World { get { return m_world; } }

    void Start()
    {
        m_world.Gravity = new BulletDotNet.Vector3 {
            X = Physics.gravity.x,
            Y = Physics.gravity.y,
            Z = Physics.gravity.z
        };
    }

    void FixedUpdate()
    {
        m_timer.Reset();
        m_timer.Start();
        m_world.StepSimulation(Time.fixedDeltaTime);
        m_timer.Stop();
    }

    void OnGUI()
    {
        GUI.Label(new Rect(0.0f, 0.0f, 200.0f, 100.0f), string.Format("rigidbodies:{0}\nstep (ms):{1}", m_world.Count, m_timer.Elapsed.TotalMilliseconds));
    }
}
