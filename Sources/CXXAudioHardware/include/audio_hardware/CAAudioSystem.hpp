//
// SPDX-FileCopyrightText: 2021 Stephen F. Booth <contact@sbooth.dev>
// SPDX-License-Identifier: MIT
//
// Part of https://github.com/sbooth/CXXAudioHardware
//

#pragma once

#include <audio_hardware/CAAudioObject.hpp>
#include <audio_hardware/CAAudioDevice.hpp>

namespace audio_hardware {

class CAAudioSystem : public CAAudioObject {
public:

	/// Creates an audio system object.
	CAAudioSystem() noexcept
	: CAAudioObject{kAudioObjectSystemObject}
	{}

	/// Copy constructor.
	CAAudioSystem(const CAAudioSystem& other) noexcept = default;

	/// Assignment operator.
	CAAudioSystem& operator=(const CAAudioSystem& other) noexcept = default;

	// Move constructor.
	CAAudioSystem(CAAudioSystem&& other) noexcept = default;

	// Move assignment operator.
	CAAudioSystem& operator=(CAAudioSystem&& other) noexcept = default;

	/// Destructor.
	virtual ~CAAudioSystem() = default;

	std::vector<AudioObjectID> DeviceIDs() const
	{
		return GetArrayProperty<AudioObjectID>(CAPropertyAddress(kAudioHardwarePropertyDevices));
	}

	std::vector<CAAudioDevice> Devices() const
	{
		const auto vec{DeviceIDs()};
		std::vector<CAAudioDevice> result{vec.size()};
		std::transform(vec.cbegin(), vec.cend(), result.begin(), [](AudioObjectID objectID) { return CAAudioDevice(objectID); });
		return result;
	}

	AudioObjectID DefaultInputDeviceID() const
	{
		return GetArithmeticProperty<AudioObjectID>(CAPropertyAddress(kAudioHardwarePropertyDefaultInputDevice));
	}

	CAAudioObject DefaultInputDevice() const
	{
		return CAAudioObject(DefaultInputDeviceID());
	}

	AudioObjectID DefaultOutputDeviceID() const
	{
		return GetArithmeticProperty<AudioObjectID>(CAPropertyAddress(kAudioHardwarePropertyDefaultOutputDevice));
	}

	CAAudioObject DefaultOutputDevice() const
	{
		return CAAudioObject(DefaultOutputDeviceID());
	}

	AudioObjectID DefaultSystemOutputDeviceID() const
	{
		return GetArithmeticProperty<AudioObjectID>(CAPropertyAddress(kAudioHardwarePropertyDefaultSystemOutputDevice));
	}

	CAAudioObject DefaultSystemOutputDevice() const
	{
		return CAAudioObject(DefaultSystemOutputDeviceID());
	}

	AudioObjectID AudioDeviceIDForUID(CFStringRef _Nonnull inUID) const
	{
		AudioObjectID deviceID;
		AudioValueTranslation valueTranslation{ &inUID, sizeof(CFStringRef), &deviceID, sizeof(AudioObjectID) };
		const CAPropertyAddress objectPropertyAddress{kAudioHardwarePropertyDeviceForUID};
		UInt32 size{sizeof(AudioValueTranslation)};
		GetPropertyData(objectPropertyAddress, 0, nullptr, size, &valueTranslation);
		return deviceID;
	}

	CAAudioDevice AudioDeviceForUID(CFStringRef _Nonnull inUID) const
	{
		return CAAudioDevice(AudioDeviceIDForUID(inUID));
	}

	//	kAudioHardwarePropertyMixStereoToMono                       = 'stmo',
	//	kAudioHardwarePropertyPlugInList                            = 'plg#',
	//	kAudioHardwarePropertyTranslateBundleIDToPlugIn             = 'bidp',
	//	kAudioHardwarePropertyTransportManagerList                  = 'tmg#',
	//	kAudioHardwarePropertyTranslateBundleIDToTransportManager   = 'tmbi',
	//	kAudioHardwarePropertyBoxList                               = 'box#',
	//	kAudioHardwarePropertyTranslateUIDToBox                     = 'uidb',
	//	kAudioHardwarePropertyClockDeviceList                       = 'clk#',
	//	kAudioHardwarePropertyTranslateUIDToClockDevice             = 'uidc',
	//	kAudioHardwarePropertyProcessIsMaster                       = 'mast',
	//	kAudioHardwarePropertyIsInitingOrExiting                    = 'inot',
	//	kAudioHardwarePropertyUserIDChanged                         = 'euid',
	//	kAudioHardwarePropertyProcessIsAudible                      = 'pmut',
	//	kAudioHardwarePropertySleepingIsAllowed                     = 'slep',
	//	kAudioHardwarePropertyUnloadingIsAllowed                    = 'unld',
	//	kAudioHardwarePropertyHogModeIsAllowed                      = 'hogr',
	//	kAudioHardwarePropertyUserSessionIsActiveOrHeadless         = 'user',
	//	kAudioHardwarePropertyServiceRestarted                      = 'srst',
	//	kAudioHardwarePropertyPowerHint                             = 'powh'
};

} /* namespace audio_hardware */
