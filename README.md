# CXXAudioHardware

Assorted C++ classes simplifying the use of Audio Hardware.

| Class | Description |
| --- | --- |
| [CAPropertyAddress](Sources/CXXAudioHardware/include/CXXAudioHardware/CAPropertyAddress.hpp) | Extends the functionality of an [`AudioObjectPropertyAddress`](https://developer.apple.com/documentation/coreaudio/audioobjectpropertyaddress?language=objc). |
| [CAAudioObject](Sources/CXXAudioHardware/include/audio_hardware/CAAudioObject.hpp) | A HAL audio object wrapper.|
| [CAAudioDevice](Sources/CXXAudioHardware/include/audio_hardware/CAAudioDevice.hpp) | A HAL audio device wrapper.|
| [CAAudioStream](Sources/CXXAudioHardware/include/audio_hardware/CAAudioStream.hpp) | A HAL audio stream wrapper.|
| [CAAudioSystem](Sources/CXXAudioHardware/include/audio_hardware/CAAudioSystem.hpp) | A `kAudioObjectSystemObject` wrapper.|

> [!NOTE]
> C++17 is required.

All classes are in the `audio_hardware` namespace.

This package depends on the [CXXCoreAudio](https://github.com/sbooth/CXXCoreAudio) package.

> [!TIP]
> For a complete Audio Hardware solution in Swift see [CAAudioHardware](https://github.com/sbooth/CAAudioHardware).

## Installation

### Swift Package Manager

Add a package dependency to https://github.com/sbooth/CXXAudioHardware in Xcode.

### Manual or Custom Build

1. Clone the [CXXAudioHardware](https://github.com/sbooth/CXXAudioHardware) repository.
2. `swift build`.

## License

Released under the [MIT License](https://github.com/sbooth/CXXAudioHardware/blob/main/LICENSE.txt).
