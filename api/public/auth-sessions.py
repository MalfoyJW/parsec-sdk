import sys

import api

if len(sys.argv) < 2:
	print 'Usage: auth-sessions.py auth_code_hash'
	sys.exit(1)

res, status_code = api.auth_sessions(sys.argv[1])

print '\n[%d] /auth/sessions/' % status_code

if status_code == 201:
	print '\nsession_id = %s' % (res['data']['id'])
