SRCS= ../inner_parser/argument_parser.c ../inner_parser/argument_parser_str_list.c \
../inner_parser/argument_parser_utils.c \
../common_util.c

LIBFT=../libft/libftprintf.a

cd:
	cc -g ft_cd.c $(SRCS) $(LIBFT) -lreadline

echo:
	cc -g ft_echo.c $(SRCS) ../libft/libftprintf.a -lreadline

pwd:
	cc -g ft_pwd.c $(SRCS) ../libft/libftprintf.a -lreadline

exit:
	cc -g ft_exit.c $(SRCS) ../libft/libftprintf.a -lreadline

test:
	cc -g test.c $(SRCS) ../libft/libftprintf.a -lreadline
