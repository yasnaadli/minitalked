# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/13 17:36:40 by yamohamm          #+#    #+#              #
#    Updated: 2025/02/13 18:10:03 by yamohamm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f 

SERVER = server 
CLIENT = client 

SRC_SERVER = server.c ultis.c
SRC_CLIENT = client.c ultis.c

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

all: $(SERVER) $(CLIENT)

$(SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(SERVER)

$(CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(CLIENT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_SERVER) $(OBJ_CLIENT)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)
	@echo "void got silent."

re: fclean all

.PHONY: all clean fclean re