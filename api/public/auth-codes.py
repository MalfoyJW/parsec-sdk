import sys

import api

if len(sys.argv) < 2:
	print 'Usage: auth-codes.py game_id'
	sys.exit(1)

res, status_code = api.auth_codes(sys.argv[1])

print '\n[%d] /auth/codes/' % status_code

if status_code == 201:
	print '\ncode = %s\nauth_code_hash = %s' % (res['data']['user_code'], res['data']['hash'])
