## SDL Client Example

This example should be easily built via `make` or `nmake` (on Windows). Tested with `Visual Studio Community Edition 2017`.
  
The Parsec SDK is loaded via DSO. See [parsec-dso.h](/sdk/parsec-dso.h).

## Running
  
```client.exe sessionID peerID```
  
See [api/public](/api/public) for acquiring a `sessionID` and `peerID`.
