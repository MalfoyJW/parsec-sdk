/*** API ***/

async function auth(email, password, tfa) {
	const res = await fetch(`https://api.parsecgaming.com/v1/auth`, {
		method: 'post',
		headers: {
			'Content-Type': 'application/json; charset=utf-8',
		},
		body: JSON.stringify({
			email,
			password,
			tfa,
		}),
	});

	return await res.json();
}

async function serverList(sessionId) {
	const res = await fetch(`https://kessel-api.parsecgaming.com/hosts/`, {
		method: 'get',
		headers: {
			'Authorization': 'Bearer ' + sessionId,
		},
	});

	return await res.json();
}



/*** UI & PARSEC CLIENT ***/

async function serverTable(sessionId) {
	const json = await serverList(sessionId);
	const table = _('#server-list');

	for (const server of json.data) {
		const tr = addRow(table);
		addTextCol(tr, server.name);
		addTextCol(tr, server.build);
		addTextCol(tr, server.peer_id);
		addTextCol(tr, server.user_name);
		addButtonCol(tr, 'Connect', async () => {
			const container = _('.video-container');
			container.style.display = 'block';
			table.style.display = 'none';

			// Parsec instance and client connection
			const parsec = new Parsec(_('video'), _('audio'), container);
			parsec.handleInput(parsec.Input.All);

			parsec.clientConnect(sessionId, server.peer_id, '');

			// Client status polling interval
			const interval = setInterval(() => {
				const status = parsec.clientGetStatus();

				if (status != parsec.Status.PARSEC_CONNECTING && status != parsec.Status.PARSEC_OK) {
					parsec.clientDisconnect();
					parsec.destroy();

					table.style.display = 'table';
					container.style.display = '';

					if (status !== 0)
						alert(`Exit code: ${status}`);

					clearInterval(interval);
				}
			}, 100);
		});
	}

	const tr = addRow(table);
	addButtonCol(tr, 'Logout', () => {
		delete localStorage.sessionId;
		window.location.reload();
	});
}

async function submit() {
	try {
		const email = _('#email').value;
		const password = _('#password').value;
		const tfa = _('#tfa').value;

		const json = await auth(email, password, tfa);

		if (json.session_id) {
			localStorage.sessionId = json.session_id;
			window.location.reload();
		} else {
			console.log(json);
		}
	} catch (e) {
		console.log(e);
	}
}

function _(selector) {
	return document.querySelector(selector);
}

function addRow(table) {
	const tr = document.createElement('tr');
	table.appendChild(tr);
	return tr;
}

function addTextCol(tr, text) {
	const td = document.createElement('td');
	td.textContent = text;
	tr.appendChild(td);
}

function addButtonCol(tr, text, onclick) {
	const td = document.createElement('td');
	tr.appendChild(td);

	const button = document.createElement('button');
	button.textContent = text;
	button.onclick = onclick;
	td.appendChild(button);
}

function UI() {
	_('#email').onkeyup = _('#password').onkeyup = _('#tfa').onkeyup = (event) => {
		if (event.keyCode === 13) submit();
	};

	if (!localStorage.sessionId) {
		_('#server-list').style.display = 'none';
		_('#auth').style.display = 'table';

	} else {
		_('#auth').style.display = 'none';
		_('#server-list').style.display = 'table';
		serverTable(localStorage.sessionId);
	}
}
