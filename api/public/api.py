import requests
import json

API_HOST = 'https://kessel-api.parsecgaming.com/'

def auth_codes(game_id):
	r = requests.post(API_HOST + 'auth/codes',
		headers={'Content-Type': 'application/json'},
		data=json.dumps({'game_id': game_id})
	)

	return json.loads(r.text), r.status_code

def auth_sessions(auth_code_hash):
	r = requests.post(API_HOST + 'auth/sessions',
		headers={'Content-Type': 'application/json'},
		data=json.dumps({'grant_type': 'auth_code', 'auth_code_hash': auth_code_hash})
	)

	return json.loads(r.text), r.status_code

def host_invites(session_id, expires_in, max_grants):
	r = requests.post(API_HOST + 'host-invites',
		headers={'Content-Type': 'application/json', 'Authorization': 'Bearer %s' % session_id},
		data=json.dumps({'expires_in': expires_in, 'max_grants': max_grants})
	)

	return json.loads(r.text), r.status_code

def hosts(session_id):
	r = requests.get(API_HOST + 'hosts',
		headers={'Content-Type': 'application/json', 'Authorization': 'Bearer %s' % session_id}
	)

	return json.loads(r.text), r.status_code
