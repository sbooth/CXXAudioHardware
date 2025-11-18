//
// Copyright © 2021-2025 Stephen F. Booth
// Part of https://github.com/sbooth/CXXAudioHardware
// MIT license
//

#pragma once

#import <type_traits>
#import <vector>

#import <CoreAudio/CoreAudio.h>
#import <CoreFoundation/CFString.h>

#import <CXXAudioHardware/CAPropertyAddress.hpp>

namespace CXXAudioHardware {

enum class CAAudioObjectDirectionalScope {
	input,
	output,
};

class CAAudioObject {
public:

	// MARK: Creation and Destruction

	/// Creates an unknown audio object.
	CAAudioObject() noexcept = default;

	/// Copy constructor.
	CAAudioObject(const CAAudioObject& other) noexcept = default;

	/// Assignment operator.
	CAAudioObject& operator=(const CAAudioObject& other) noexcept = default;

	// Move constructor.
	CAAudioObject(CAAudioObject&& other) noexcept = default;

	/// Move assignment operator.
	CAAudioObject& operator=(CAAudioObject&& other) noexcept = default;

	/// Destructor.
	virtual ~CAAudioObject() = default;

	/// Creates an audio object with the specified object ID.
	explicit CAAudioObject(AudioObjectID objectID) noexcept
	: objectID_{objectID}
	{}

	// MARK: Comparison

	/// Returns true if this object's ID is not kAudioObjectUnknown.
	explicit operator bool() const noexcept
	{
		return objectID_ != kAudioObjectUnknown;
	}

	/// Returns true if other is equal to this
	bool operator==(AudioObjectID other) const noexcept
	{
		return objectID_ == other;
	}

	/// Returns true if other is not equal to this
	bool operator!=(AudioObjectID other) const noexcept
	{
		return !operator==(other);
	}

	operator AudioObjectID() const noexcept
	{
		return objectID_;
	}

	AudioObjectID ObjectID() const noexcept
	{
		return objectID_;
	}

	// MARK: Property Operations

	bool HasProperty(const AudioObjectPropertyAddress& inAddress) const noexcept
	{
		return AudioObjectHasProperty(objectID_, &inAddress);
	}

	bool IsPropertySettable(const AudioObjectPropertyAddress& inAddress) const;

	UInt32 GetPropertyDataSize(const AudioObjectPropertyAddress& inAddress, UInt32 inQualifierDataSize = 0, const void * _Nullable inQualifierData = nullptr) const;

	void GetPropertyData(const AudioObjectPropertyAddress& inAddress, UInt32 inQualifierDataSize, const void * _Nullable inQualifierData, UInt32& ioDataSize, void * _Nonnull outData) const;

	void SetPropertyData(const AudioObjectPropertyAddress& inAddress, UInt32 inQualifierDataSize, const void * _Nullable inQualifierData, UInt32 inDataSize, const void * _Nonnull inData);


	template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
	T GetArithmeticProperty(const AudioObjectPropertyAddress& inAddress, UInt32 inQualifierDataSize = 0, const void * _Nullable inQualifierData = nullptr) const
	{
		T value;
		UInt32 size{sizeof(T)};
		GetPropertyData(inAddress, inQualifierDataSize, inQualifierData, size, &value);
		return value;
	}

	template <typename T, typename = std::enable_if_t<std::is_trivial_v<T>>>
	T GetStructProperty(const AudioObjectPropertyAddress& inAddress, UInt32 inQualifierDataSize = 0, const void * _Nullable inQualifierData = nullptr) const
	{
		T value;
		UInt32 size{sizeof(T)};
		GetPropertyData(inAddress, inQualifierDataSize, inQualifierData, size, &value);
		return value;
	}

	template <typename T, typename = std::enable_if_t<std::is_trivial_v<T>>>
	std::vector<T> GetArrayProperty(const AudioObjectPropertyAddress& inAddress, UInt32 inQualifierDataSize = 0, const void * _Nullable inQualifierData = nullptr) const
	{
		auto size{GetPropertyDataSize(inAddress, inQualifierDataSize, inQualifierData)};
		const auto count{size / sizeof(T)};
		auto vec{std::vector<T>(count)};
		GetPropertyData(inAddress, inQualifierDataSize, inQualifierData, size, vec.data());
		return vec;
	}

	template <typename T, typename = std::enable_if_t</*std::is_class_v<T> &&*/ std::is_pointer_v<T>>>
	T CopyCFTypeProperty(const AudioObjectPropertyAddress& inAddress, UInt32 inQualifierDataSize = 0, const void * _Nullable inQualifierData = nullptr) const CF_RETURNS_RETAINED
	{
		T value;
		UInt32 size{sizeof(T)};
		GetPropertyData(inAddress, inQualifierDataSize, inQualifierData, size, &value);
		return value;
	}

