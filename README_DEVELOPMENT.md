## Makefile

Three makefiles:
- Makefile: the default one. Advantage: it is the simplest and easy to reasoning. Disadvantage: must duplicate for release an debug
- Makefile_params: Executed by using `make debug=y`. Advantage: no duplicated lines. Disadvantage: not default make command
- Makefile_permanent: Set a flag in storage. Advantage: can set to mode release and debug permanently, while command still the same for building (`make`). Also, same feature as provided by IDEs or CMAKE . Disadvantage: must state in the documentation how to use it.

## Kyber

- Download kyber and common folders from PQClean.
- Using the "clean" flavor, to allow multi-platform instead of performance.
- Adapt Makefile to add some /common headers and objects to the library.

