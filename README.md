# minishell![Minishell - Architecture (big picture) - Big picture - REPL loop@2x](https://user-images.githubusercontent.com/94463724/175309936-7f562987-e6d5-4eaa-b7d4-05131286ccfc.png)

![Minishell - Architecture (big picture) - Zoom in - READ state@2x](https://user-images.githubusercontent.com/94463724/175310045-f541001d-efe7-4cf2-a97b-86642f368e37.png)

in general the commands must run within forks, even the builtins (otherwise your program will end because of `execve`). Watch out for corner cases though!
- first part of execution must be handling redirects (checking files and opening them if need be)
- secondly, you must reckon whether each cmd has an absolute path, otherwise if it‘s found in `$PATH`, or whether it’s a builtin

![Minishell - Architecture (big picture) - Zoom in - EVALUATE state@2x](https://user-images.githubusercontent.com/94463724/175310141-ea96698c-104e-4273-b1ac-f762885807aa.png)

Output might be printed anywhere really (STD_OUT or redirected to a file), so there’s no singular function to print the output as it may vary case by case.

Pay special attention to redirects, as they are captured in the command table step, and must be implemented in the Executor, inside each fork for each command separately.

Error messages must always be printed out in the terminal (STD_ERR), as this project does not require the implementation of the `&` token, thus making error redirection impossible as per Bash’s standards.

You should write your own error messages in case of syntax error / other errors.

Don’t forget to also set the variable `$?` to the return code of the last round of executions! Test abundantly with bash, you must replicate it’s behaviour!


Useful links : 

Shell command language: https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html

Bash reference manual: https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html

Youtube playlist unix processes in C: https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY

Minishell architecture : https://whimsical.com/minishell-architecture-big-picture-7b9N8PL3qHrddbs977mQ2J
