import {Parsec} from './parsec.js';


/*** API ***/

const OLD_HOST = 'api.parsecgaming.com';
const HOST = 'kessel-api.parsecgaming.com';

async function auth(email, password, tfa) {
	const res = await fetch(`https://${OLD_HOST}/v1/auth`, {
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
	const res = await fetch(`https://${HOST}/hosts/`, {
		method: 'get',
		headers: {
			'Authorization': 'Bearer ' + sessionId,
		},
	});

	return await res.json();
}


/*** MAIN ***/

function _(selector) {
	return document.querySelector(selector);
}

function toggleFullscreen(element) {
	if (document.webkitFullscreenElement) {
		document.webkitExitFullscreen();

	} else {
		element.webkitRequestFullscreen();

		if (navigator.keyboard && navigator.keyboard.lock)
			navigator.keyboard.lock();
	}
}

function runClient(elementVideo, sessionId, serverId) {
	return new Promise((resolve) => {
		//set up client object with an event callback: gets connect, status, chat, and shutter events
		const client = new Parsec(elementVideo, (event) => {
			console.log('EVENT', event);

			if (event.type === 'exit') {
				document.removeEventListener('keydown', hotkeys, true);
				resolve(event.code);
			}
		});

		//set up useful hotkeys that call client methods: destroy can also be used to cancel pending connection
		const hotkeys = (event) => {
			event.preventDefault();

			if (event.code === 'Backquote' && event.ctrlKey && event.altKey) {
				client.destroy(0);

			} else if (event.code === 'KeyW' && event.ctrlKey && event.altKey) {
				toggleFullscreen(element);
			}
		};
		document.addEventListener('keydown', hotkeys, true);

		client.connect(sessionId, serverId);
	});
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
			const elementVideo = _('video');

			table.style.display = 'none';
			container.style.display = 'block';

			const code = await runClient(elementVideo, sessionId, server.peer_id);

			table.style.display = '';
			container.style.display = '';

			element.src = '';
			element.load();

			if (code !== 0)
				alert(`Exit code: ${code}`);
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

export function ui() {
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
