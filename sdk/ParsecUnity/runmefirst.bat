@echo off
copy /b /v /y ParsecUnity46.dll ..\..\examples\unity\Assets\ParsecUnity\
copy /b /v /y ParsecUnity46.dll ..\..\examples\unity-rewired\Assets\ParsecUnity\

copy /b /v /y ..\windows\Parsec.dll .\
copy /b /v /y ..\windows\Parsec.dll ..\..\examples\unity\Assets\ParsecUnity\
copy /b /v /y ..\windows\Parsec.dll ..\..\examples\unity-rewired\Assets\ParsecUnity\

copy /b /v /y ..\windows\Parsec32.dll .\
copy /b /v /y ..\windows\Parsec32.dll ..\..\examples\unity\Assets\ParsecUnity\
copy /b /v /y ..\windows\Parsec32.dll ..\..\examples\unity-rewired\Assets\ParsecUnity\

copy /b /v /y ..\macos\libparsec.dylib .\parsec.bundle
copy /b /v /y ..\macos\libparsec.dylib ..\..\examples\unity\Assets\ParsecUnity\parsec.bundle
copy /b /v /y ..\macos\libparsec.dylib ..\..\examples\unity-rewired\Assets\ParsecUnity\parsec.bundle
