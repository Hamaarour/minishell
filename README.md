# minishell
<p align="center">
<img src ="https://github.com/Hamaarour/minishell/blob/Parsing/team.jpg">
</p>
<p align="center">
<img src ="">
</p>

This project is about creating a simple shell

MiniShell will introduce you to the world of shells, which provide a convenient text interface to interact with your system. Shells might seem very easy to understand but have very specific and defined behaviour in almost every single case, most of which will need to be handled properly

## The Challenge
This was probably the biggest project I've done so far, as well as the first one I did as a group.  The goal was to create a mini version of bash, I say mini but it was still a huge project.  We had to learn how bash takes arguments, parses them, and executes them. We had to incorporate the following features:
- Display a promt while waiting for a new commmand.
- Have a working history.
- Find and launch executables (using the `PATH` variable or an absolute path).
- Handle `'` (single) and `"` (double) **quotes** like in bash.
- Implement **redirections** such as:
  - `<` redirect input.
  - `>` redirect output.
  - `<<` heredoc (doesn't affect history).
  - `>>` redirect output in append mode.
- Implement `|` (**pipes**).
- Handle **environment variables**.
- Handle `$?`.
- `ctrl-C`, `ctrl-D`, and `ctrl-\` should behave like in bash.
- Recreate the following **builtins**:
  - `echo` with option `-n`.
  - `cd` with only a relative or absolute path.
  - `pwd` (no flags).
  - `export` (no flags).
  - `unset` (no flags).
  - `env` (no flags or arguments).
  - `exit` (no flags).

We didn't have to implement && and ||, or wildcards, as well as any special symbols that weren't specifically asked for.  We were also told that when in doubt, take bash as a reference.  This sometimes led to discussions on wether or not we had to implement something, the result of which was usually
