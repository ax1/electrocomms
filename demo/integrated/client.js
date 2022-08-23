/**
 * Client example.
 * 
 * This client simply request a Post-quantum key exchange agreement.
 * Once the server returns OK (not the key), the shared key is retrieved in the stardard output.
 * Note that electrocomms is started in client mode, so once the key is exchanged, we can stop the child process. 
 */

import { promisify } from 'util'
import { execFile } from 'child_process'
const runFile = promisify(execFile)
import { Socket } from 'net'
import { encrypt } from './util.js'

// ---START THE SERVER CLIENT @8081---
const client = new Socket()

client.connect(8081, '127.0.0.1', async function () {
	// Get secure key by using post-quantum
	const skey = await negociateSessionKey()
	console.log('PQ session key = ' + skey)
	const key = Buffer.from(skey, 'hex')
	// Send data securely by using that key
	const msg = "The European Commission is the executive of the European Union. It operates as a cabinet government, with 27 members of the Commission headed by a President."
	const { nonce, enc, tag } = encrypt(key, 'CLIENT_6856', msg)
	client.write(nonce)
	client.write(enc)
	client.write(tag)
	console.log('Message sent')
	client.end()
})

client.on('data', function (data) { console.log('Received: ' + data); client.destroy() })
client.on('close', function () { console.log('Connection closed') })

async function negociateSessionKey() {
	const { stdout, stderr } = await runFile('./electrocomms', ['127.0.0.1', '8080'], { cwd: '../../bin/' })
	return stdout.substring(0, stdout.length - 1)
}
