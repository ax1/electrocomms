
import { Socket } from 'net'

const client = new Socket();
client.connect(8080, '127.0.0.1', function () {
	const msg = "The European Commission is the executive of the European Union. It operates as a cabinet government, with 27 members of the Commission headed by a President."
	console.log("Sending message")
	client.write(msg)
	client.end()
})

/*
client.on('data', function (data) {
	console.log('Received: ' + data)
	client.destroy()
})

client.on('close', function () {
	console.log('Connection closed')
})
*/