# Minishell

[cite_start]*This project has been created as part of the 42 curriculum by lartes-s.* [cite: 147]

## Description
[cite_start]Minishell is a minimalist implementation of a shell, designed to recreate a "little Bash" environment[cite: 5]. [cite_start]This project serves as an extensive introduction to process management, file descriptors, and the challenges developers faced before modern graphical interfaces[cite: 6, 16].

Key features include:
* [cite_start]**Interactive Prompt**: Displays a prompt when waiting for a new command[cite: 96].
* [cite_start]**Command History**: A working history mechanism using the `readline` library[cite: 97].
* [cite_start]**Execution**: Searches and launches the correct executable based on the `PATH` variable or absolute/relative paths[cite: 98].
* **Redirections**:
    * [cite_start]`<` Redirects input[cite: 112].
    * [cite_start]`>` Redirects output[cite: 113].
    * [cite_start]`<<` Heredoc mode; reads input until a delimiter is encountered[cite: 114].
    * [cite_start]`>>` Redirects output in append mode[cite: 116].
* [cite_start]**Pipes**: Connects the output of one command to the input of the next using `|`[cite: 117].
* [cite_start]**Variables**: Handles environment variable expansion (`$VAR`) and the `$?` exit status[cite: 118, 119].
* [cite_start]**Signals**: Proper handling of `ctrl-C`, `ctrl-D`, and `ctrl-\` to mimic Bash behavior in interactive mode[cite: 120].
* [cite_start]**Built-ins**: Implementation of `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`, and `exit` [cite: 125-132].

## Instructions

### Compilation
[cite_start]The project must be compiled using a provided `Makefile` which uses the `cc` compiler with the flags `-Wall -Wextra -Werror`[cite: 26].

To compile the mandatory part, run:
```bash
make