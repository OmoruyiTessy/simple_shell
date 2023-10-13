# Simple Shell Project
This repository hosts a collaborative project on a simple shell, developed by Tessy Ezeali and Abdulkabir Abdulwasiu. The project is scheduled for submission on October 19th, 2023.

### Project Overview
The goal of the simple shell project is to develop a fundamental command-line interface that can both read and execute user input. For developers interested in operating systems and system-level programming, this shell offers a good starting point for understanding how shells function. The shell is both an interactive command language and a scripting language and is used by the operating system to control the execution of the system using shell scripts.

### Project Features
- **User Input Interpretation:** The shell interprets user input and identifies command keywords and arguments.
- **Command Execution:** It executes the recognized commands, facilitating interaction with the underlying operating system.
- **Collaborative Development:** Tessy Ezeali and Abdulkabir Abdulwasiu collaborate on this project, bringing together diverse skills and ideas for efficient development.

## Project Timeline
- **Start Date:** October 4th, 2023
- **Submission Date:** October 19th, 2023

## Contributors
**Tessy Ezeali**
- **GitHub:** [github.com/OmuruyiTessy](github.com/OmuruyiTessy)

**Abdulkabir Abdulwasiu**
- **GitHub:** [github.com/abdulkabirmusty](github.com/abdulkabirmusty)

## Project Guidelines
- Allowed editors: vi, vim, emacs
- All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
- All your files should end with a new line
- A README.md file, at the root of the folder of the project is mandatory
- Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
- Your shell should not have any memory leaks
- No more than 5 functions per file
- All your header files should be include guarded
- Use system calls only when you need to (why?)
- Write a README with the description of your project
- You should have an AUTHORS file at the root of your repository, listing all individuals having contributed content to the repository. Format, see Docker

## Testing
The shell should work like this in interactive mode:

```
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```

But also in non-interactive mode:
```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```
