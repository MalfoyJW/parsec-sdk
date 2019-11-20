## Web Example

```js
import {Parsec} from './parsec.js';

const client = new Parsec(videoElement, (event) => {
    // Process 'connect' and 'exit' events here
});

client.connect(sessionId, peerId);
```

The constructor takes an HTML5 `<video>` element and can take an optional second callback argument that can receive events such as `connect`, `exit`, `userData`, and `metrics`.

You'll need [Node.js](https://nodejs.org) to run the development server. This project was tested with `node 8.12.0 LTS`.

```bash
node server.js
```

The development server will be running at `localhost:9000`.
