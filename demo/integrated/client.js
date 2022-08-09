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
runFile('../../bin/electrocomms', ['127.0.0.1', '8080'], { cwd: '../../bin/' })
	.then(({ stdout, stderr }) => { console.log(stdout); console.error(stderr) })