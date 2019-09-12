import sys

import api

if len(sys.argv) < 4:
	print 'Usage: host-invites.py session_id expires_in max_grants'
	sys.exit(1)

res, status_code = api.host_invites(sys.argv[1], int(sys.argv[2]), int(sys.argv[3]))

print '\n[%d] /host-invites/' % status_code

if status_code == 201:
	print '\ncode = %s' % (res['data']['code'])
