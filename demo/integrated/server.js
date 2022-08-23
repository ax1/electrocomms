/**
 * Server example
 * 
 * The server starts an electrocomms app as 'server' mode
 * 
 * Whenever a client requests a secure connection key, 
 * by using Post-Quantum KEM, the key is retrieved in the stdout.
 * Note that the electrocomms in server mode is always alive, to 
 * provide KEM to clients.
 */
import { spawn } from 'child_process'
import { createServer } from 'net'
import { decrypt } from './util.js'

// ---START THE SERVER LISTENER @8081---
const server = createServer(function (c) {
  console.log('client connected')
  let key = null
  const buf = Buffer.alloc(10000)
  let offset = 0
  c.on('data', data => {
    if (!key) key = Buffer.from(SKEY, 'hex')
    buf.fill(data, offset, offset + data.length)
    offset += data.length
  })
  c.on('end', data => {
    const id = 'CLIENT_6856' // note this value can be a "secondary" secret
    const tagl = id.length
    const nonce = buf.subarray(0, 12)
    const enc = buf.subarray(12, offset - tagl)
    const tag = buf.subarray(offset - tagl, offset)
    const msg = decrypt(key, id, nonce, enc, tag)
    console.log(msg.toString('utf-8'))
    console.log('client disconnected')
  })
  c.on('error', console.error)
})
const port = 8081
server.listen(port)
console.log('Socket server listening at port ' + port)

// ---START THE KEM BRIDGE @8080----
const p = spawn('./electrocomms', ['8080'], { cwd: '../../bin/' })
p.stdout.on('data', data => { const key = data.toString().substring(0, data.length - 1); processSecureData(key).catch(console.error) })
p.stderr.on('data', err => { console.error(`stderr: ${err}`); process.exit(409) })
p.on('close', code => console.log(`child process exited with code ${code}`))
p.on('exit', code => console.log('pasa por p.exit'))


let SKEY = null
async function processSecureData(skey) {
  console.log('PQ session key = ' + skey)
  SKEY = skey
}

process.on('uncaughtException', (err, origin) => { if (p) p.kill(1); console.log(err); process.exit(1) })