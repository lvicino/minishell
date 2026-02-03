# minishell

A custom shell implementation that mimics the behavior of the standard Bash (Bourne Again SHell). This project involves parsing commands, managing environment variables, handling signals, and executing executables with pipe and redirection support.

## Overview

`minishell` is a command-line interpreter that reads commands from the standard input or a file and executes them. It serves as a study in process creation, file descriptor management, and the complexities of parsing user input.

## Features

This shell supports the following features:

* **Command Execution:** Search and launch executables based on the `PATH` environment variable or using relative/absolute paths.
* **Prompt:** Displays a prompt when waiting for a new command.
* **History:** Maintains a working command history.
* **Quotes:** Handles single quotes (`'`) and double quotes (`"`), managing meta-characters like `$` inside them appropriately.
* **Redirections:**
    * `<`: Redirect input.
    * `>`: Redirect output.
    * `<<`: Heredoc (read input until a delimiter line).
    * `>>`: Redirect output in append mode.
* **Pipes:** Connects commands via pipes (`|`), where the output of each command in the pipeline is connected via a pipe to the input of the next command.
* **Environment Variables:** Expands variables (e.g., `$USER`, `$HOME`) and handles `$?` (exit status of the most recently executed foreground pipeline).
* **Signals:**
    * `Ctrl-C`: Displays a new prompt on a new line.
    * `Ctrl-D`: Exits the shell.
    * `Ctrl-\`: Does nothing (interactive mode).
* **Built-in Commands:**
    * `echo` (with option `-n`)
    * `cd` (with relative or absolute paths)
    * `pwd` (print working directory)
    * `export` (export variables to environment)
    * `unset` (remove variables from environment)
    * `env` (print environment variables)
    * `exit` (exit the shell)
