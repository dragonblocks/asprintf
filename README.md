# Dragonport

Dragonport is a small C library to provide portable implementations of some GNU or Linux only methods that [dragonblocks_alpha](https://github.com/dragonblocks/dragonblocks_alpha) depends on.
It also includes methods that are technically in the POSIX standard, but are not implemented on some target platforms (or the target platforms only conform with an older standard, like Plan 9 APE).
Where possible, dragonblocks will use an already existing library, this library is just a collection of code that is part of a bigger project that dragonblocks should not depend on or that is not compatible with dragonblocks without modifications.
This library is only capable of what dragonblocks needs, and it does not intend to be general purpose.

## Implementations
* `asprintf.c`: Taken from [libressl-portable](https://github.com/libressl-portable/portable/blob/master/crypto/compat/bsd-asprintf.c).
