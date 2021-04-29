## Overview

The Parsec SDK allows your application to make interactive, low-latency peer-to-peer connections for the purpose of game streaming. The SDK handles the low level internals of peer-to-peer connectivity, networking, and hardware accelerated video/audio processing. It is lightweight, consisting of a [single header file](/sdk/parsec.h) and a shared object < 5MB.

#### Hosting
The `ParsecHost` portion of the SDK allows a host to accept incoming client connections (guests). There are two modes of operation: **game mode** and **desktop mode**.

Game mode allows your game to add multiplayer functionality to an otherwise local only game. This is achieved via a tight integration into your game's render loop. Game mode requires that the application call one of the `ParsecHostSubmitFrame` functions (supporting OpenGL, D3D9, and D3D11) and `ParsecHostSubmitAudio`. Input is polled via `ParsecHostPollInput`, exposing input events much like they would appear locally. In game mode, Parsec can only interact with your game and has no access to the OS or any other application.

Additionally, game mode can be used to make any game entirely headless from the host's point of view. The game window, rendering swap chain, and audio playback can be removed, leaving the game to accept input from and invisibly output data to Parsec connected guests.

Desktop mode shares the host's entire desktop (or any fullscreen application) and adds additional permissions/approval to the connection process.

#### Client
The `ParsecClient` portion of the SDK provides everything necessary to make a connection to a host, send gamepad/mouse/keyboard input, and receive video/audio output from the host. The `ParsecClientRender` family of functions allow the client application to efficiently render the incoming frames with OpenGL, D3D9, D3D11, or Metal.

## Examples
  
#### Game Mode Hosting with Unity
The Parsec SDK provides the [ParsecUnity](/sdk/ParsecUnity) module for easy integration in Unity games. See [examples/unity](/examples/unity) for details.

#### Windows, macOS, Linux Clients
The [client](/examples/client) example demonstrates the most complete implementation of the client SDK. It uses the cross platform [libmatoya](https://github.com/matoya/libmatoya) library to handle window creation, rendering, audio playback, and input handling. Windows, macOS, and x86-64 Linux are supported.

#### iOS and Android Clients
The [ios](/examples/ios) and [android](/examples/android) examples demonstrate audio playback, rendering, and basic input capabilities of the client SDK. The Android example provides a simple JNI bindings package to expose a subset of the C API in Java.

#### Desktop Mode Hosting
The [host](/examples/host) example is a succinct implementation of desktop hosting functionality. Desktop hosting is currently only available on Windows.

#### Web Client
The Parsec Web SDK provides a fully wrapped Parsec client interface only requiring a `<video>` and `<audio>` element for initialization. The performance is limited compared to the native SDK clients. See [examples/web](/examples/web) and [sdk/web](/sdk/web) for details.

## Documentation

Documentation is procedurally generated from the [parsec.h](/sdk/parsec.h) header file.

https://parsecgaming.com/docs/sdk

## Obtaining a `sessionID` and `peerID`

The SDK requires a `sessionID` and `peerID` obtained through the Parsec API to identify users and make secure connections. There are three methods of obtaining a `sessionID`:  

- For quick start, testing, and personal use only, see [api/personal](/api/personal). The `/v1/auth` API call may NOT be used in any application distributed to the public or in any enterprise use case.
- For third party distribution intended for other Parsec users, see [api/third-party](/api/third-party) for OAuth style access delegation.
- For enterprise customers, see [api/enterprise](/api/enterprise).

## Sharing Private Hosts

The Parsec SDK supports a `secret` property on both the `ParsecHostConfig` and `ParsecClientConfig` structs. If the host sets a secret during `ParsecHostStart`, the client must also provide the same secret during `ParsecClientConnect` in order to make a connection. Your application may choose how to privately share both this `secret` and the host's `peerID` to facilitate features such as link sharing or private games.  

For simple link sharing testing, you may use the URL template https://parsec.gg/g/{peerID}/{secret}/, however this template is used by the Parsec consumer application and may change without notice. It is highly recommended that your application uses a custom method for sharing the `peerID` and `secret`.

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

## Community

For questions, suggestions, concerns, and support, visit the [Parsec SDK Server on Discord](https://discord.gg/xQaTQt2).


