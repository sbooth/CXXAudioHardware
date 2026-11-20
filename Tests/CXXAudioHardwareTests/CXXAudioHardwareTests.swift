//
// SPDX-FileCopyrightText: 2025 Stephen F. Booth <contact@sbooth.dev>
// SPDX-License-Identifier: MIT
//
// Part of https://github.com/sbooth/CXXAudioHardware
//

import Testing
@testable import CXXAudioHardware

@Suite struct CXXAudioHardwareTests {
    @Test func audioObject() async {
        let obj = audio_hardware.CAAudioObject()
        #expect(obj.ObjectID() == kAudioObjectUnknown)
    }
}
