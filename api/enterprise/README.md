# Overview
This document describes how to use the Parsec Enterprise API to retrieve sessions and discover hosts.

We provide examples below as cURL commands and Python code. If have any questions about implementing the API calls in your own game, please reach out to your Enterprise contact.

The Python examples require Python 2.7 and the `requests` package.

# Important Concepts

### API Key
The Enterprise API Key given to you by your Parsec Enterprise contact must be kept private and only used by your server backend, **NOT** included with your client applications. This key is used for calls to `/enterprise/sessions` and can be used to create Sessions for any `external_id` on your system.

### Session ID
A Session ID is string token that is required for secure use of the Parsec API. It is sensitive information, similar to a password, so your application must store the Session ID securely. The SDK needs Session ID in order to be a host or connect to other hosts.

### Hosts
A "Host" refers to a computer that the user may connect to and control remotely.

# API

## Sessions - /enterprise/sessions
The /enterprise/sessions endpoint allows you to create a Session associated with a unique ID from your system (typically, a user ID). This unique ID, called `external_id`, can be any string.

This endpoint may be called multiple times for the same `external_id`, it will return a unique Session ID each time for a new device. You do not need to request a new Session ID every time a device connects -- rather, the intent is that each unique device should have one Session ID.

* Request
    ```text
    POST https://kessel-api.parsecgaming.com/enterprise/

    Headers:
        x-api-key: YOUR_ENTERPRISE_API_KEY
        Content-Type: application/json

    Body:
      {
          "external_id": "SOME_UNIQUE_ID"
      }
    ```

* Response
    ```javascript
    STATUS 201

    {
      "session": {
        "id": "aaaaaaaa1111111111ffffffffffffffffff222222222222222222bbbbbbbbbb", // The session ID
        "expires_at" : {UNIX Epoch time integer},
        "host_peer_id": "1QA0qE1h0aBW7GKRTXCU0ZInLVZ",
        "client_peer_id": "1QA0qBt04fWhJqgII3a1TnsG8Ls",
        //
        // These fields beloware Parsec internal metadata that are subject to change
        // We recommend not recording or relying on these fields
        "user_id": 1234,
        "roles": ["host","client"],
      }
    }
    ```

* Examples
    * cURL
        ```bash
        curl -X "POST" "https://kessel-api.parsecgaming.com/enterprise/sessions" \
          -H 'x-api-key: YOUR_API_KEY' \
          -H 'Content-Type: application/json \
          -d $'{ "external_id": "SOME_UNIQUE_ID" }'
        ```

    * Python
        ```python
        r = requests.post(
          'https://kessel-api.parsecgaming.com/enterprise/sessions',
          headers={'Content-Type': 'application/json', 'x-api-key': YOUR_API_KEY},
          data=json.dumps({'external_id': SOME_UNIQUE_ID})
        )

        response = json.loads(r.text)

        session_id = response['session']['id']
        ```


## Hosts - /hosts
The /hosts endpoint requires a Session ID, and will return all the online Hosts that the given Session ID may connect to, based on the `external_id` provided when creating sessions.

* Request
    ```text
    GET https://kessel-api.parsecgaming.com/hosts/

    Headers:
        Authorization: Bearer YOUR_SESSION_ID
    ```

* Response
    ```javascript
    "data": [
      {
        "peer_id": "1QA0qE1h0aBW7GKRTXCU0ZInLVZ",
        "name": "name set via SDK",
        "user_name": "abcd#43523",
        // These fields below are Parsec internal metadata that are subject to change
        // We recommend not recording or relying on these fields
        "description": "",
        "game": null,
        "players": 0,
        "max_players": 0,
        "public": false,
        "sdk_version": 1,
        "mode": "desktop",
        "user": {user object},
        "user_id": 1234,
        "build": "150-0"
      }
    ],
    "has_more": false
    ```

* Examples
    * cURL
        ```bash
        curl -X "GET" "https://kessel-api.parsecgaming.com/hosts" \
          -H 'Authorization: Bearer YOUR_SESSION_ID'
        ```

    * Python
        ```python
        r = requests.get(
          'https://kessel-api.parsecgaming.com/hosts',
          headers={'Authorization': 'Bearer %s' % YOUR_SESSION_ID}
        )

        response = json.loads(r.text)

        host_peer_id = response['data'][0]['peer_id']
        ```

To host's `peer_id` above is used to make a connection via `ParsecClientConnect` in the SDK.

Your External Provider code and `external_id` will be made available in the `name` member of the `ParsecGuest` struct, i.e. `abcd#43523`. This may be useful for looking up additional user metadata associated with the guest.
