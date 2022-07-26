## Overview

This example was tested with Unity Hub version `2017.4.32f1` on Windows 10 64-bit and macOS Mojave, although the recommended version is `2018.4.19f1` as it is the latest LTS version. It should also work with later versions of Unity Hub.

The project is set up with a simple multiplayer structure borrowed from the popular [Tanks Tutorial](https://learn.unity.com/project/tanks-tutorial). The [Parsec Unity SDK](/sdk/ParsecUnity) module lives in [Assets/ParsecUnity](Assets/ParsecUnity).

After running the example, you will be shown a code to pair the example with a Parsec account. Visit the URL displayed next to the code to authenticate securely via the Parsec website. 

You'll then be promted to input some game data to begin hosting. You should NOT select the `public` option unless you want your demo to visible by ALL Parsec users!

After the Parsec SDK has begun hosting, you'll be given a link that can be shared privately for others to join the demo. You may use this link yourself on another computer or in a web browser for testing.

There are two streamers, `ParsecStreamCamera` for streaming one camera, and `ParsecStreamFull` to stream the full end result. They both inherit `ParsecStreamGeneral` which can be used to find it on a camera. On the camera there is a property named Game ID, this needs to be filled in for all network calls to work.

You will need to set your project to use Expirimental 4.6 on Unity Version `2017.4` for the scripting runtime engine in the player settings.

## Parsec SDK Implementation in [`Assets`](Assets)

### GameManager.cs
This file, as in the tank demo, in this case we added a players object, that will have the local player in Element 0, and assign remote players to the remaining slots. So Size needs to be at least 1 for local play.

`void GetAccessCode()` - This function is assigned to the button to get the user access code to give access for this application to stream. The `streamer.RequestCodeAndPoll` function is the one that gets the values.

`void AuthenticationPoll(ParsecUnity.API.SessionResultDataData data, ParsecUnity.API.SessionResultEnum status)` this function gets automatically called after calling `GetAccessCode()`

`void StartParsec()` this function starts parsec streaming

`void StopParsec()` this function stops parsec streaming

### ParsecSampleScene.unity
This is the sample scene with the objects.

### PlayerManager.cs
This file has the same functionality as the tanks one, but only adds the guest state by `m_AssignedGuest`
Calls `ParsecInput.AssignGuestToPlayer` to bind the `ParsecInput` calls to a certain guest number.

`public void Setup()` this is where we assign the guest to a player.

### PlayerMovement.cs
This file parses the input from remote players, the changes here is mainly from `Input.GetKey(KeyCode.LeftArrow)` to `Input.GetKey(player, KeyCode.LeftArrow)`

`void Update()` called every frame by unity to do movement stuff, see the tank tutorial for more details.

### PlayerObject.prefab
This has the player object, with the PlayerMovement script assigned
