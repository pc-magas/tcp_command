# Simplistic Command Server

A simple TCP Server that is able to execute pseudo-commands. By default Listend into localhost and port 7070 (no terminal parameter are provided yet).

 made this kind of server in order to learn better C++. You can do it whatever you want with it, the code and the whole project, should be considered as a public domain work, as long as you do not claim that you make it instead of **Dimitrios Desyllas**.

# Build & test

* `make build`: builds the application.
* `make test_command_parser_build`: runs the unit test for command parser.
* `test_command_parser_run`: is running the unit test compiled above.

On `make` commands you can provide a parameter `DEBUG` with values either `1` or `0`, `1` indicated that the projhect will be build with the appropriate flags in order to be able to debug it with `g++`.

For unit tests I use the `cxxtestgen` and in Ubuntu GNU/Liux is available via the command:

```
sudo apt install cxxtestgen
```