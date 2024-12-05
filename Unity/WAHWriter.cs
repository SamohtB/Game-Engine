using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using System.IO;

public class WAHWriter : EditorWindow
{
    [MenuItem("Tools/Save Scene as .wah")]

    public static void WriteWAHFile()
    {
        string path = EditorUtility.SaveFilePanel("Save Scene As .wah", "", "NewScene.wah", "wah");

        if (path.Length != 0)
        {
            StreamWriter writer = new StreamWriter(path);

            GameObject[] allObjects = FindObjectsOfType<GameObject>();

            foreach (GameObject obj in allObjects)
            {
                if (obj.GetComponent<MeshFilter>() == null) continue;

                // Write object name
                writer.WriteLine(obj.name);

                int typeValue = (int)GetWAHType(obj);
                writer.WriteLine("Type: " + typeValue);

                // Write position
                Vector3 position = obj.transform.position;
                writer.WriteLine("Position: " + position.x + " " + position.y + " " + position.z);

                // Write rotation
                Vector3 rotation = obj.transform.rotation.eulerAngles;
                writer.WriteLine("Rotation: " + rotation.x + " " + rotation.y + " " + rotation.z);

                // Write scale
                Vector3 scale = obj.transform.localScale;
                writer.WriteLine("Scale: " + scale.x + " " + scale.y + " " + scale.z);

                // Write if has rigidbody
                if (obj.GetComponent<Rigidbody>())
                {
                    writer.WriteLine("Rigidbody: 1");
                }
                else
                {
                    writer.WriteLine("Rigidbody: 0");
                }
            }

            writer.Close();
            Debug.Log("Scene exported to " + path);
        }
    }

    private static WAHTypes GetWAHType(GameObject obj)
    {
        if (obj.GetComponent<MeshFilter>() != null)
        {
            Mesh mesh = obj.GetComponent<MeshFilter>().sharedMesh;

            if (mesh == null) return WAHTypes.NONE;

            if (mesh.name == "Cube")
                return WAHTypes.CUBE;
            else if (mesh.name == "Quad")
                return WAHTypes.PLANE;
            else if (mesh.name == "Sphere")
                return WAHTypes.SPHERE;
            else if (mesh.name == "Cylinder")
                return WAHTypes.CYLINDER;
            else if (mesh.name == "Capsule")
                return WAHTypes.CAPSULE;
        }

        return WAHTypes.NONE;
    }

}
