//
// SPDX-FileCopyrightText: 2021 Stephen F. Booth <contact@sbooth.dev>
// SPDX-License-Identifier: MIT
//
// Part of https://github.com/sbooth/CXXAudioHardware
//

#pragma once

#include <audio_hardware/CAAudioObject.hpp>
#include <audio_hardware/CAAudioStream.hpp>

namespace audio_hardware {

class CAAudioDevice : public CAAudioObject {
public:

	using CAAudioObject::CAAudioObject;

	//	kAudioDevicePropertyConfigurationApplication        = 'capp',

	CFStringRef CopyUID() const CF_RETURNS_RETAINED
	{
		return CopyCFTypeProperty<CFStringRef>(CAPropertyAddress(kAudioDevicePropertyDeviceUID));
	}

	CFStringRef CopyModelUID() const CF_RETURNS_RETAINED
	{
		return CopyCFTypeProperty<CFStringRef>(CAPropertyAddress(kAudioDevicePropertyModelUID));
	}

	//	kAudioDevicePropertyTransportType                   = 'tran',
	//	kAudioDevicePropertyRelatedDevices                  = 'akin',
	//	kAudioDevicePropertyClockDomain                     = 'clkd',
	//	kAudioDevicePropertyDeviceIsAlive                   = 'livn',
	//	kAudioDevicePropertyDeviceIsRunning                 = 'goin',
	//	kAudioDevicePropertyDeviceCanBeDefaultDevice        = 'dflt',
	//	kAudioDevicePropertyDeviceCanBeDefaultSystemDevice  = 'sflt',

	UInt32 Latency(CAAudioObjectDirectionalScope scope) const
	{
		return GetArithmeticProperty<UInt32>(CAPropertyAddress(kAudioDevicePropertyLatency, scope == CAAudioObjectDirectionalScope::input ? kAudioObjectPropertyScopeInput : kAudioObjectPropertyScopeOutput));
	}

	std::vector<AudioObjectID> StreamIDs(CAAudioObjectDirectionalScope scope) const
	{
		return GetArrayProperty<AudioObjectID>(CAPropertyAddress(kAudioDevicePropertyStreams, scope == CAAudioObjectDirectionalScope::input ? kAudioObjectPropertyScopeInput : kAudioObjectPropertyScopeOutput));
	}

	std::vector<CAAudioStream> Streams(CAAudioObjectDirectionalScope scope) const
	{
		auto vec{StreamIDs(scope)};
		std::vector<CAAudioStream> result{vec.size()};
		std::transform(vec.cbegin(), vec.cend(), result.begin(), [](AudioObjectID objectID) { return CAAudioStream(objectID); });
		return result;
	}

	//	kAudioObjectPropertyControlList                     = 'ctrl',

	UInt32 SafetyOffset(CAAudioObjectDirectionalScope scope) const
	{
		return GetArithmeticProperty<UInt32>(CAPropertyAddress(kAudioDevicePropertySafetyOffset, scope == CAAudioObjectDirectionalScope::input ? kAudioObjectPropertyScopeInput : kAudioObjectPropertyScopeOutput));
	}

	Float64 NominalSampleRate() const
	{
		return GetArithmeticProperty<Float64>(CAPropertyAddress(kAudioDevicePropertyNominalSampleRate));
	}

	//	kAudioDevicePropertyAvailableNominalSampleRates     = 'nsr#',
	//	kAudioDevicePropertyIcon                            = 'icon',
	//	kAudioDevicePropertyIsHidden                        = 'hidn',
	//	kAudioDevicePropertyPreferredChannelsForStereo      = 'dch2',
	//	kAudioDevicePropertyPreferredChannelLayout          = 'srnd'

	//	kAudioDevicePropertyPlugIn                          = 'plug',
	//	kAudioDevicePropertyDeviceHasChanged                = 'diff',
	//	kAudioDevicePropertyDeviceIsRunningSomewhere        = 'gone',
	//	kAudioDeviceProcessorOverload                       = 'over',
	//	kAudioDevicePropertyIOStoppedAbnormally             = 'stpd',
	//	kAudioDevicePropertyHogMode                         = 'oink',

	UInt32 BufferFrameSize() const
	{
		return GetArithmeticProperty<UInt32>(CAPropertyAddress(kAudioDevicePropertyBufferFrameSize));
	}

	//	kAudioDevicePropertyBufferFrameSizeRange            = 'fsz#',
	//	kAudioDevicePropertyUsesVariableBufferFrameSizes    = 'vfsz',
	//	kAudioDevicePropertyIOCycleUsage                    = 'ncyc',
	//	kAudioDevicePropertyStreamConfiguration             = 'slay',
	//	kAudioDevicePropertyIOProcStreamUsage               = 'suse',
	//	kAudioDevicePropertyActualSampleRate                = 'asrt',
	//	kAudioDevicePropertyClockDevice                     = 'apcd',
	//	kAudioDevicePropertyIOThreadOSWorkgroup				= 'oswg'

};

} /* namespace audio_hardware */
