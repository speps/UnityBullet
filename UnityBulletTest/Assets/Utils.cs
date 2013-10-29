using UnityEngine;
using System.Collections;

public struct SimpleTransform
{
    public Vector3 position;
    public Quaternion rotation;

    public static SimpleTransform Inverse(SimpleTransform transform)
    {
        var invRot = Quaternion.Inverse(transform.rotation);
        return new SimpleTransform { position = invRot * -transform.position, rotation = invRot };
    }

    public static SimpleTransform operator*(SimpleTransform lhs, SimpleTransform rhs)
    {
        return new SimpleTransform {
            position = rhs.position,
            rotation = lhs.rotation * rhs.rotation
        };
    }
}