import os

Import("env")

CORESOURCE = "https://github.com/MobiFlight/MobiFlight-FirmwareSource"
CORESOURCE_DIR = env.subst("$PROJECT_DIR/src")
CORESOURCE_TAG = env.GetProjectOption("custom_core_firmware_version")
print("Compiling for Core Version: " + CORESOURCE_TAG)

if not os.path.exists(CORESOURCE_DIR):
    print ("Cloning Mobiflight-Firmware repo ... ")
    env.Execute(f'git clone --depth 1 --filter=blob:none --sparse --branch {CORESOURCE_TAG} "{CORESOURCE}" "{CORESOURCE_DIR}"')
    env.Execute(f'git --work-tree="{CORESOURCE_DIR}" --git-dir="{CORESOURCE_DIR}/.git" sparse-checkout set _Boards src')
    if os.path.isfile(CORESOURCE_DIR + "/platformio.ini"):
        os.remove(CORESOURCE_DIR + "/platformio.ini")
else:
    print ("Checking for Mobiflight-Firmware repo updates ... ")
    env.Execute(f'git --work-tree="{CORESOURCE_DIR}" --git-dir="{CORESOURCE_DIR}/.git" pull origin {CORESOURCE_TAG} --depth 100')
