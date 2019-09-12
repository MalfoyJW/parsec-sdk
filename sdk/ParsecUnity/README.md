## Parsec Unity SDK
The Parsec Unity SDK uses shared objects from [sdk/windows](../windows) and [sdk/macos](../macos). The macOS `libparsec.dylib` is renamed to `parsec.bundle`. They are copied into this directory for convenience.

See [examples/unity](/examples/unity) for a walkthrough and detailed example.

## Interface Details

### ParsecStreamer Class
| Function | Description |
|----------|-------------|
| `SessionData RequestCodeAndPoll(string gameId)` | Request an oauth token for polling |
| `onUserAuthenticated<SessionResultDataData, SessionResultEnum>` | Event called when there is an update regarding the access token |
| `GuestConnected(object, ParsecGuest)` | Event called when there's a guest connecting |
| `GuestDisconnected(object, ParsecGuest)` | Event called when a guest disconnected |
| `void StartParsec(int max_players, bool public_game, string gamename, string description, string session_id)` | Start streaming an application |
| `string GetInviteUrl(SessionResultDataData session, uint expiresInSeconds, uint maxUses)` | Function to get an Invite link |
| `void StopParsec()` | Call this to stop streaming. |

### ParsecInput Class
This class is the same as the [Unity Input](https://docs.unity3d.com/ScriptReference/Input.html), but only adds the `player` parameter to each function. To assign a Guest to a Player, call the `AssignGuestToPlayer` function in this class, and call `UnassignGuest` when done. The Guest is automatically unassigned when they disconnect.
