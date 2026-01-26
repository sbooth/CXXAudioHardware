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
        .library(
            name: "CXXAudioHardware",
            targets: [
                "CXXAudioHardware",
            ]
        ),
    ],
    dependencies: [
        .package(url: "https://github.com/sbooth/CXXCoreAudio", from: "0.5.1")
    ],
    targets: [
        .target(
            name: "CXXAudioHardware",
            dependencies: [
                "CXXCoreAudio",
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
