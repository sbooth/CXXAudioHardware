import Testing
@testable import CXXAudioHardware

@Suite struct CXXAudioHardwareTests {
	@Test func audioObject() async {
		let obj = CXXAudioHardware.CAAudioObject()
		#expect(obj.ObjectID() == kAudioObjectUnknown)
	}
}
