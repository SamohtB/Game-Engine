using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using System.Globalization;
using System.IO;
using System;

enum WAHTypes : int
{
    NONE = 0,
    CUBE = 1,
    PLANE = 2,
    SPHERE = 3,
    CYLINDER = 4,
    CAPSULE = 5
}

public class WAHParser : EditorWindow
{
    private static string filePath = "Scenes/";
    private static string selectedFilePath = string.Empty;

    [MenuItem("Tools/Import .wah Scene")]
    public static void ShowWindow()
    {
        GetWindow<WAHParser>("Import .wah Scene");
    }

    private void OnGUI()
    {
        GUILayout.Label("Import .wah Scene", EditorStyles.boldLabel);

        if (GUILayout.Button("Select .wah File"))
        {
            selectedFilePath = EditorUtility.OpenFilePanel("Select .wah file", filePath, "wah");
        }

        GUILayout.Label("Selected File: " + selectedFilePath, EditorStyles.wordWrappedLabel);

        if (!string.IsNullOrEmpty(selectedFilePath) && GUILayout.Button("Load Scene"))
        {
            List<GameObject> objects = LoadWAHFile(selectedFilePath);
        }
    }

    private static List<GameObject> LoadWAHFile(string path)
    {
        List<GameObject> objects = new List<GameObject>();
        using (StreamReader reader = new StreamReader(path))
        {
            GameObject currentObject = null;
            string line;
            string n_name = null;
            WAHTypes n_type = WAHTypes.NONE;
            Vector3 n_position = Vector3.zero;
            Vector3 n_rotation = Vector3.zero;
            Vector3 n_scale = Vector3.one;
            bool n_rigidbody = false;

            int index = 0;

            while ((line = reader.ReadLine()) != null)
            {
                switch (index)
                {
                    /* Get Name */
                    case 0:
                        n_name = line;
                        index++;
                        break;

                    /* Get Primitive Type */
                    case 1:
                        if (Enum.TryParse(line.Substring(6).Trim(), out n_type))
                        {
                            currentObject = CreatePrimitive(n_type);
                        }
                        index++;
                        break;

                    /* Get Position */
                    case 2:
                        n_position = ParseVector3(line.Substring(10).Trim());
                        index++;
                        break;

                    /* Get Rotation */
                    case 3:
                        n_rotation = ParseVector3(line.Substring(10).Trim());
                        index++;
                        break;

                    /* Get Scale */
                    case 4:
                        n_scale = ParseVector3(line.Substring(7).Trim());
                        index++;
                        break;

                    case 5:
                        n_rigidbody = line.Substring(11).Trim() == "1";
                        index = 0;

                        /* Spawn and Set Transforms */
                        SetTransform(currentObject, n_name, n_position, n_rotation, n_scale, n_type, n_rigidbody);
                        objects.Add(currentObject);
                        break;
                }
            }
        }

        return objects;
    }

    private static GameObject CreatePrimitive(WAHTypes type)
    {
        switch (type)
        {
            case WAHTypes.CUBE: return GameObject.CreatePrimitive(PrimitiveType.Cube);
            case WAHTypes.PLANE: return GameObject.CreatePrimitive(PrimitiveType.Quad);
            case WAHTypes.SPHERE: return GameObject.CreatePrimitive(PrimitiveType.Sphere);
            case WAHTypes.CYLINDER: return GameObject.CreatePrimitive(PrimitiveType.Cylinder);
            case WAHTypes.CAPSULE: return GameObject.CreatePrimitive(PrimitiveType.Capsule);
            default: return null;
        }
    }

    private static Vector3 ParseVector3(string s)
    {
        string[] parts = s.Split(' ');
        return new Vector3(
            float.Parse(parts[0]),
            float.Parse(parts[1]),
            float.Parse(parts[2])
        );
    }

    private static void SetTransform(GameObject obj, string name, Vector3 position, Vector3 rotation, Vector3 scale, WAHTypes type, bool hasRigidbody)
    {
        if (obj == null) return;
        obj.transform.position = position;
        obj.transform.rotation = Quaternion.Euler(rotation);
        obj.transform.localScale = scale;
        obj.name = name;

        if (hasRigidbody)
        {
            obj.AddComponent<Rigidbody>();
        }
    }
}
