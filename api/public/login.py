import getpass

import api

email = raw_input('Email address: ')
password = getpass.getpass('Password: ')

res, status_code = api.login(email, password)

if status_code == 403 and res.get('tfa_required'):
	tfa = raw_input('TFA code: ')
	res, status_code = api.login(email, password, tfa)

print '\n[%d] /v1/auth/' % status_code

if status_code == 200:
	print '\nsession_id = %s' % res['session_id']
