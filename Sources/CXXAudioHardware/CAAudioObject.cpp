//
// Copyright © 2021-2025 Stephen F. Booth
// Part of https://github.com/sbooth/CXXAudioHardware
// MIT license
//

#import "CAAudioObject.hpp"
#import "AudioHardwareErrors.hpp"

bool CXXAudioHardware::CAAudioObject::IsPropertySettable(const AudioObjectPropertyAddress& inAddress) const
{
	Boolean settable = false;
	auto result = AudioObjectIsPropertySettable(objectID_, &inAddress, &settable);
	ThrowIfAudioObjectError(result, "AudioObjectIsPropertySettable");
	return settable != 0;
}

UInt32 CXXAudioHardware::CAAudioObject::GetPropertyDataSize(const AudioObjectPropertyAddress& inAddress, UInt32 inQualifierDataSize, const void *inQualifierData) const
{
	UInt32 size = 0;
	auto result = AudioObjectGetPropertyDataSize(objectID_, &inAddress, inQualifierDataSize, inQualifierData, &size);
	ThrowIfAudioObjectError(result, "AudioObjectGetPropertyDataSize");
	return size;
}

void CXXAudioHardware::CAAudioObject::GetPropertyData(const AudioObjectPropertyAddress& inAddress, UInt32 inQualifierDataSize, const void *inQualifierData, UInt32& ioDataSize, void *outData) const
{
	auto result = AudioObjectGetPropertyData(objectID_, &inAddress, inQualifierDataSize, inQualifierData, &ioDataSize, outData);
	ThrowIfAudioObjectError(result, "AudioObjectGetPropertyData");
}

void CXXAudioHardware::CAAudioObject::SetPropertyData(const AudioObjectPropertyAddress& inAddress, UInt32 inQualifierDataSize, const void *inQualifierData, UInt32 inDataSize, const void *inData)
{
	auto result = AudioObjectSetPropertyData(objectID_, &inAddress, inQualifierDataSize, inQualifierData, inDataSize, inData);
	ThrowIfAudioObjectError(result, "AudioObjectSetPropertyData");
}

void CXXAudioHardware::CAAudioObject::AddPropertyListener(const AudioObjectPropertyAddress& inAddress, AudioObjectPropertyListenerProc inListenerProc, void *inClientData)
{
	auto result = AudioObjectAddPropertyListener(objectID_, &inAddress, inListenerProc, inClientData);
	ThrowIfAudioObjectError(result, "AudioObjectAddPropertyListener");
}

void CXXAudioHardware::CAAudioObject::RemovePropertyListener(const AudioObjectPropertyAddress& inAddress, AudioObjectPropertyListenerProc inListenerProc, void *inClientData)
{
	auto result = AudioObjectRemovePropertyListener(objectID_, &inAddress, inListenerProc, inClientData);
	ThrowIfAudioObjectError(result, "AudioObjectRemovePropertyListener");
}

void CXXAudioHardware::CAAudioObject::AddPropertyListenerBlock(const AudioObjectPropertyAddress& inAddress, dispatch_queue_t inDispatchQueue, AudioObjectPropertyListenerBlock inListenerBlock)
{
	auto result = AudioObjectAddPropertyListenerBlock(objectID_, &inAddress, inDispatchQueue, inListenerBlock);
	ThrowIfAudioObjectError(result, "AudioObjectAddPropertyListenerBlock");
}

void CXXAudioHardware::CAAudioObject::RemovePropertyListenerBlock(const AudioObjectPropertyAddress& inAddress, dispatch_queue_t inDispatchQueue, AudioObjectPropertyListenerBlock inListenerBlock)
{
	auto result = AudioObjectRemovePropertyListenerBlock(objectID_, &inAddress, inDispatchQueue, inListenerBlock);
	ThrowIfAudioObjectError(result, "AudioObjectRemovePropertyListenerBlock");
}
