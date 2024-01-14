import os

Import("env")

CORESOURCE_DIR = env.subst("$PROJECT_DIR/src")
CORESOURCE_TAG = env.GetProjectOption("custom_core_firmware_version")
print("Compiling for Core Version: " + CORESOURCE_TAG)

if not os.path.exists(CORESOURCE_DIR):
    print ("Cloning Mobiflight-CustomDevices repo ... ")
    env.Execute(f"git clone --depth 1 --filter=blob:none --sparse --branch {CORESOURCE_TAG} https://github.com/MobiFlight/MobiFlight-FirmwareSource $PROJECT_DIR/src")
    env.Execute(f"git --work-tree=$PROJECT_DIR/src --git-dir=$PROJECT_DIR/src/.git sparse-checkout set _Boards src")
    if os.path.isfile(CORESOURCE_DIR + "/platformio.ini"):
        os.remove(CORESOURCE_DIR + "/platformio.ini")
else:
    print ("Checking for Mobiflight-CustomDevices repo updates ... ")
    env.Execute(f"git --work-tree=$PROJECT_DIR/src --git-dir=$PROJECT_DIR/src/.git pull origin {CORESOURCE_TAG} --depth 100")
