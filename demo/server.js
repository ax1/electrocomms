import { createServer } from 'net'

const server = createServer(function (c) {
  console.log('client connected')
  c.on('data', data => console.log(data.toString()))
  c.on('end', () => console.log('client disconnected'))
})

const port = 8080
server.listen(port)
console.log('Socket server listening at port ' + port)