## Makefile

Three makefile example files:
- Makefile: the default one. Advantage: it is the simplest and easy to reasoning. Disadvantage: must duplicate for release an debug
- Makefile_params: Executed by using `make debug=y`. Advantage: no duplicated lines. Disadvantage: not default make command
- Makefile_permanent: Set a flag in storage. Advantage: can set to mode release and debug permanently, while command still the same for building (`make`). Also, same feature as provided by IDEs or CMAKE . Disadvantage: must state in the documentation how to use it.

## Kyber

- Download kyber and common folders from PQClean.
- Using the "clean" flavor, to allow multi-platform instead of performance.
- Adapt Makefile to add some /common headers and objects to the library.

## Compilation and platform dependency

|Part|Dependencies|OS|
|---|---|---|
|PQ algorithm|none (already the `clean` version)|Linux, Windows?|
|Server socket|pthread lib (POSIX)|Linux (Windows must replace pthread)|
|Client socket|none|Linux (Windows must replace pthread)|

## Acceptance of public key

The aim of the app is **to provide PQ comms into existing servers and communication stacks**, and not changing these servers by forked versions with PQ features (they are still experimental, the PQ algorithms have not been battle tested, etc..., so not recommended as production servers). In addition, the certificates we could create would be self-signed, or not accepted unless clients are also PQ-ready. In this case, signing the public key does not add the security that real PKI requires to be considered safe (which is the root signature?). In the future, production servers and clients will integrate post-quantum features, so it will be a matter of replacing just the certificate, but this is not the case at this stage of the technology.

Options:
- distribute the public key by a safe secondary channel (the public key is only known by allowed clients). Eg: via email o via ad-hoc enrollment between 2 non-PQ servers.
- distibute a signature by a secondary channel. Then future changes and transmissions of the KEM public key would be also signed.
- create a X509 PQ certificate. The same as before. We need another signature we trust to verify that the KEM certificate is valid. 
Therefore, to avoid plain public key attacks:
 - attacker disguised as the PQ server, sending its own public key. Solutions: public key not transmitted in connection, signed key with previously accepted signature, etc.
 - attacker disguised as the PQ client. When public key is not delivered, the attacker is easily detected. When signed key, the attacker just accept the Key and establish connection, we need another step from server to verify that the client is legitimate (authentication).

 Therefore, at this moment the simplest solution to provide PQ comms, while staying away of common potential attacks well known in non-PQ comms, **we set as SECURITY REQUIREMENT, that the enrollment must be done** previously to using PQ comms:
 - either delivering the public key to the allowed clients.
 - or using the existing client-server secure communication to transmit the public key for that channel, and then create the PQ channel wit this app
