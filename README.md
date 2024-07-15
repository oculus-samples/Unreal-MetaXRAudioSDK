# Project Overview

This repo contains a reference app showcasing the uses of the Meta XR Audio plug-in for Unreal. From the main level, users can launch various other levels via a UI menu that showcase different features of the Meta XR Audio plug-in for Unreal.

An overview for using Meta's Presence Platform Audio SDK in Unreal can be found [here](https://developer.oculus.com/documentation/unreal/meta-xr-audio-sdk-unreal-req-setup/).

# How to Use

## Prerequisites

### A Windows Machine
Currently the plug-in only supports Windows development.

### Visual Studio

Launch the Visual Studio Installer and click Modify for the Visual Studio version you want to use. Under the Workloads tab, click Game development with C++ if it isn’t checked and then click Modify.

### Developer Mode Enabled Quest Device
The project in this repository can be be compiled and installed onto Developer Mode Enabled Quest devices. Instructions for enabling developer mode on your Quest device can be found [here](https://developer.oculus.com/documentation/native/android/mobile-device-setup/#enable-developer-mode).

### Install Unreal Engine using one of the following options:

#### Epic Games Launcher with MetaXR plugin

The easiest way to get started is to use the prebuilt Unreal Engine from the Epic Games Launcher, with MetaXR plugin.

1. Install the [Epic Games Launcher](https://www.epicgames.com/store/en-US/download)
2. Using the launcher, install UE5. Make sure the UE5 version you install is compatible with the UE version specified in the MetaXRAudioSample.uproject file of this repo.
3. Download the MetaXR plugin from the [Unreal Engine 5 Integration download page](https://developer.oculus.com/downloads/package/unreal-engine-5-integration). Follow the instructions on that page to install the Meta XR Plug-in into the UE5 version you installed in step 2. Make sure the Meta XR Plug-in you download is compatible with the UE version you installed in step 2 (you may have to use the "Version" drop down menu to select previous versions).
3. Launch the Unreal Editor.
4. From "Recent Projects", click "Browse" and select the `MetaXRAudioSample.uproject` file of this repo.

#### Oculus Unreal fork

The Oculus Unreal fork will give you the most up to date integration of Oculus features. However, you must build the editor from its source.

Follow the instructions on [Accessing Unreal Engine source code on GitHub](https://www.unrealengine.com/en-US/ue-on-github) to obtain:
- an Epic account
- a GitHub account
- authorization to access the Unreal Engine source repository
Disregard instructions on downloading Epic’s Unreal Engine source code as you will be building the Oculus-VR fork of Unreal Engine source.

Make sure you have Visual Studio installed properly:
- Launch the Visual Studio Installer and click Modify for the Visual Studio version you want to use.
- Under the Workloads tab, click Game development with C++ if it isn’t checked and then click Modify.

1. Download the source code from the [Oculus-VR fork of Unreal Engine on GitHub](https://github.com/Oculus-VR/UnrealEngine). Checkout the branch of that repo that corresponds to the UE version specified in the MetaXRAudioSample.uporject file of this repo.
2. Follow Epic’s instructions on [Building Unreal Engine from Source](https://docs.unrealengine.com/5.2/en-US/building-unreal-engine-from-source/) to complete the process.

Depending on your machine, the build may take a while to complete.

### [Optional] Setup Oculus Link

It's suggested to use Oculus Link when in the Unreal Editor. Instructions for using Oculus Link can be found [here](https://developer.oculus.com/documentation/unreal/unreal-link/).

### Install Meta Presence Platform XR Audio Plug-in

1. First [download the Unreal plug-in from the Oculus Developer Center](https://developer.oculus.com/downloads/package/meta-xr-audio-unreal/).
1. Once downloaded, extract the .zip to a local folder on your machine.
1. The downloaded SDK package contains a sub-folder titled “Unreal” and inside it the plugin is found in a folder named “MetaXRAudio”. Copy that plugin folder to “UnrealEnginePath\Engine\Plugins\Marketplace" to add it to your engine installation.

Up-to-date instructions to download and install the Meta Presence Platform XR Audio Plug-in can be found [here](https://developer.oculus.com/documentation/unreal/meta-xr-audio-sdk-unreal-req-setup/).

### Load the project

First, ensure you have Git LFS installed by running this command:
```sh
git lfs install
```

Then, clone this repo using the "Code" button above, or this command:
```sh
git clone https://github.com/oculus-samples/Unreal-MetaXRAudioSDK
```

## Building

### [Optional] Bake all lightmaps
Once the project is loaded, you might see a warning to rebake all lighting. To fix this warning (and make the demo look better when built):

1. Filter the content browser and only display levels.
1. Open each level listed with the filter applied and go to "Build" -> "Build All Levels"
1. Make sure to save the level.

### Build the .apk
1. To build the .apk, go to the Platforms Button -> Android -> Package Product.
1. Choose any folder you want for the build destination and click "Ok".

The project should build successfully.

## Running
1. Make sure you quest device is connected to your machine via USB-C cable
1. Locate the build folder you specified above. In the ANDROID_ASTC folder, you'll find a `Install_MetaXRAudioSample-Android-Shipping-arm64.bat` file (or similarly named). Double click that batch file to automatically install the .apk to your device.
1. Open the application through your Quest device's App Library. The application will likely be listed under the **Unknown Sources** section.

# LICENSES

The Unreal-MetaXRAudioSDK repository including all packages and SDKs, is released under the Oculus SDK License.  You may obtain a copy of the SDK License at https://developer.oculus.com/licenses/oculussdk/

Helicopter audio samples are sourced from https://github.com/viktorphoenix/fieldrecordings-ccby4.  The License for the helicopter audio samples can be found in the Third-party folder.
