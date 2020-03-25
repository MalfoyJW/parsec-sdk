#!/bin/sh

cp -f "ParsecUnity46.dll" "../../examples/unity/Assets/ParsecUnity/"
cp -f "ParsecUnity46.dll" "../../examples/unity-rewired/Assets/ParsecUnity/"

cp -f "../windows/Parsec.dll" "./"
cp -f "../windows/Parsec.dll" "../../examples/unity/Assets/ParsecUnity/"
cp -f "../windows/Parsec.dll" "../../examples/unity-rewired/Assets/ParsecUnity/"

cp -f "../windows/Parsec32.dll" "./"
cp -f "../windows/Parsec32.dll" "../../examples/unity/Assets/ParsecUnity/"
cp -f "../windows/Parsec32.dll" "../../examples/unity-rewired/Assets/ParsecUnity/"

cp -f "../macos/libparsec.dylib" "./parsec.bundle"
cp -f "../macos/libparsec.dylib" "../../examples/unity/Assets/ParsecUnity/parsec.bundle"
cp -f "../macos/libparsec.dylib" "../../examples/unity-rewired/Assets/ParsecUnity/parsec.bundle"

