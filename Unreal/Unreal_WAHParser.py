import unreal

class WAHTypes:
    NONE = 0
    CUBE = 1
    PLANE = 2
    SPHERE = 3
    CYLINDER = 4
    CAPSULE = 5

def import_wah_scene(file_path):

    with open(file_path, 'r') as file:
        lines = file.readlines()
    
    current_object = {}
    folder_path = "SpawnedObjectsFolder"
    index = 0

    for line in lines:
        line = line.strip()
        if not line:
            continue
        
        if index == 0:  # Get Name
            current_object["name"] = line
            index += 1

        elif index == 1:  # Get Primitive Type
            type_str = line.split(":")[1].strip()
            if type_str == "1":
                current_object["type"] = 1  # Cube
            elif type_str == "2":
                current_object["type"] = 2  # Plane
            elif type_str == "3":
                current_object["type"] = 3  # Sphere
            elif type_str == "4":
                current_object["type"] = 4  # Cylinder
            elif type_str == "5":
                current_object["type"] = 5  # Capsule
            else:
                current_object["type"] = 0  # None
            index += 1

        elif index == 2:  # Get Position
            current_object["position"] = [float(x) for x in line.split(":")[1].strip().split()]
            # Swap y and z values and multiply by 100
            current_object["position"] = [current_object["position"][0] * 100, current_object["position"][2] * 100, current_object["position"][1] * 100]
            index += 1

        elif index == 3:  # Get Rotation (Quaternion)
            current_object["rotation"] = [float(x) for x in line.split(":")[1].strip().split()]
            # Swap y and z values
            current_object["rotation"] = [current_object["rotation"][0], current_object["rotation"][2], current_object["rotation"][1]]
            index += 1

        elif index == 4:  # Get Scale
            current_object["scale"] = [float(x) for x in line.split(":")[1].strip().split()]
            # Swap y and z values
            current_object["scale"] = [current_object["scale"][0], current_object["scale"][2], current_object["scale"][1]]
            index += 1

        elif index == 5:
            current_object["rigidbody"] = line[11:] == "1"

            create_actor(current_object, folder_path)
            current_object = {}
            index = 0


def create_actor(object_data, folder_path):
    actor_type = unreal.StaticMeshActor
    mesh_path = ""  # Default mesh path

    if object_data["type"] == 1:  # Cube
        mesh_path = "/Engine/BasicShapes/Cube.Cube"
    elif object_data["type"] == 2:  # Plane
        mesh_path = "/Engine/BasicShapes/Plane.Plane"
    elif object_data["type"] == 3:  # Sphere
        mesh_path = "/Engine/BasicShapes/Sphere.Sphere"
    elif object_data["type"] == 4:  # Cylinder
        mesh_path = "/Engine/BasicShapes/Cylinder.Cylinder"
    elif object_data["type"] == 5:  # Capsule
        mesh_path = "/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule"
    else:
        unreal.log_warning(f"Unknown type {object_data['type']} for object {object_data['name']}")
        return

    # Spawn the actor in the world
    world = unreal.EditorLevelLibrary.get_editor_world()
    location = unreal.Vector(*object_data["position"])
    rotation = unreal.Quat(*object_data["rotation"]).rotator()  # Convert quaternion to rotator
    scale = unreal.Vector(*object_data["scale"])

    if object_data["type"] == 2:
        rotation.roll += 180

    actor = unreal.EditorLevelLibrary.spawn_actor_from_class(actor_type, location, rotation)

    # Set the mesh for the actor
    static_mesh_component = actor.get_component_by_class(unreal.StaticMeshComponent)
    static_mesh = unreal.EditorAssetLibrary.load_asset(mesh_path)
    if static_mesh_component and static_mesh:
        static_mesh_component.set_static_mesh(static_mesh)

    # Apply scale to the actor
    actor.set_actor_scale3d(scale)

    # Add Rigidbody (Physics Component) if required
    if object_data.get("rigidbody", False):
        static_mesh_component.set_simulate_physics(True)

    # Set the actor's folder in the World Outliner
    actor.set_folder_path(folder_path)

    # Log the creation
    unreal.log(f"Created {object_data['name']} at {location} with scale {scale}")

input_file_name = "Scene_2_Unreal.wah"
input_directory = "D:\GitRepository\Game Engine\Scenes\\"
wah_file_path = f"{input_directory}{input_file_name}"
import_wah_scene(wah_file_path)