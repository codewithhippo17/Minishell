# Minishell

A compact, modular, POSIX-like shell implemented in **C**, featuring tokenization, parsing, expansion, execution, builtins, and inter-process communication (pipes/redirections), with support for heredoc and signal handling.

---

## Features

- **Modular codebase**: lexer, parser/AST, expander, executor, builtins, heredoc, signals, pipex, etc.  
- **GNU Readline integration**: interactive input, history, and line-editing.  
- **Full pipeline support**: multi-process pipelines handled by executor/pipex.  
- **Redirections & heredoc**: robust support for input/output redirection.  
- **Built-ins**: cd, echo, pwd, export, unset, env, exit, etc.  
- **Reusable helpers**: bundled `libft` for utilities and reduced dependencies.
- **Build automation**: Makefile with standard targets.
- **Active development**: frequent commits and improvements.

---

## Requirements

- Unix-like environment (Linux / macOS)
- C compiler (gcc / clang)
- GNU Readline development headers/libraries installed (for readline/history)
- Make

On Debian/Ubuntu you can install the readline development package with:
```sh
sudo apt-get install libreadline-dev
```

---

## Build

From the repository root:

```sh
make
```

This will compile the project using the provided Makefile. Typical targets in this Makefile include building the executable (`minishell`) and cleaning object files (`make clean`, `make fclean`), though consult the Makefile for exact targets and behaviors.

---

## Run

Start the shell:

```sh
./minishell
```

Once started, you can execute standard system commands, use pipelines and redirections, and run built-in commands.

Example usage:

- Run a single command
  ```sh
  ls -la /tmp
  ```

- Pipelines
  ```sh
  cat file.txt | grep hello | wc -l
  ```

- Redirection
  ```sh
  echo "hello" > out.txt
  wc -c < out.txt
  ```

- Heredoc (example)
```sh
  cat << EOF
  line 1
  line 2
  EOF
```

**Builtins**
- `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`

(Exact builtin behavior is implemented in the `builtins/` and `exec_builtin/` directories. See those files for specific semantics and edge cases.)

---

## Testing & Debugging

- Use the shell interactively to test common flows: pipelines, redirections, heredoc, environment variable expansion, and builtin commands.
- To debug, compile with debugging symbols (edit the Makefile or add `CFLAGS=-g`) and run under gdb or use valgrind to check for memory issues:
```sh
make CFLAGS=-g
gdb ./minishell
valgrind --leak-check=full ./minishell
  ```
