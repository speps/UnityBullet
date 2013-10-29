using UnityEngine;
using System.Collections;

public class PlacementGrid : MonoBehaviour
{
    public int numX, numY, numZ;
    public Vector3 spacing;
    public GameObject placedObject;

    void Start()
    {
        Vector3 bounds = spacing;
        bounds.Scale(new Vector3(numX, numY, numZ));

        Vector3 origin = -bounds * 0.5f;

        for (int x = 0; x < numX; x++)
        {
            for (int y = 0; y < numY; y++)
            {
                for (int z = 0; z < numZ; z++)
                {
                    var position = transform.position + origin + spacing * 0.5f + transform.rotation * new Vector3(x * spacing.x, y * spacing.y, z * spacing.z);
                    Object.Instantiate(placedObject, position, transform.rotation);
                }
            }
        }
    }

    void Update()
    {
    }

    void OnDrawGizmos()
    {
        Vector3 bounds = spacing;
        bounds.Scale(new Vector3(numX, numY, numZ));

        Vector3 origin = transform.position - bounds * 0.5f;

        Gizmos.color = Color.red;
        Vector3 axisStart = origin;
        Vector3 axisEnd = origin + transform.rotation * new Vector3(0.0f, bounds.y, 0.0f);
        for (int i = 0; i <= numX; i++)
        {
            Gizmos.DrawLine(axisStart, axisEnd);
            axisStart += transform.rotation * new Vector3(spacing.x, 0.0f, 0.0f);
            axisEnd += transform.rotation * new Vector3(spacing.x, 0.0f, 0.0f);
        }

        Gizmos.color = Color.green;
        axisStart = origin;
        axisEnd = origin + transform.rotation * new Vector3(0.0f, 0.0f, bounds.z);
        for (int i = 0; i <= numY; i++)
        {
            Gizmos.DrawLine(axisStart, axisEnd);
            axisStart += transform.rotation * new Vector3(0.0f, spacing.y, 0.0f);
            axisEnd += transform.rotation * new Vector3(0.0f, spacing.y, 0.0f);
        }

        Gizmos.color = Color.blue;
        axisStart = origin;
        axisEnd = origin + transform.rotation * new Vector3(bounds.x, 0.0f, 0.0f);
        for (int i = 0; i <= numZ; i++)
        {
            Gizmos.DrawLine(axisStart, axisEnd);
            axisStart += transform.rotation * new Vector3(0.0f, 0.0f, spacing.z);
            axisEnd += transform.rotation * new Vector3(0.0f, 0.0f, spacing.z);
        }
    }
}
