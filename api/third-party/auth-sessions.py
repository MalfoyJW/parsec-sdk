import sys
import json
import requests

API_HOST = 'https://kessel-api.parsecgaming.com/'

def auth_sessions(auth_code_hash):
	r = requests.post(API_HOST + 'auth/sessions',
		headers={'Content-Type': 'application/json'},
		data=json.dumps({'grant_type': 'auth_code', 'auth_code_hash': auth_code_hash})
	)

	return json.loads(r.text), r.status_code

if len(sys.argv) < 2:
	print('Usage: auth-sessions.py auth_code_hash')
	sys.exit(1)

res, status_code = auth_sessions(sys.argv[1])

print('\n[%d] /auth/sessions/' % status_code)

if status_code == 201:
	print('\nsession_id = %s' % (res['data']['id']))
