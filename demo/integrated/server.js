/**
 * Server example
 * 
 * The server starts an electrocomms app as 'server' mode
 * 
 * Whenever a client requests a secure connection key, 
 * by usinng Post-quantum KEM, the key is retrieved in the stdout.
 * Note that the electrocomms in server mode is always alive, to 
 * provide KEM to clients.
 */
import { spawn } from 'child_process'

const p = spawn('../../bin/electrocomms', ['8080'], { cwd: '../../bin/' })

p.stdout.on('data', data => console.log(`stdout: ${data}`))
p.stderr.on('data', data => console.error(`stderr: ${data}`))
p.on('close', code => console.log(`child process exited with code ${code}`))