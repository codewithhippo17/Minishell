# Minishell

A custom Unix shell implementation in C, mimicking bash/zsh behavior. Supports command parsing, pipelines, redirections, built-in commands, environment variable expansion, signal handling, heredoc, and memory management.

---

## Project Structure

### Entry Point
- **minishell.c**: Main loop, input handling, dispatches commands, manages signals and cleanup.
- **minishell.h**: Central header, includes all modules, defines main structures and function prototypes.

### Directories
- **ast/**: Abstract Syntax Tree (AST) construction and manipulation for parsed commands.
- **builtins/**: Implementation of shell built-in commands (cd, echo, env, exit, export, pwd, unset).
- **checker/**: Syntax and command validation before execution.
- **exec_builtin/**: Execution logic for built-in commands within the shell process.
- **executor/**: External command execution, redirections, and pipeline management.
- **expander/**: Environment variable and parameter expansion in command lines.
- **gb_col/**: Garbage collection and memory management utilities.
- **heredoc/**: Heredoc (<<) support for multi-line input.
- **kill/**: Shell exit and resource cleanup.
- **lexer/**: Lexical analysis (tokenization) of input command lines.
- **libft/**: Custom standard C library functions (string, memory, char, etc).
- **pipex/**: Pipeline and file descriptor management for command pipelines.
- **signals/**: Unix signal handling (SIGINT, SIGQUIT) for shell and child processes.
- **utils/**: Miscellaneous utilities for environment, export, and shell helpers.

---

## Pipeline and Redirect Edge Cases

Minishell matches bash behavior for ambiguous or empty pipeline segments:
- `> file | ls` creates `file` and runs `ls` (rightmost command always executes)
- `| ls` and `> file |` produce syntax errors, matching bash
- Empty or redirect-only segments do not crash or cause ambiguous redirect errors

---

## Main Flow
1. **Input**: Reads user input with `readline()`.
2. **Lexing**: Tokenizes the input string.
3. **Parsing**: Builds an AST for the command structure.
4. **Expansion**: Expands environment variables and parameters.
5. **Execution**: Runs built-in or external commands, manages pipelines and redirections.
6. **Cleanup**: Frees resources and handles memory via garbage collection.

---

## Key Features
- **Built-in commands**: cd, echo, env, exit, export, pwd, unset
- **Pipelines and redirections**: Supports `|`, `>`, `<`, `>>`, `<<` (heredoc)
- **Environment variable expansion**: Handles `$VAR` and special parameters
- **Signal handling**: Properly handles Ctrl+C (SIGINT) and Ctrl+\ (SIGQUIT) in both shell and child processes
- **Memory management**: Custom garbage collector to prevent leaks

---

## How to Read the Codebase
- Start with `minishell.c` for the main loop and input handling.
- Follow the flow: input → lexer → parser/AST → expander → executor/pipex → builtins/external commands.
- Check `signals/` for signal handling logic.
- Look at `gb_col/` for memory management.
- Use `libft/` for custom standard library functions.

---

## Example: Signal Handling and Exit Status
- When running a command like `cat` and pressing Ctrl+C, the shell should terminate `cat` and return to the prompt.
- The exit status (`$?`) after SIGINT should be `130`.

```
minishell$ cat
^C
minishell$ echo $?
130
minishell$
```

If you see no output after `echo $?`, check the shell's status handling in child process termination and variable expansion.

---

## Contributing
- See each directory for more details on specific modules.
- For questions or improvements, open an issue or PR.

