# Overview

This document describes the Parsec API endpoints that allow third-party apps to authenticate Parsec users and obtain a `sessionID` without an email and password. If you are using Unity, the Parsec Unity SDK already takes care of these API calls.

Please see the cURL command examples below and the example scripts in Python. Please reach out at `sdk@parsecgaming.com` if you have any questions.

The Python examples require Python 3.0 and the `requests` package:

`pip3 install requests`

# Important Concepts

### Session ID
A `sessionID` is string token that is required for secure use of the Parsec API. It is sensitive information, similar to a password, so your application must store the `sessionID` securely. The Parsec SDK needs a `sessionID` to host via `ParsecHostStart` and connect via `ParsecClientConnect`.

### Auth Code
An Auth Code is different from a `sessionID` -- it is a way for a user to securely login and provide your SDK integration with a `sessionID`, without directly giving you their email and password.

# API

## Auth Codes - /auth/codes
The Auth Codes allow for a user to sign in and obtain a `sessionID` without providing their password directly to your app. The workflow is as such:

1. You create a new Auth Code with a POST to the `/auth/codes` endpoint.
1. You begin polling with POST requests against `/auth/sessions` with the `hash` received in Step 1 and a `grant_type` of `auth_code`. The Auth Code will be valid for 30 minutes from the time it was created.
1. The user visits `https://parsec.gg/activate` in their browser and enters in the `user_code` received in Step 1
**_Important:_** An Auth Code is not the same as a `sessionID`. An Auth Code will be exchanged for a `sessionID`, which is then what you use for authenticated API calls.
1. Once the user signs in and approves the `user_code` in the browser, the polling against `/auth/sessions` will receive a response with a `sessionID`

The first step in obtaining a `sessionID` securely is making a call to the `/auth/codes` endpoint. An example of this is found in the `auth-codes.py` example script. You must submit your Parsec supplied `game_id` as a command line argument to the script. Please contact us if you do not have a `game_id`.

* Request
  ```text
  POST https://kessel-api.parsecgaming.com/auth/codes

  Headers:
    Content-Type: application/json

  Body:
    {
      "game_id": "xxxxxxxx"
    }
  ```

* Response
  ```javascript
  STATUS 201

  {
    "data": {
      "verification_uri": "https://parsec.gg/activate", // The URL for user to visit
      "user_code": "ABCD3456", // The code the user will enter after logging in at above URL
      "hash": "0ujsswThIGTUYm2K8FjOOfXtY1K", // The hash to send in the /auth/sessions polling call
      "expires_at": {UNIX Epoch time},
      "interval": 5 // Number of seconds you should wait between polling calls to /auth/sessions
    }
  }
  ```

* cURL Example
  ```bash
  curl -X "POST" "https://kessel-api.parsecgaming.com/auth/codes" \
    -H 'Content-Type: application/json' \
    -d $'{ "game_id": "YOUR_GAME_ID" }'
  ```

## Sessions Polling - /auth/sessions
You will poll against this endpoint with the `hash` for the Auth Code created above, and eventually will receive a response with 3 possible status codes:

| Status | Description |
| ------ | ----------- |
| 202 | The Auth Code is pending approval, keep polling |
| 201 | The Auth Code has been approved by the user, the `sessionID` is in the response body |
| 401 | The Auth Code is invalid or has been denied by the user |

* Request
  ```text
  POST https://kessel-api.parsecgaming.com/auth/sessions

  Headers:
    Content-Type: application/json

  Body:
    {
      "grant_type": "auth_code",
      "auth_code_hash": {hash from above)
    }
  ```

* Response
  ```javascript
  {
    "data": {
      "id": "a30436aa3d110ffffaf6e84c3037dc4635a18135ca92eea49e4ca7388e158aaa", // the `sessionID`
      "user_id": 1525260,
      "roles": [ "host" ],
      "host_peer_id": "1QA0qE1h0ABW7GKRTXCU0ZInLVz",
      "expires_at": 1569790281
    }
  }
  ```

* cURL Example
  ```bash
  curl -X "POST" "https://kessel-api.parsecgaming.com/auth/sessions" \
    -H 'Content-Type: application/json' \
    -d $'{ "grant_type": "auth_code", "auth_code_hash": "YOUR_AUTH_CODE_HASH" }'
  ```

You can now pass this `sessionID` to the Parsec SDK to make connections or begin hosting.

# Fetching Available Hosts

See [/api/personal](/api/personal#hosts---v2hosts) for documentation of the `/v2/hosts` API endpoint. `/v2/hosts` is the only way to retrieve available hosts.
