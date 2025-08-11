# Minishell Ambiguous Redirect Test Results

This file compares the output of your Minishell against expected bash behavior for ambiguous and edge redirect cases.

| Command           | Expected Bash Output                | Minishell Output                |
|-------------------|-------------------------------------|---------------------------------|
| > file            | OK (creates file)                   | OK (creates file)               |
| > file | ls       | OK (creates file, runs ls)          | OK (creates file, runs ls)      |
| > file | cmd      | Syntax error, no file, no crash     | Syntax error, no crash          |
| cmd > file        | OK (output redirected to file)      | OK (output redirected to file)  |
| | ls              | Syntax error                        | Syntax error                    |
| > file |          | Syntax error                        | Syntax error                    |
| | cmd             | Syntax error, no crash              | Syntax error, no crash          |
| echo > $a         | OK (writes to file)                 | [output observed]               |
| echo > $e         | ambiguous redirect                  | [output observed]               |
| echo > $f         | ambiguous redirect                  | [output observed]               |
| echo > $j         | ambiguous redirect                  | [output observed]               |
| echo > $k         | ambiguous redirect                  | [output observed]               |
| echo > $l         | ambiguous redirect                  | [output observed]               |

<!-- Add more cases as needed -->
