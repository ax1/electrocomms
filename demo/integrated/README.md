# Demo for integration with existing servers

> Note: this is a minimal integration. Deeper integration can be donde by using FFI or creating native modules. Note that servers receive the shared key and encrypt data at application level. If servers allow to access PSK or change the key in the TLS communication via API, this would be the fastest option. Otherwise, the data is encrypted twice (once in the TLS channel, another in the dedicated encryption). This performance degradation is offset by the security enhancement provided by:
- no change in the existing TLS security
- use of a quantum-resistant key for the secondary encryption
- the secondary encryption algorithm can be different than the TLS one. Also AEAD could be disabled in the secondary algorithm to mek it faster, since message verification is already in the TLS symmetric algorithm.

## Start server

```sh
node server
```

## Start client

```sh
node client
```

