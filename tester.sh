#!/bin/bash

printf 'echo hi'|./minishell
printf 'echo hi\n'|./minishell
printf 'cat<<1\nhi'|./minishell ; echo $?
printf 'cat<<1\nhi\n'|./minishell ; echo $?
printf 'cat<<1\nhi\n1'|./minishell
printf 'cat<<1\necho hi\n1'|./minishell|./minishell

printf ''|./minishell
printf 'exit'|./minishell ; echo $?
printf 'echo hi&&exit'|./minishell ; echo $?
printf 'false||false&&exit'|./minishell ; echo $?
printf 'false||false'|./minishell ; echo $?
printf '|'|./minishell ; echo $?

printf '$empty'|./minishell ; echo $?
printf ' '|./minishell ; echo $?
printf '$empty '|./minishell ; echo $?
printf ' $empty '|./minishell ; echo $?
printf '$empty$twice'|./minishell ; echo $?
printf '$empty $twice'|./minishell ; echo $?
printf '"'|./minishell ; echo $?
printf '$'|./minishell ; echo $?
printf 'echo $'|./minishell ; echo $?
printf 'echo $empty'|./minishell ; echo $?
printf 'echo $-'|./minishell ; echo $?
printf 'echo $0'|./minishell ; echo $?
printf 'echo $a'|./minishell ; echo $?
printf 'echo $""'|./minishell ; echo $?
printf '$$'|./minishell ; echo $?
printf '..'|./minishell ; echo $?
