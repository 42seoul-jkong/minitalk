# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/07 02:59:42 by jkong             #+#    #+#              #
#    Updated: 2022/04/07 02:59:42 by jkong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES: .c .o .h
.PHONY: all clean fclean re bonus

CC = cc
RM = rm -f

SRCS_BASE = minitalk.c signal.c\
			bit_buf.c bit_buf_ext.c \
			safe_mem.c safe_io.c\
			libft.c libft_try_atoi.c
OBJECTS_DIR = objs/
HEADER = minitalk.h

TARGET_SERVER = server
SRCS_SERVER = $(SRCS_BASE) server_app.c
OBJS_SERVER = $(addprefix $(OBJECTS_DIR), $(SRCS_SERVER:.c=.o))

TARGET_CLIENT = client
SRCS_CLIENT = $(SRCS_BASE) client_app.c
OBJS_CLIENT = $(addprefix $(OBJECTS_DIR), $(SRCS_CLIENT:.c=.o))

TARGETS = $(TARGET_SERVER) $(TARGET_CLIENT)

C_SANITIZER_FLAGS = address undefined
CFLAGS += $(addprefix -fsanitize=, $(C_SANITIZER_FLAGS))
LDFLAGS += $(addprefix -fsanitize=, $(C_SANITIZER_FLAGS))

C_WARNING_FLAGS = all extra error
CFLAGS += $(addprefix -W, $(C_WARNING_FLAGS))

C_DEBUG_FLAGS = g3
CFLAGS += $(addprefix -, $(C_DEBUG_FLAGS))

all: $(TARGETS)
clean:				;	$(RM) -r $(OBJECTS_DIR)
fclean: clean		;	$(RM) $(TARGETS)
re: fclean all
bonus: all

$(OBJECTS_DIR):
	mkdir $(OBJECTS_DIR)

$(OBJS_SERVER) $(OBJS_CLIENT): $(HEADER) | $(OBJECTS_DIR)

$(addprefix $(OBJECTS_DIR), %.o): %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET_SERVER): $(OBJS_SERVER)
	$(CC) -o $@ $(LDFLAGS) $^

$(TARGET_CLIENT): $(OBJS_CLIENT)
	$(CC) -o $@ $(LDFLAGS) $^
