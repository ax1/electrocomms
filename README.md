# Electrocomms

Provide Quantum resistant communications without changing existing stacks.

This is part of the *STRONGBOX* component, into the WP4, in the [ELECTRON (UE funding) project](https://electron-project.eu/). 

## Selection of the PQ alternatives

There are many approaches to Post-Quantum (PQ) communications. Each ot fhem has advantages but also important drawbacks.

|Approach|Advantages|Disadvantages|
|---|---|---|
|Openssl fork with PQ|Versatility, PQ certificates instead of keys | No ROOT CA to sign certificate, slower than other options| not all chip architectures|not suitable for embeddin|
|Nginx fork with PQ|Server ready to use|Client must be also a PQ (new client or change the client stack)|
|Pre shared Key (PSK) into TLS|Use only the external PQ for shared key. TLS1.3 already allow this|Existing programs may not have PSK as public method in code, so external implementation is still required|
|Using Qdefender lib|Faster to develop|Qdefender license is Tecnalia proprietary for now|
|Plain C implementation|Better suited for servers and embedded, open source is possible|Only for simple scenarios, ad-hoc code|

For the Electron project, since many elements are not still defined, we will opt for the plain C implementation focused on server to server communication. Reasons:
- if the C program is kept simple, it could be also used for low resources systems, with some effort. Other options will never be capable in embedded due to RAM, cycles or size of binary, compilation issues etc.
-  external dependencies (algorithms) can be  linked as open source. The project license can be set to Free and Open Source Project (FOSS). This is a positive point for the European comission funding the Electron project.

## Selection of the algorithms

For the asymmetric part (the key exchange mechanism or KEM), KYBER will be selected. Reasons:
- Selected for standardization in the third round of NIST.
- Lattice family performs really well in most architectures

For the symmetric part (the encryption of data to be transmitted securely) [STILL TO BE SELECTED]

## Licenses

All licenses are permisive open source, see LICENSE file on each subfolder:
- current project: [MIT](/LICENSE)
- Kyber implementation: [Creative Commons Zero CC0](/src/kyber1024/LICENSE)


## Disclaimer

**[ELECTRON "rEsilient and seLf-healed EleCTRical pOwer Nanogrid"](https://electron-project.eu/)**

Call: H2020-SU-DS-2020, Topic: U-DS04-2018-2020, Start Date: 01/10/2021, Duration: 36 months.

This project has received funding from the European Union’s Horizon 2020 research and innovation programme under Grant Agreement No. 101021936.


