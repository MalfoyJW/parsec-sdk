import sys
import json
import requests

API_HOST = 'https://kessel-api.parsecgaming.com/'

def auth_codes(game_id):
	r = requests.post(API_HOST + 'auth/codes',
		headers={'Content-Type': 'application/json'},
		data=json.dumps({'game_id': game_id})
	)

	return json.loads(r.text), r.status_code

if len(sys.argv) < 2:
	print('Usage: auth-codes.py game_id')
	sys.exit(1)

res, status_code = auth_codes(sys.argv[1])

print('\n[%d] /auth/codes/' % status_code)

if status_code == 201:
	print('\ncode = %s\nauth_code_hash = %s' % (res['data']['user_code'], res['data']['hash']))
