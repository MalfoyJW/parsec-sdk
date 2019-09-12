## Overview

The Parsec SDK allows your application to make interactive, low-latency peer-to-peer connections for the purpose of game streaming. The SDK handles the low level internals of peer-to-peer connectivity, networking, and hardware accelerated video/audio processing. It is lightweight, consisting of a [single header file](/sdk/parsec.h) and a shared object < 5MB.

#### Hosting
The `ParsecHost` portion of the SDK allows a host to accept incoming client connections (guests). There are two modes of operation: **game mode** and **desktop mode**.

Game mode allows your game to add multiplayer functionality to an otherwise local only game. This is achieved via a tight integration into your game's render loop. Game mode requires that the application call `ParsecHostSubmitFrame` and `ParsecHostSubmitAudio`. Input is polled via `ParsecHostPollInput`, exposing input events much like they would appear locally. In game mode, Parsec can only interact with your game and has no access to the OS or any other application.

Additionally, game mode can be used to make any game entirely headless from the host's point of view. The game window, rendering swap chain, and audio playback can be removed, leaving the game to accept input from and invisibly output data to Parsec connected guests.

Desktop mode shares the host's entire desktop (or any fullscreen application) and adds additional permissions/approval to the connection process.

#### Client
The `ParsecClient` portion of the SDK provides everything necessary to make a connection to a host, send gamepad/mouse/keyboard input, and receive video/audio output from the host. `ParsecClientGLRender` allows the client application to efficiently render the incoming frames.

## Examples

#### Game Mode Hosting
[cddNES](https://github.com/chrisd1100/cddNES) is a NES emulator written in C and serves as the canonical example of game mode hosting. It demonstrates polling Parsec guest input, submitting rendered frames via D3D11 and OpenGL, submitting audio, and generally handling guest state and guest events.
  
#### Game Mode Hosting with Unity
The Parsec SDK provides the [ParsecUnity](/sdk/ParsecUnity) module for easy integration in Unity games. See [examples/unity](/examples/unity) for details.

#### Windows, macOS, Linux Clients
The [client](/examples/client) example demonstrates the most complete implementation of the client SDK. It uses the cross platform SDL2 library to handle window creation, rendering, audio playback, and input handling. Windows, macOS, and x86-64 Linux are supported.

#### iOS and Android Clients
The [ios](/examples/ios) and [android](/examples/android) examples demonstrate audio playback, rendering, and basic input capabilities of the client SDK. The Android example provides a simple JNI bindings package to expose a subset of the C API in Java.

#### Desktop Mode Hosting
The [host](/examples/host) example is a succinct implementation of desktop hosting functionality. Desktop hosting is currently only available on Windows.

#### Web Client
The Web Client SDK provides a fully wrapped Parsec client interface only requiring a `<video>` element for initialization. The performance is limited compared to the native SDK clients. See [examples/web](/examples/web) and [sdk/web](/sdk/web) for details.

## C Documentation

Documentation is procedurally generated from the [parsec.h](/sdk/parsec.h) header file.

https://parsecgaming.com/sdk/docs

The Parsec SDK is currently in beta and will begin properly versioning `PARSEC_VER_MAJOR` and `PARSEC_VER_MINOR` on October 1, 2019. For the time being, the version will stay at `1.0` while small ABI/API tweaks may be published.

## Obtaining a `sessionID` and `peerID`

The SDK requires a `sessionID` and `peerID` obtained through the Parsec API to identify users and make secure connections. See the [Public API](/api/public) for details.

For enterprise customers, refer to the example in [api/enterprise](/api/enterprise) on how to wrap the Enterprise API. 

## Using Runtime Linking (DSO)

If `PARSEC_DSO` is defined before including [parsec.h](/sdk/parsec.h), the header will export a `struct` containing function pointers for use with runtime linking. There is a convenience header which makes DSO easy to use called [parsec-dso.h](/sdk/parsec-dso.h) in the [sdk](/sdk) directory. The [client](/examples/client) and [host](/examples/host) examples use DSO. There are a few differences when using the [parsec-dso.h](/sdk/parsec-dso.h) header instead of [parsec.h](/sdk/parsec.h):

- The `Parsec *` context is now `ParsecDSO *`.
- All global functions that do not normally take a `Parsec *` context now need to take `ParsecDSO *` as their first argument, such as `ParsecSetLogCallback`.
- The signature for `ParsecInit` changes to to take an additional `char *` argument specifying the name of the shared object.
- `ParsecInit` may return `SO_ERR_OPEN` or `SO_ERR_SYMBOL` if runtime linking was unsuccessful.

## Bindings

Bindings are maintained by third party developers (thank you!). If you're interested in another language and would like to create a binding, please submit an issue or contact us via [sdk@parsecgaming.com](mailto:sdk@parsecgaming.com).

| Language | Maintainer | Repo |
|----------|------------|------|
| Java | [Richard Smith](https://github.com/electronstudio) | [electronstudio/parsec-java](https://github.com/electronstudio/parsec-java)

