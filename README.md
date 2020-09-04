# smpl

The `smpl` data format is a human readable and easy to parse data format, prioritizing ease of parsing in C.

The following principles are what defines `smpl`:

* Needs to be human readable and data types should be easily inferred
* Should take a very minimal amount of C code to parse a given file. C is given precedence.
* The file should be easily extensible and have no specific limitation on length or contents.
* A file should also be parsable with the removal of all whitespace. (newlines, spaces, etc.)

A binary format will also be created using the same principles.
