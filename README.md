To complile the project: gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c

Check memory leaks: valgrind --leak-check=full --show-leak-kinds=all ./a.out
