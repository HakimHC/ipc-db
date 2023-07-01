SERVER 	= db-server

CLIENT 	= db-cli

CC 	= gcc

CFLAGS 	= -Wall -Werror -Wextra

CFLAGS 	+= -I./include

CFLAGS 	+= -I./libft/inc

SRCDIR	= src

SERVDIR = server

CLIDIR = cli

SERVSRC = main.c \
	  hash.c

CLISRC 	= main.c

SERV	= $(addprefix $(SRCDIR)/,$(addprefix $(SERVDIR)/,$(SERVSRC)))

CLI	= $(addprefix $(SRCDIR)/,$(addprefix $(CLIDIR)/,$(CLISRC)))

SRVOBJ	= $(SERV:.c=.o)

CLIOBJ	= $(CLI:.c=.o)

all: $(SERVER) $(CLIENT)

$(SERVER): $(SRVOBJ)
	$(CC) $(CFLAGS) $(SRVOBJ) $(LDFLAGS) -o $(SERVER)

$(CLIENT): $(CLIOBJ)
	$(CC) $(CFLAGS) $(CLIOBJ) $(LDFLAGS) -o $(CLIENT)

%.o: %.c
	@make bonus -sC libft 2>&1 >/dev/null
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(SRVOBJ) $(CLIOBJ)
	@make fclean -sC libft 2>&1 >/dev/null

fclean: clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
