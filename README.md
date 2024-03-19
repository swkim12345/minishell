# Minishell

### 42 seoul circle 03

### Description

- Duplicate bash 3.2 version using C language.

- Operate this token.

``` shell
|  #pipe
|| #OR
&& #AND
() #Bracket
$  #Shell environment
*  #Asterisk(Wild Card)
```


- Duplicate builtin funcion 

``` shell
echo
cd
export
env
unset
pwd
exit
```

### How to start

``` shell
# if you use in x86 mac or linux base os
$ make

# if you use arm64 mac or not installed readline

$ brew install libreadline7 #or new version readline
# Add path of readline in Makefile
$ make

```
