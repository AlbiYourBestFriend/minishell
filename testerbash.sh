#!/bin/bash

printf 'echo hi'|bash
printf 'echo hi\n'|bash
printf 'cat<<1\nhi'|bash ; echo $?
printf 'cat<<1\nhi\n'|bash ; echo $?
printf 'cat<<1\nhi\n1'|bash
printf 'cat<<1\necho hi\n1'|bash|bash

printf ''|bash
printf 'exit'|bash ; echo $?
printf 'echo hi&&exit'|bash ; echo $?
printf 'false||false&&exit'|bash ; echo $?
printf 'false||false'|bash ; echo $?
printf '|'|bash ; echo $?

printf '$empty'|bash ; echo $?
printf ' '|bash ; echo $?
printf '$empty '|bash ; echo $?
printf ' $empty '|bash ; echo $?
printf '$empty$twice'|bash ; echo $?
printf '$empty $twice'|bash ; echo $?
printf '"'|bash ; echo $?
printf '$'|bash ; echo $?
printf 'echo $'|bash ; echo $?
printf 'echo $empty'|bash ; echo $?
printf 'echo $-'|bash ; echo $?
printf 'echo $0'|bash ; echo $?
printf 'echo $a'|bash ; echo $?
printf 'echo $""'|bash ; echo $?
printf '$$'|bash ; echo $?
printf '..'|bash ; echo $?