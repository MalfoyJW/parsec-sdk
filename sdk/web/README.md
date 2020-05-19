## Quick Start
```js
const video = document.querySelector('video'); // A <video> element
const audio = document.querySelector('audio'); // An <audio> element
const container = document.querySelector('#container'); // Top level wrapper element (optional)

const parsec = new Parsec(video, audio, container);
parsec.handleInput(parsec.Input.All);

const sessionID = ''; // SessionID acquired via the Parsec API
const peerID = ''; // PeerID acquired via the Parsec API
const secret = ''; // An optional host-defined secret key for private connections

parsec.clientConnect(sessionID, peerID, secret);
```

## Polling Connection Status

After calling `clientConnect`, the `Parsec` object should be polled to query the connection status. The connections status will move from `PARSEC_NOT_RUNNING` -> `PARSEC_CONNECTING` -> `PARSEC_OK` after a successful connection, then back to `PARSEC_NOT_RUNNING` on a graceful disconnect. Abnormal exit codes can be found in the `Parsec.Status` enumeration.

```js
const interval = setInterval(() => {
	const status = parsec.clientGetStatus();

	if (status != parsec.Status.PARSEC_CONNECTING && status != parsec.Status.PARSEC_OK) {
		parsec.clientDisconnect();
		parsec.destroy();

		if (status !== parsec.Status.PARSEC_NOT_RUNNING)
			alert(`Exit Code: ${status}`);

		clearInterval(interval);
	}
}, 100);

```

## Handling Browser Input

By default, without calling `handleInput`, the Parsec Web SDK will not handle any mouse, keyboard, or gamepad input for you. It will also not handle absolute/relative mouse mode transitions or setting the host's cursor image. It is the responsibility of the application to call `clientSendMessage` and `clientPollEvents` to handle host input/output.

To handle certain input/output events automatically, call `handleInput` with a bitwise OR of values from the `Parsec.Input` enumeration:

```js
Parsec.Input.All       // All input will be handled.
Parsec.Input.Gamepad   // Gamepad input will be handled and rumble events will no longer be returned by clientPollEvents.
Parsec.Input.Mouse     // Mouse input will be handled, absolute/relative mode switches will be handled, and cursor events will no longer be returned by clientPollEvents.
Parsec.Input.Keyboard  // Keyboard input will be handled.
```

## Methods

The methods on the `Parsec` class mimic the behavior of the native SDK found in found in [parsec.h](../parsec.h).

```js
// See ParsecDestroy.
destroy()

// See ParsecSetLogCallback.
setLogCallback(callback)

// See ParsecGetBuffer.
getBuffer(key)

// Instruct the SDK to automatically handle browser input evens and filter certain events from clientPollEvents.
// A bitwise OR of values found in the `Parsec.Input` enumeration.
handleInput(input)

// See ParsecClientConnect. All parameters are strings.
clientConnect(sessionID, peerID, secret)

// See ParsecClientGetStatus. Returns an integer ParsecStatus code.
clientGetStatus()

// See ParsecClientGetGuests. Returns an a javascript array of ParsecGuests.
clientGetGuests()

// Returns the current client connection's guestID. Useful for matching your own guestID to the guest list
// returned from clientGetGuests.
clientGetGuestID()

// See ParsecClientDisconnect.
clientDisconnect()

// See ParsecClientSendUserData. `msg` is a string.
clientSendUserData(id, msg)

// See ParsecClientSendMessage. Takes a Javascript object mimicking the members of the ParsecMessage struct.
clientSendMessage(msg)

// See ParsecClientPollEvents. Returns a Javascript objet mimicking the members of the ParsecClientEvent struct.
clientPollEvents()

// See ParsecClientGetStatus. Returns a Javascript object mimicking the ParsecMetrics member of the ParsecClientStatus struct.
clientGetMetrics()

// See ParsecClientGetStatus. Returns true if the network has encountered an unrecoverable error.
clientNetworkFailure()

// Instruct the SDK to temporarily enable/disable the sending of browser input events.
clientBlockInput(block)
```

## Enumerations

```js
Parsec.Input  // Values passed to handleInput
Parsec.Status // Possible return values from clientGetStatus
```

## Example

See [examples/web](/examples/web).
