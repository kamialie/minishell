# minishell

Minimal version of shell binary based on zshell.

### Supported features

- built-ins: echo, cd, setenv, unsetenv, env, exit
- expansions: $ and ~
- separation of commands with ";"
- Ctrl-C signal

### Usage

compile the project with make command

run ./minishell and enjoy the shell ;)

### Project commands

make - compile executable

make clean - remove object files

make fclean - make clean plus remove library and executable

make re - remove all temporary files and compile the project again
