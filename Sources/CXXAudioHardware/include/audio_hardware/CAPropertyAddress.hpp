//
// SPDX-FileCopyrightText: 2021 Stephen F. Booth <contact@sbooth.dev>
// SPDX-License-Identifier: MIT
//
// Part of https://github.com/sbooth/CXXAudioHardware
//

#pragma once

#import <cstring>

#import <CoreAudio/AudioHardware.h>

namespace audio_hardware {

/// A class extending the functionality of an AudioObjectPropertyAddress structure.
class CAPropertyAddress : public AudioObjectPropertyAddress {
public:

	/// Creates an empty audio object property address.
	CAPropertyAddress() noexcept
	: AudioObjectPropertyAddress{0}
	{}

	/// Copy constructor.
	CAPropertyAddress(const CAPropertyAddress& other) noexcept = default;

	/// Assignment operator.
	CAPropertyAddress& operator=(const CAPropertyAddress& other) noexcept = default;

	/// Move constructor.
	CAPropertyAddress(CAPropertyAddress&& other) noexcept = default;

	/// Move assignment operator.
	CAPropertyAddress& operator=(CAPropertyAddress&& other) noexcept = default;

	/// Destructor.
	~CAPropertyAddress() = default;


	/// Creates an audio object property address.
	/// @param selector The property selector.
	/// @param scope The property element.
	/// @param element The property scope.
	CAPropertyAddress(AudioObjectPropertySelector selector, AudioObjectPropertyScope scope = kAudioObjectPropertyScopeGlobal, AudioObjectPropertyElement element = kAudioObjectPropertyElementMain) noexcept
	: AudioObjectPropertyAddress{selector, scope, element}
	{}

	// Native overloads

	/// Creates an audio object property address from the specified AudioObjectPropertyAddress structure.
	CAPropertyAddress(const AudioObjectPropertyAddress& other) noexcept
	: AudioObjectPropertyAddress{other}
	{}

	/// Assignment operator.
	CAPropertyAddress& operator=(const AudioObjectPropertyAddress& other) noexcept
	{
		AudioObjectPropertyAddress::operator=(other);
		return *this;
	}

	// MARK: Comparison

	/// Returns true if this audio object property address is equal to another.
	bool operator==(const AudioObjectPropertyAddress& other) const noexcept
	{
		return !std::memcmp(this, &other, sizeof(AudioObjectPropertyAddress));
	}

	/// Returns true if this audio object property address is not equal to another.
	bool operator!=(const AudioObjectPropertyAddress& other) const noexcept
	{
		return !operator==(other);
	}

	/// Returns true if this audio object property address is congruent to another.
	/// @note Congruence relations consider wildcards.
	bool Congruent(const AudioObjectPropertyAddress& other) const noexcept
	{
		return (mSelector == other.mSelector || mSelector == kAudioObjectPropertySelectorWildcard || other.mSelector == kAudioObjectPropertySelectorWildcard)
		&& (mScope == other.mScope || mScope == kAudioObjectPropertyScopeWildcard || other.mScope == kAudioObjectPropertyScopeWildcard)
		&& (mElement == other.mElement || mElement == kAudioObjectPropertyElementWildcard || other.mElement == kAudioObjectPropertyElementWildcard);
	}
};

} /* namespace audio_hardware */
