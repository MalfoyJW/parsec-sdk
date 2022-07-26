## Quick Start
```js
const video = document.querySelector('video'); // A <video> element
const audio = document.querySelector('audio'); // An <audio> element
const container = document.querySelector('#container'); // Top level wrapper element (optional)

const parsec = new Parsec(video, audio, container);

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

## Methods

The methods on the `Parsec` class mimic the behavior of the native SDK found in found in [parsec.h](../parsec.h).

```js
// See ParsecDestroy.
destroy()

// See ParsecSetLogCallback.
setLogCallback(callback)

// See ParsecGetBuffer.
getBuffer(key)

// See ParsecClientConnect. All parameters are strings.
clientConnect(sessionID, peerID, secret)

// See ParsecClientGetStatus. Returns an integer ParsecStatus code.
clientGetStatus()

// See ParsecClientGetGuests. Returns an a javascript array of ParsecGuests.
clientGetGuests()

// Returns the current client connection's guestID. Useful for matching your own guestID to the guest list
// returned from clientGetGuests.
clientGetSelf()

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
```

## Enumerations

```js
Parsec.Status // Possible return values from clientGetStatus
```

## Example

See [examples/web](/examples/web).
