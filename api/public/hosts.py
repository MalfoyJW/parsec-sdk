import sys

import api

if len(sys.argv) < 2:
	print 'Usage: hosts.py session_id'
	sys.exit(1)

res, status_code = api.hosts(sys.argv[1])

print '\n[%d] /hosts/' % status_code

if status_code == 200:
	print '\n{0:<20} {1}'.format('NAME', 'PEER_ID')
	print '{0:<20} {1}'.format('----', '-------')

	for host in res['data']:
		print '{0:<20} {1}'.format(host['name'], host['peer_id'])
