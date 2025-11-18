//
// Copyright © 2021-2025 Stephen F. Booth
// Part of https://github.com/sbooth/CXXAudioHardware
// MIT license
//

#pragma once

#import <CXXCoreAudio/CAStreamDescription.hpp>
#import <CXXAudioHardware/CAAudioObject.hpp>

namespace CXXAudioHardware {

class CAAudioStream : public CAAudioObject {
public:
	using CAAudioObject::CAAudioObject;

	bool IsActive() const
	{
		return GetArithmeticProperty<UInt32>(CAPropertyAddress(kAudioStreamPropertyIsActive)) != 0;
	}

	UInt32 Direction() const
	{
		return GetArithmeticProperty<UInt32>(CAPropertyAddress(kAudioStreamPropertyDirection));
	}

	UInt32 TerminalType() const
	{
		return GetArithmeticProperty<UInt32>(CAPropertyAddress(kAudioStreamPropertyTerminalType));
	}

	UInt32 StartingChannel() const
	{
		return GetArithmeticProperty<UInt32>(CAPropertyAddress(kAudioStreamPropertyStartingChannel));
	}

	UInt32 Latency() const
	{
		return GetArithmeticProperty<UInt32>(CAPropertyAddress(kAudioStreamPropertyLatency));
	}

	CXXCoreAudio::CAStreamDescription VirtualFormat() const
	{
		return GetStructProperty<AudioStreamBasicDescription>(CAPropertyAddress(kAudioStreamPropertyVirtualFormat));
	}

	std::vector<AudioStreamRangedDescription> AvailableVirtualFormats() const
	{
		return GetArrayProperty<AudioStreamRangedDescription>(CAPropertyAddress(kAudioStreamPropertyAvailableVirtualFormats));
	}

	CXXCoreAudio::CAStreamDescription PhysicalFormat() const
	{
		return GetStructProperty<AudioStreamBasicDescription>(CAPropertyAddress(kAudioStreamPropertyPhysicalFormat));
	}

	std::vector<AudioStreamRangedDescription> AvailablePhysicalFormats() const
	{
		return GetArrayProperty<AudioStreamRangedDescription>(CAPropertyAddress(kAudioStreamPropertyAvailablePhysicalFormats));
	}
};

} /* namespace CXXAudioHardware */
