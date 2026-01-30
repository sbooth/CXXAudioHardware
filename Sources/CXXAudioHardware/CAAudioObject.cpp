//
// SPDX-FileCopyrightText: 2021 Stephen F. Booth <contact@sbooth.dev>
// SPDX-License-Identifier: MIT
//
// Part of https://github.com/sbooth/CXXAudioHardware
//

#include "audio_hardware/CAAudioObject.hpp"

#include "AudioHardwareErrors.hpp"

bool audio_hardware::CAAudioObject::IsPropertySettable(const AudioObjectPropertyAddress& inAddress) const
{
	Boolean settable = false;
	const auto result = AudioObjectIsPropertySettable(objectID_, &inAddress, &settable);
	ThrowIfAudioObjectError(result, "AudioObjectIsPropertySettable");
	return settable != 0;
}

UInt32 audio_hardware::CAAudioObject::GetPropertyDataSize(const AudioObjectPropertyAddress& inAddress, UInt32 inQualifierDataSize, const void *inQualifierData) const
{
	UInt32 size = 0;
	const auto result = AudioObjectGetPropertyDataSize(objectID_, &inAddress, inQualifierDataSize, inQualifierData, &size);
	ThrowIfAudioObjectError(result, "AudioObjectGetPropertyDataSize");
	return size;
}

void audio_hardware::CAAudioObject::GetPropertyData(const AudioObjectPropertyAddress& inAddress, UInt32 inQualifierDataSize, const void *inQualifierData, UInt32& ioDataSize, void *outData) const
{
	const auto result = AudioObjectGetPropertyData(objectID_, &inAddress, inQualifierDataSize, inQualifierData, &ioDataSize, outData);
	ThrowIfAudioObjectError(result, "AudioObjectGetPropertyData");
}

void audio_hardware::CAAudioObject::SetPropertyData(const AudioObjectPropertyAddress& inAddress, UInt32 inQualifierDataSize, const void *inQualifierData, UInt32 inDataSize, const void *inData)
{
	const auto result = AudioObjectSetPropertyData(objectID_, &inAddress, inQualifierDataSize, inQualifierData, inDataSize, inData);
	ThrowIfAudioObjectError(result, "AudioObjectSetPropertyData");
}

void audio_hardware::CAAudioObject::AddPropertyListener(const AudioObjectPropertyAddress& inAddress, AudioObjectPropertyListenerProc inListenerProc, void *inClientData)
{
	const auto result = AudioObjectAddPropertyListener(objectID_, &inAddress, inListenerProc, inClientData);
	ThrowIfAudioObjectError(result, "AudioObjectAddPropertyListener");
}

void audio_hardware::CAAudioObject::RemovePropertyListener(const AudioObjectPropertyAddress& inAddress, AudioObjectPropertyListenerProc inListenerProc, void *inClientData)
{
	const auto result = AudioObjectRemovePropertyListener(objectID_, &inAddress, inListenerProc, inClientData);
	ThrowIfAudioObjectError(result, "AudioObjectRemovePropertyListener");
}

void audio_hardware::CAAudioObject::AddPropertyListenerBlock(const AudioObjectPropertyAddress& inAddress, dispatch_queue_t inDispatchQueue, AudioObjectPropertyListenerBlock inListenerBlock)
{
	const auto result = AudioObjectAddPropertyListenerBlock(objectID_, &inAddress, inDispatchQueue, inListenerBlock);
	ThrowIfAudioObjectError(result, "AudioObjectAddPropertyListenerBlock");
}

void audio_hardware::CAAudioObject::RemovePropertyListenerBlock(const AudioObjectPropertyAddress& inAddress, dispatch_queue_t inDispatchQueue, AudioObjectPropertyListenerBlock inListenerBlock)
{
	const auto result = AudioObjectRemovePropertyListenerBlock(objectID_, &inAddress, inDispatchQueue, inListenerBlock);
	ThrowIfAudioObjectError(result, "AudioObjectRemovePropertyListenerBlock");
}
