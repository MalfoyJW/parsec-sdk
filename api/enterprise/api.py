import os
import sys
import json
import requests

import tornado.ioloop
import tornado.web

HOST = 'kessel-api.parsecgaming.com'

API_KEY = os.environ.get('PARSEC_API_KEY')
if not API_KEY:
	print 'PARSEC_API_KEY must be set to your as an environment variable'
	sys.exit(1)

class sessions(tornado.web.RequestHandler):
	def get(self):
		# FIXME XXX This is where your usual authentication is handled and user information
		# is retrieved. A good choice for the 'external_id' sent to the Parsec API is your user's
		# unique ID (it MUST be unique). In this example, the 'external_id' is set via the query string.

		external_id = self.get_argument('external_id')

		r = requests.post(
			'https://%s/enterprise/sessions/' % HOST,
			headers={'Content-Type': 'application/json', 'x-api-key': API_KEY},
			json={'external_id': external_id}
		)

		r_json = json.loads(r.text)

		self.write(json.dumps({'sessionID': r_json['session']['id']}))

app = tornado.web.Application([
	(r'/sessions/?', sessions),
], **{
	'debug': True,
})

app.listen(8888)
tornado.ioloop.IOLoop.current().start()
