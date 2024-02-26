rm ./a.out
gcc -g -fsanitize=address ft_unset.c ft_export.c ft_env.c \
../environ/binary_tree_util.c ../environ/binary_tree.c ../environ/environ.c ../environ/binary_tree_mem.c ../environ/env_to_binary_tree.c \
../utils/error_msg.c ../parser/set_mem.c \
main.c ../libft/libftprintf.a

./a.out
