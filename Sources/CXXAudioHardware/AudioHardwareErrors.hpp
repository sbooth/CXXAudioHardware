//
// Copyright © 2024-2025 Stephen F. Booth
// Part of https://github.com/sbooth/CXXAudioHardware
// MIT license
//

#pragma once

#import <exception>
#import <system_error>

#import <CoreAudio/CoreAudio.h>

namespace CXXAudioHardware {
namespace detail {

/// A std::error_category for return values from the AudioObject API.
class AudioObjectErrorCategory : public std::error_category {
public:
	virtual const char * name() const noexcept override final { return "AudioObject"; }
	virtual std::string message(int condition) const override final
	{
		switch(static_cast<OSStatus>(condition)) {
				// CoreAudioBaseTypes.h
			case kAudio_NoError: 							return "The function call completed successfully";
			case kAudio_UnimplementedError: 				return "Unimplemented core routine";
			case kAudio_FileNotFoundError: 					return "File not found";
			case kAudio_FilePermissionError: 				return "File cannot be opened due to either file, directory, or sandbox permissions";
			case kAudio_TooManyFilesOpenError: 				return "File cannot be opened because too many files are already open";
			case kAudio_BadFilePathError: 					return "File cannot be opened because the specified path is malformed";
			case kAudio_ParamError: 						return "Error in user parameter list";
			case kAudio_MemFullError: 						return "Not enough room in heap zone";
				// AudioHardwareBase.h
				//			case kAudioHardwareNoError:						return "The function call completed successfully";
			case kAudioHardwareNotRunningError:				return "The function call requires that the hardware be running but it isn't";
			case kAudioHardwareUnspecifiedError:			return "The function call failed while doing something that doesn't provide any error messages";
			case kAudioHardwareUnknownPropertyError:		return "The AudioObject doesn't know about the property at the given address";
			case kAudioHardwareBadPropertySizeError:		return "An improperly sized buffer was provided when accessing the data of a property";
			case kAudioHardwareIllegalOperationError:		return "The requested operation couldn't be completed";
			case kAudioHardwareBadObjectError:				return "The AudioObjectID passed to the function doesn't map to a valid AudioObject";
			case kAudioHardwareBadDeviceError:				return "The AudioObjectID passed to the function doesn't map to a valid AudioDevice";
			case kAudioHardwareBadStreamError:				return "The AudioObjectID passed to the function doesn't map to a valid AudioStream";
			case kAudioHardwareUnsupportedOperationError: 	 return "The AudioObject doesn't support the requested operation";
			case kAudioDeviceUnsupportedFormatError:		return "The AudioStream doesn't support the requested format";
			case kAudioDevicePermissionsError:				return "The requested operation can't be completed because the process doesn't have permission";
			default:										return "Unknown AudioObject error";
		}
	}
};

/// Global instance of AudioObject error category.
const AudioObjectErrorCategory audioObjectErrorCategory_;

} /* namespace detail */

// MARK: -

/// Throws a std::system_error in the AudioObjectErrorCategory if result != kAudio_NoError.
/// @param result An OSStatus result code.
/// @param operation An optional string describing the operation that produced result.
/// @throw std::system_error in the AudioObjectErrorCategory.
inline void ThrowIfAudioObjectError(OSStatus result, const char * const operation = nullptr)
{
	if(__builtin_expect(result != kAudio_NoError, false))
		throw std::system_error(result, detail::audioObjectErrorCategory_, operation);
}

} /* namespace CXXAudioHardware */
