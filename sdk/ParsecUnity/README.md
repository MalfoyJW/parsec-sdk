## Parsec Unity SDK
The Parsec Unity SDK uses shared objects from [sdk/windows](../windows) and [sdk/macos](../macos). The macOS `libparsec.dylib` is renamed to `parsec.bundle`. To copy them run `runmefirst.bat` or `runmefirst.sh`.

See [examples/unity](/examples/unity) for a walkthrough and detailed example.

## Interface Details

### ParsecStreamer Class
| Function | Description |
|----------|-------------|
| `SessionData RequestCodeAndPoll()` | Request an oauth token for polling |
| `onUserAuthenticated<SessionResultDataData, SessionResultEnum>` | Event called when there is an update regarding the access token |
| `GuestConnected(object, ParsecGuest)` | Event called when there's a guest connecting |
| `GuestDisconnected(object, ParsecGuest)` | Event called when a guest disconnected |
| `void StartParsec(int max_players, bool public_game, string gamename, string description, string session_id)` | Start streaming an application |
| `string GetInviteUrl(SessionResultDataData session, uint expiresInSeconds, uint maxUses)` | Function to get an Invite link |
| `void StopParsec()` | Call this to stop streaming. |

### ParsecInput Class
This class is the same as the [Unity Input](https://docs.unity3d.com/ScriptReference/Input.html), but only adds the `player` parameter to each function. To assign a Guest to a Player, call the `AssignGuestToPlayer` function in this class, and call `UnassignGuest` when done. The Guest is automatically unassigned when they disconnect. If you want the guests to use the mouse on elements, set `ParsecUnity.ParsecInput.AllowUIActions` to `true`, this checks when the mouse gets clicked, if the object has the `onClick` property, or the `Select` function, it will execute this.

### Rewired Support
Parsec has support for [Rewired](https://assetstore.unity.com/detail/tools/utilities/rewired-21676) they will be CustomControllers, you will have to call `ParsecRewiredInput.AssignCustomControllerToUser`, `ParsecRewiredInput.AssignKeyboardControllerToUser` and `ParsecRewiredInput.AssignMouseControllerToUser` to assign them to a guest, where you create the custom controller with `ReInput.controllers.CreateCustomController` and give it a unique id like `"Parsec_" + guest.id`.

As a precaution, uncheck "Assign Mouse on Start" and "Assign Keyboard on Start". For the rest it's the same as any other rewired project.

The file [ParsecRewiredInputManagerDataExport.json](ParsecRewiredInputManagerDataExport.json) has the Custom Controllers, and the Custom Controller Maps.
