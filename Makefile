NAME = Expert_System

SRC = main.cpp Lexer.class.cpp Operator.class.cpp Token.class.cpp \
		TokenFact.class.cpp Parser.class.cpp \
		Instr.class.cpp	Fact.class.cpp TokenMixed.class.cpp \
		ExpertSystem.class.cpp

OBJ = $(addprefix $(O_DIR)/,$(SRC:.cpp=.o))

O_DIR = ./objs

S_DIR = ./srcs

CFLAGS = -Wall -Wextra -Werror -ferror-limit=2 -I includes

CC = clang++

RM = rm -rf

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJ)

$(O_DIR)/%.o: $(S_DIR)/%.cpp
	@mkdir -p $(O_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@$(RM) $(O_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re