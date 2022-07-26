## libmatoya Client Example

This example should be easily built via `make` or `nmake` (on Windows). Tested with `Visual Studio Community Edition 2017`.

This example is built with [libmatoya](https://github.com/matoya/libmatoya) for cross platform window management, game controllers, mouse/keyboard input, and 2D quad rendering.
  
The Parsec SDK is loaded via DSO. See [parsec-dso.h](/sdk/parsec-dso.h).

## Running
  
```client.exe sessionID peerID```
  
See [api/public](/api/public) for acquiring a `sessionID` and `peerID`.
