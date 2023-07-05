SERVER 	= db-server

CLIENT 	= db-cli

CC 	= gcc

CFLAGS 	= -Wall -Werror -Wextra

CFLAGS 	+= -I./include

CFLAGS 	+= -fsanitize=address -g3

LDFLAGS	= -fsanitize=address

SRCDIR	= src

SERVDIR = server

CLIDIR 	= cli

SOCKDIR = socket

SERVSRC = main.c \
	  hash.c \
	  hashtable.c \
	  init.c

SOCKSRC = recieve.c

CLISRC 	= main.c

SERV	= $(addprefix $(SRCDIR)/,$(addprefix $(SERVDIR)/,$(SERVSRC))) \
	  $(addprefix $(SRCDIR)/,$(addprefix $(SOCKDIR)/,$(SOCKSRC))) \

CLI	= $(addprefix $(SRCDIR)/,$(addprefix $(CLIDIR)/,$(CLISRC)))

SRVOBJ	= $(SERV:.c=.o)

CLIOBJ	= $(CLI:.c=.o)

all: $(SERVER) $(CLIENT)

$(SERVER): $(SRVOBJ)
	$(CC) $(CFLAGS) $(SRVOBJ) $(LDFLAGS) -o $(SERVER)

$(CLIENT): $(CLIOBJ)
	$(CC) $(CFLAGS) $(CLIOBJ) $(LDFLAGS) -o $(CLIENT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(SRVOBJ) $(CLIOBJ)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
