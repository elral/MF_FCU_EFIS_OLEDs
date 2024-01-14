Import("env")
import os, zipfile, shutil
from pathlib import Path

# Get the version number from the build environment.
firmware_version = os.environ.get('VERSION', "")
if firmware_version == "":
    firmware_version = "0.0.1"
firmware_version = firmware_version.lstrip("v")
firmware_version = firmware_version.strip(".")

# Get the ZIP filename from the build environment.
community_project = env.GetProjectOption('custom_community_project', "")

# Get the custom folder from the build environment.
custom_device_folder = env.GetProjectOption('custom_device_folder', "")


def copy_fw_files (source, target, env):
    fw_file_name=str(target[0])

    if os.path.exists("./_build/" + custom_device_folder) == False:
        os.makedirs("./_build/" + custom_device_folder + "/Community/firmware")
        shutil.copytree(custom_device_folder + "/Community", "./_build/" + custom_device_folder + "/Community", dirs_exist_ok=True)
        print("Creating Folder and copying community folder")
    
    if fw_file_name[-3:] == "bin":
        fw_file_name=fw_file_name[0:-3] + "uf2"

    shutil.copy(fw_file_name, "./_build/" + custom_device_folder + "/Community/firmware")
    createCommunityZipFile(source, target, env)

def createCommunityZipFile(source, target, env):
    original_folder_path = "./_build/" + custom_device_folder + "/Community"
    zip_file_path = './_dist/' + community_project + '_' + firmware_version + '.zip'
    new_folder_in_zip = community_project
    createZIP(original_folder_path, zip_file_path, new_folder_in_zip)

def createZIP(original_folder_path, zip_file_path, new_folder_name):
    if os.path.exists("./_dist") == False:
        os.mkdir("./_dist")
    with zipfile.ZipFile(zip_file_path, 'w') as zipf:
        for root, dirs, files in os.walk(original_folder_path):
            for file in files:
                # Create a new path in the ZIP file
                new_path = os.path.join(new_folder_name, os.path.relpath(os.path.join(root, file), original_folder_path))
                # Add the file to the ZIP file
                zipf.write(os.path.join(root, file), new_path)


env.AddPostAction("$BUILD_DIR/${PROGNAME}.hex", copy_fw_files)
env.AddPostAction("$BUILD_DIR/${PROGNAME}.bin", copy_fw_files)
#env.AddPostAction("checkprogsize", createCommunityZipFile)
#env.AddCustomTarget("create_community_zip", None, createCommunityZipFile)