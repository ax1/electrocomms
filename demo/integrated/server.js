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


//---START THE KEM BRIDGE @8080-----
const p = spawn('./electrocomms', ['8080'], { cwd: '../../bin/' })
p.stdout.on('data', data => { const key = data.toString().substring(0, data.length - 1); processSecureData(key).catch(console.error) })
p.stderr.on('data', data => console.error(`stderr: ${data}`))
p.on('close', code => console.log(`child process exited with code ${code}`))

//--START THE SERVER LISTENER @8081----
const server = createServer(function (c) {
  console.log('client connected')
  c.on('data', data => console.log(data.toString()))
  c.on('end', () => console.log('client disconnected'))
  c.on('error', console.error)
})
const port = 8081
server.listen(port)
console.log('Socket server listening at port ' + port)

async function processSecureData(key) {
  console.log(`stdout: ${key}`)
}