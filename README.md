# Simplistic Command Server

A simple TCP Server that is able to execute pseudo-commands. By default Listend into localhost and port 7070 (no terminal parameter are provided yet).

I made this kind of server in order to learn better C++. You can do it whatever you want with it, the code and the whole project, should be considered as a public domain work, as long as you do not claim that you make it instead of **Dimitrios Desyllas** (aka **pc_magas** or **pcmagas**).

# Build, develop and run unit test

* `make build`: builds the application.
* `make run` : Builds and runs a production-ready binary executable.
* `make debug`: Debugs the application (needs gdb)
* `make test_command_parser_build`: runs the unit test for command parser.
* `make test_command_parser_run`: is running the unit test compiled above.

On `make` commands you can provide a parameter `DEBUG` with values either `1` or `0`, `1` indicated that the projhect will be build with the appropriate flags in order to be able to debug it with `g++`.

For unit tests I use the `cxxtestgen` and in Ubuntu GNU/Liux is available via the command:

```
sudo apt install cxxtestgen
```

In order to send commands you can utilize the UNIX `nc` command:

```
netcat ^host^ ^port^ <<<$'^command^\n^command^\n...exit\n'
```

A toy example of using the netcat is:

```
 nc -4 localhost 7070 <<<$'hello\nhello\nexit\n'
```

# Command Line arguments and run 

The server uses the following mandatory command-line arguments:

* `-h` That the host is specified.
* `-p` That the post is specified.

Any executable and usefull binary is build upon `build/release` the unit tests are built in `build/testing` in order to run it from the cli on a console run:

```
./build/release/server -h ^host^ -p ^port^
```

# Available commands:

The following commands are available:

* `hello` That returns the message **hello**
* `exit` That indicates the end of the command sequence.

Each command is being seperated with `\n`.