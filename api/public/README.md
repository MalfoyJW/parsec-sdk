# Overview
This document describes the Parsec API endpoints that allow the SDK to host games and send invites to other users. If you are using Unity, the Parsec Unity SDK already takes care of these API calls.

We provide examples below as cURL commands and Python code. If have any questions about implementing the API calls in your own game, please reach out in our Discord `#devs` channel or send an email to `sdk@parsecgaming.com`

The Python examples require Python 2.7 and the `requests` package.

- [Overview](#overview)
- [Important Concepts](#important-concepts)
    - [Session ID](#session-id)
    - [Auth Code](#auth-code)
    - [Hosts](#hosts)
    - [Host Invites](#host-invites)
- [API](#api)
  - [Auth Codes - /auth/codes](#auth-codes---authcodes)
  - [Sessions Polling - /auth/sessions](#sessions-polling---authsessions)
  - [Host Invites - /host-invites](#host-invites---host-invites)

# Important Concepts

### Session ID
A Session ID is string token that is required for secure use of the Parsec API. It is sensitive information, similar to a password, so your application must store the Session ID securely. The SDK needs Session ID in order to host games and create host invites. Your game can obtain a Session ID for the user with [Auth Codes](#auth-codes).

### Auth Code
An Auth Code is different from a Session ID -- it is a way for a user to securely login and provide your SDK integration with a Session ID, without directly giving you their email and password.

### Hosts
A "Host" or a game that is "Hosting" refers to a game that other users can connect to and play via Parsec

### Host Invites
A host invite is a temporary link that allows other users to join your game, once it is hosting.

# API
## Auth Codes - /auth/codes
The Auth Codes allow for a user to sign in and obtain a Session ID without providing their password directly to your app. The workflow is as such:

1. You create a new Auth Code with a POST to the `/auth/codes` endpoint
1. You begin polling with POST requests against `/auth/sessions` with the `hash` received in Step 1 and a `grant_type` of `auth_code`.
1. The user visits `https://parsec.gg/activate` in their browser and enters in the `user_code` received in Step 1
**_Important:_** An Auth Code is not the same as a Session ID. An Auth Code will be exchanged for a Session ID, which is then used for authenticated API calls.
1. Once the user signs in and approves the `user_code` in the browser, the polling against `/auth/sessions` will receive a response with a Session ID

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

* Examples
    * cURL
        ```bash
        curl -X "POST" "https://kessel-api.parsecgaming.com/auth/codes" \
          -H 'Content-Type: application/json' \
          -d $'{ "game_id": "YOUR_GAME_ID" }'
        ```

    * Python
        ```python
        r = requests.post(
          'https://kessel-api.parsecgaming.com/auth/codes',
          headers={'Content-Type': 'application/json'},
          data=json.dumps({'game_id': YOUR_GAME_ID})
        )

        response = json.loads(r.text)

        user_code = response['data']['user_code']
        hash = response['data']['hash']
        ```

## Sessions Polling - /auth/sessions
You will poll against this endpoint with the `hash` for the Auth Code created above, and eventually will receive a response with 3 possible status codes:

| Status | Description |
| ------ | ----------- |
| 202 | The Auth Code is pending approval, keep polling |
| 201 | The Auth Code has been approved by the user, the Session ID is in the response body |
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
        "id": "a30436aa3d110ffffaf6e84c3037dc4635a18135ca92eea49e4ca7388e158aaa", // the Session ID
        "user_id": 1525260,
        "roles": [ "host" ],
        "host_peer_id": "1QA0qE1h0ABW7GKRTXCU0ZInLVz",
        "expires_at": 1569790281
      }
    }
    ```

* Examples
    * cURL
        ```bash
        curl -X "POST" "https://kessel-api.parsecgaming.com/auth/sessions" \
          -H 'Content-Type: application/json' \
          -d $'{ "grant_type": "auth_code", "auth_code_hash": "YOUR_AUTH_CODE_HASH" }'


        ```

    * Python
        ```python
        r = requests.post('https://kessel-api.parsecgaming.com/auth/sessions',
          headers={'Content-Type': 'application/json'},
          data=json.dumps({'grant_type': 'auth_code', 'auth_code_hash': YOUR_AUTH_CODE_HASH})
        )

        response = json.loads(r.text)

        session_id = response['data']['id']
        ```

You can now pass this Session ID to the SDK to begin Hosting your game.

## Host Invites - /host-invites
Once your game is Hosting, you can create an invite link to give to other users and allow them to join your game. A Session ID is required for creating a Host Invite.


* Request
    ```text
    POST https://kessel-api.parsecgaming.com/host-invites

    Headers:
      Authorization: Bearer YOUR_SESSION_ID
      Content-Type: application/json

    Body:
      {
        "expires_in": {integer between 600 and 108000}, // number of seconds before the Invite expires
        "max_grants": {integer between 1 and 100} // number of times this invite can be used
      }
    ```

* Response
    ```javascript
    {
      "data": {
        "code": "87AF7M3P", // the Invite code
        "peer_id": "1PR4MhUjhravzLr5irhKfGUNZN2",
        "grants": 0,
        "max_grants": 20,
        "expires_at": 1566589883
      }
    }
    ```

* Examples
    * The examples below create an Invite code that expires in 1 hour and can be used 20 times.
    * cURL
        ```bash
        curl -X "POST" "https://kessel-api.parsecgaming.com/host-invites" \
          -H 'Authorization: Bearer YOUR_SESSION_ID' \
          -H 'Content-Type: application/json' \
          -d $'{ "expires_in": 3600, "max_grants": 20 }'
        ```

    * Python
        ```python
        r = requests.post('https://kessel-api.parsecgaming.com/host-invites',
          headers={'Content-Type': 'application/json', 'Authorization': 'Bearer %s' % YOUR_SESSION_ID},
          data=json.dumps({'expires_in': 3600, 'max_grants': 20})
        )

        response = json.loads(r.text)

        invite_code = response['data']['code']
        ```

The code may be shared with others and used at `https://parsec.gg/g/{CODE}`. The landing page will walk the user through making a connection.
