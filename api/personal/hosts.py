import sys
import json
import requests

API_HOST = 'https://kessel-api.parsecgaming.com/'

def hosts(session_id, mode, public):
	r = requests.get(API_HOST + 'v2/hosts?mode=%s&public=%s' % (mode, 'true' if public else 'false'),
		headers={'Content-Type': 'application/json', 'Authorization': 'Bearer %s' % session_id}
	)

	return json.loads(r.text), r.status_code

if len(sys.argv) < 2:
	print('Usage: hosts.py session_id')
	sys.exit(1)

res, status_code = hosts(sys.argv[1], 'desktop', False)

print('\n[%d] /v2/hosts/' % status_code)

if status_code == 200:
	print('\n{0:<20} {1}'.format('NAME', 'PEER_ID'))
	print('{0:<20} {1}'.format('----', '-------'))

	for host in res['data']:
		print('{0:<20} {1}'.format(host['name'], host['peer_id']))
