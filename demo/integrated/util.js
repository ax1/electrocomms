import * as crypto from 'crypto'
import { Buffer } from 'buffer'

export function encrypt(key, id, dec) {
  const nonce = crypto.randomBytes(12)
  const cipher = crypto.createCipheriv('chacha20-poly1305', key, nonce, { authTagLength: id.length })
  cipher.setAAD(id)
  const enc = cipher.update(dec)
  cipher.final()
  const tag = cipher.getAuthTag()
  return { nonce, enc, tag }
}

export function decrypt(key, id, nonce, enc, tag) {
  const decipher = crypto.createDecipheriv("chacha20-poly1305", key, nonce, { authTagLength: id.length })
  decipher.setAAD(id)
  const dec = decipher.update(enc)
  decipher.setAuthTag(tag)
  decipher.final()
  return dec
}

function test() {
  const key = crypto.randomBytes(32)
  const id = Buffer.from("myID")
  const msg = "This is a test"
  const data = Buffer.from(msg)

  const { nonce, enc, tag } = encrypt(key, id, data)
  const res = decrypt(key, id, nonce, enc, tag)
  console.log(res.toString('utf-8'))
}

test()