	void AddPropertyListener(const AudioObjectPropertyAddress& inAddress, AudioObjectPropertyListenerProc _Nonnull inListenerProc, void * _Nullable inClientData);

	void RemovePropertyListener(const AudioObjectPropertyAddress& inAddress, AudioObjectPropertyListenerProc _Nonnull inListenerProc, void * _Nullable inClientData);

	void AddPropertyListenerBlock(const AudioObjectPropertyAddress& inAddress, dispatch_queue_t _Nonnull inDispatchQueue, AudioObjectPropertyListenerBlock _Nonnull inListenerBlock);

	void RemovePropertyListenerBlock(const AudioObjectPropertyAddress& inAddress, dispatch_queue_t _Nonnull inDispatchQueue, AudioObjectPropertyListenerBlock _Nonnull inListenerBlock);

	// MARK: AudioObject Properties

	AudioClassID BaseClass() const
	{
		return GetArithmeticProperty<AudioClassID>(CAPropertyAddress(kAudioObjectPropertyBaseClass));
	}

	AudioClassID Class() const
	{
		return GetArithmeticProperty<AudioClassID>(CAPropertyAddress(kAudioObjectPropertyClass));
	}

	AudioObjectID OwnerID() const
	{
		return GetArithmeticProperty<AudioObjectID>(CAPropertyAddress(kAudioObjectPropertyOwner));
	}

	CAAudioObject Owner() const
	{
		return CAAudioObject(OwnerID());
	}

	CFStringRef CopyName() const CF_RETURNS_RETAINED
	{
		return CopyCFTypeProperty<CFStringRef>(CAPropertyAddress(kAudioObjectPropertyName));
	}

	CFStringRef CopyModelName() const CF_RETURNS_RETAINED
	{
		return CopyCFTypeProperty<CFStringRef>(CAPropertyAddress(kAudioObjectPropertyModelName));
	}

	CFStringRef CopyManufacturer() const CF_RETURNS_RETAINED
	{
		return CopyCFTypeProperty<CFStringRef>(CAPropertyAddress(kAudioObjectPropertyManufacturer));
	}

	CFStringRef CopyElementName(AudioObjectPropertyScope inScope, AudioObjectPropertyElement inElement) const CF_RETURNS_RETAINED
	{
		return CopyCFTypeProperty<CFStringRef>(CAPropertyAddress(kAudioObjectPropertyElementName, inScope, inElement));
	}

	CFStringRef CopyElementCategoryName(AudioObjectPropertyScope inScope, AudioObjectPropertyElement inElement) const CF_RETURNS_RETAINED
	{
		return CopyCFTypeProperty<CFStringRef>(CAPropertyAddress(kAudioObjectPropertyElementCategoryName, inScope, inElement));
	}

	CFStringRef CopyElementNumberName(AudioObjectPropertyScope inScope, AudioObjectPropertyElement inElement) const CF_RETURNS_RETAINED
	{
		return CopyCFTypeProperty<CFStringRef>(CAPropertyAddress(kAudioObjectPropertyElementNumberName, inScope, inElement));
	}

	std::vector<AudioObjectID> OwnedObjectIDs() const
	{
		return GetArrayProperty<AudioObjectID>(CAPropertyAddress(kAudioObjectPropertyOwnedObjects));
	}

	std::vector<CAAudioObject> OwnedObjects() const
	{
		auto vec{OwnedObjectIDs()};
		std::vector<CAAudioObject> result{vec.size()};
		std::transform(vec.cbegin(), vec.cend(), result.begin(), [](AudioObjectID objectID) { return CAAudioObject(objectID); });
		return result;
	}

	//	kAudioObjectPropertyIdentify            = 'iden',

	CFStringRef CopySerialNumber() const CF_RETURNS_RETAINED
	{
		return CopyCFTypeProperty<CFStringRef>(CAPropertyAddress(kAudioObjectPropertySerialNumber));
	}

	CFStringRef CopyFirmwareVersion() const CF_RETURNS_RETAINED
	{
		return CopyCFTypeProperty<CFStringRef>(CAPropertyAddress(kAudioObjectPropertyFirmwareVersion));
	}

protected:
	// The underlying audio object ID.
	AudioObjectID objectID_{kAudioObjectUnknown};
};

} /* namespace CXXAudioHardware */
