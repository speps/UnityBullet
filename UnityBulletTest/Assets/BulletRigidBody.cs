using UnityEngine;
using BulletDotNet;

public class BulletRigidBody : MonoBehaviour
{
    RigidBody m_rigidBody;
    bool m_added = false;

    public float mass;
    public UnityEngine.Vector3 centerOfMass;
    public float friction;

    void Start()
    {
        var boxCollider = GetComponent<BoxCollider>();
        var boxSize = UnityEngine.Vector3.Scale(boxCollider.size, transform.lossyScale);
        var boxHalfExtents = new BulletDotNet.Vector3 {
            X = boxSize.x * 0.5f,
            Y = boxSize.y * 0.5f,
            Z = boxSize.z * 0.5f
        };

        var info = new RigidBodyConstructionInfo();
        info.Mass = mass;
        info.CollisionShape = new BulletDotNet.Shapes.BoxShape(boxHalfExtents);
        info.CenterOfMass = new BulletDotNet.Vector3 { X = centerOfMass.x, Y = centerOfMass.y, Z = centerOfMass.z };
        info.Friction = friction;
        info.LinearDamping = 0.1f;
        info.LinearSleepingThreshold = 0.01f;
        m_rigidBody = new RigidBody(info, OnGetTransform, OnSetTransform);

        AddRigidBody();
    }

    void OnEnable()
    {
        AddRigidBody();
    }

    void OnDisable()
    {
        RemoveRigidBody();
    }

    void OnDestroy()
    {
        RemoveRigidBody();
    }

    void OnApplicationQuit()
    {
        RemoveRigidBody();
    }

    void AddRigidBody()
    {
        if (!m_added && m_rigidBody != null)
        {
            var worldGameObject = GameObject.FindGameObjectWithTag("BulletWorld");
            var world = worldGameObject.GetComponent<BulletWorld>();
            world.World.AddRigidBody(m_rigidBody);
            m_added = true;
        }
    }

    void RemoveRigidBody()
    {
        if (m_added && m_rigidBody != null)
        {
            var worldGameObject = GameObject.FindGameObjectWithTag("BulletWorld");
            var world = worldGameObject.GetComponent<BulletWorld>();
            world.World.RemoveRigidBody(m_rigidBody);
            m_added = false;
        }
    }

    private void OnGetTransform(out BulletDotNet.Vector3 position, out BulletDotNet.Quaternion rotation)
    {
        position = new BulletDotNet.Vector3(transform.position.x, transform.position.y, transform.position.z);
        rotation = new BulletDotNet.Quaternion(transform.rotation.x, transform.rotation.y, transform.rotation.z, transform.rotation.w);
    }

    private void OnSetTransform(BulletDotNet.Vector3 position, BulletDotNet.Quaternion rotation)
    {
        transform.position = new UnityEngine.Vector3(position.X, position.Y, position.Z);
        transform.rotation = new UnityEngine.Quaternion(rotation.X, rotation.Y, rotation.Z, rotation.W);
    }

    void Update()
    {

    }
}
