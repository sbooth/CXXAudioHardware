// swift-tools-version: 5.9
//
// SPDX-FileCopyrightText: 2025 Stephen F. Booth <contact@sbooth.dev>
// SPDX-License-Identifier: MIT
//
// Part of https://github.com/sbooth/CXXAudioHardware
//

import PackageDescription

let package = Package(
	name: "CXXAudioHardware",
	platforms: [
		.macOS(.v11),
	],
	products: [
		// Products define the executables and libraries a package produces, making them visible to other packages.
		.library(
			name: "CXXAudioHardware",
			targets: [
				"CXXAudioHardware",
			]
		),
	],
	dependencies: [
		.package(url: "https://github.com/sbooth/CXXCoreAudio", from: "0.1.0")
	],
	targets: [
		// Targets are the basic building blocks of a package, defining a module or a test suite.
		// Targets can depend on other targets in this package and products from dependencies.
		.target(
			name: "CXXAudioHardware",
			dependencies: [
				"CXXCoreAudio",
			],
			cSettings: [
				.headerSearchPath("include/CXXAudioHardware"),
			],
			linkerSettings: [
				.linkedFramework("CoreAudio"),
			]
		),
		.testTarget(
			name: "CXXAudioHardwareTests",
			dependencies: [
				"CXXAudioHardware",
			],
			swiftSettings: [
				.interoperabilityMode(.Cxx),
			]
		),
	],
	cxxLanguageStandard: .cxx17
)
