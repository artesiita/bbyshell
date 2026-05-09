_This project has been created as part of the 42 curriculum by <becanals> and <lartes-s>_

# MINISHELL

## DESCRIPTION
Minishell is a project centered around creating a simple shell, essentially a personalized version of Bash. The goal is to gain extensive knowledge regarding process creation, management, and file descriptors.  

Our implementation, bbyshell, features a functional command-line interface that handles:
* __Command execution:__ Searching and launching executables using the PATH variable or absolute/relative paths.  
* __Built-in commands:__ Internal implementations of echo, cd, pwd, export, unset, env, and exit.  Redirections: Supporting input `<` , output `>` , append `>>` , and heredoc `<<`.  
* __Pipes:__ Connecting the output of one command to the input of the next.  
* __Environment variables:__ Expansion of $VAR and the exit status $?.  
* __Signal handling:__ Mimicking Bash behavior for `ctrl-C`, `ctrl-D`, and `ctrl-\`.

### Project Objectives
✅ Interpret and execute commands    
✅ Environment variable management   
✅ Implement basic built-ins   
✅ Handle pipes and redirections   
✅ Variable expansion   
✅ Signal control (SIGINT, SIGQUIT)   
✅ Heredocs and quotes 

### Implemented Built-ins
* `echo`: Prints arguments (with `-n` option)  
* `cd`: Changes the current directory  
* `pwd`: Prints the current working directory  
* `export`: Defines or updates environment variables
* `unset`: Removes environment variables  
* `env`: Displays the current environment variables  
* `exit`: Exits the shell

### Funcionalities
🔹 __Interactive Prompt:__ Displays a prompt `bbyshell> ` when waiting for new commands.  
🔹 __History:__ Working command history integrated with readline.  
🔹 __Pipes:__ `cmd1 | cmd2 | cmd3` connects the output of one command to the input of the next.  
🔹 __Redirections:__ Supports `<`, `>`, `>>`, and `<<` (heredoc).  
🔹 __Expansion:__ Handles `$VAR` environment variables and `$?` for the last exit status.  
🔹 __Quotes:__ Supports single quotes `'text'` (literal) and double quotes `"$VAR"` (expansion allowed).  
🔹 __Signals:__ Handles `Ctrl-C`, `Ctrl-D`, and `Ctrl-\` behaving like Bash.  
🔹 __External Commands:__ Searches and launches executables using the `PATH` variable or absolute/relative paths.  
🔹 __Terminal Control:__ Managed through termios and ioctl for a seamless shell experience.  

## INSTRUCTIONS

### Compilation
The project includes a `Makefile` that compiles the source files using `cc` with the flags `-Wall -Wextra -Werror`. To compile the program, run the following command in your terminal:

```bash
make
```

### Execution
Once compiled, you launch the shell by running:
```bash
./minishell
```

### Makefile rules
* `make`: Compiles the mandatory part of the project.
* `make clean`: Remove the object files.
* `make fclean`: Removes object files and the executable.
* `make re`: Performs a full recompilation (fclean followed by all).

### Project Structure

```Plaintext
.
├── Makefile                # Compiles the project with -Wall, -Wextra, -Werror 
├── README.md               # Project documentation
├── readline.supp           # Valgrind suppression file for readline memory leaks 
├── inc/                    # Header files
│   └── minishell.h         # Main project header 
├── libft/                  # Custom C library 
│   ├── ...                 # (Internal libft source files)
│   └── Makefile            # Libft compilation rules 
├── src/                    # Source code 
│   ├── main.c              # Entry point and main shell loop
│   ├── builtins/           # Internal shell commands (cd, echo, env, exit, etc.) 
│   ├── cleanup/            # Memory management and error handling
│   ├── executor/           # Process creation, pipes, and redirections 
│   ├── expansions/         # Environment variable and quote handling 
│   ├── heredoc/            # Heredoc (<<) input and processing 
│   ├── lexer/              # Tokenization of the input string
│   ├── parser/             # Command table construction from tokens
│   └── signals/            # Signal handling (Ctrl-C, Ctrl-D, Ctrl-\) 
└── test/                   # Directory for internal testing scripts
```

## RESOURCES

### Documentation and tutorials
* __GNU Bash Manual__: For understanding expected shell behaviour.
* __The e Linux Programming Interface:__ For technical details on `fork()`, `execve()`, `pipe()`, and signal handling. 
* __Chapter 5: writing your own shell__ from _Introduction to Systems Programming: a Hands-on Approach (V2015-2-25)_ (© 2014 Gustavo Rodriguez-Rivera and Justin Ennen (systemsprogrammingbook.com)
* __POSIX Standard__: We used [The Open Group Base Specifications](https://pubs.opengroup.org/onlinepubs/9799919799/) to ensure our shell's behavior regarding system calls like `fork`, `execve`, and `waitpid` aligns with industry standards.

### Use of AI
Anyone trying to code has already seen the limitations of AI. Althought this is a widely coded project with plenty of references for the AI to steal and generate correct answers from, at the end of the day AI cannot be trusted with any more responsability than an intern, provided you want to keep a good speed and code consistency along the way. 

In this regard, we have made use AI tools for the following tasks:
* __Task 1:__ Architecture Design: AI assisted in brainstorming the data structures for the lexer and parser nodes (e.g., t_token and t_cmds).  
* __Task 2:__ Debugging: Used to identify potential edge cases in quote masking and environment variable expansion logic.  
* __Task 3:__ Documentation: Assisted in formatting and structuring this README file to meet the subject requirements.  

__Note:__ All AI-generated suggestions were critically reviewed and verified by the development team to ensure full understanding of the logic.

![:)](assets/joguman.png)