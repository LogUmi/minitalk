NAME = 	minitalk.a
EXE1 =	server.c
EXE2 =	client.c
DIRSR =	srcs/
DIROB =	objs/
DIRLI =	includes/
FILEH = minitalk.h
FILEC = server_0.c \
		server_1.c \
		client_0.c \
		client_1.c \
		minitalk_utils.c
SRCS =	$(addprefix $(DIRSR), $(FILEC))
OBJS =	$(addprefix $(DIROB), $(FILEC:.c=.o))
HDRS =	$(addprefix $(DIRLI), $(FILEH))
LDIR = libft
LIBR = $(LDIR)/libft.a
FLAGS = -Wall -Werror -Wextra
CC = cc
AR = ar -rcs

all:		initdir	$(NAME)		

$(NAME):	$(OBJS)	$(LIBR)
			$(AR) $(NAME) $(OBJS)
			$(CC) $(FLAGS) $(DIRSR)$(EXE1) $(NAME) -o $(EXE1:.c=) -g
			$(CC) $(FLAGS) $(DIRSR)$(EXE2) $(NAME) -o $(EXE2:.c=) -g
			
$(DIROB)%.o:	$(DIRSR)%.c	
				$(CC) $(FLAGS) -c $< -o $@ -I$(DIRLI) -I$(LDIR)

# Création du dossier obj/ si nécessaire
initdir:
			@mkdir -p $(DIROB)
			
$(LIBR):		
			[ -d $(LDIR) ] && $(MAKE) -C $(LDIR) all		
			cp $(LIBR) .
			mv $(notdir $(LIBR)) $(NAME)

clean:		
			rm -rf	$(OBJS) $(EXE1:.c=.o) $(EXE2:.c=.o)
			$(MAKE) -C $(LDIR) clean	

fclean:		clean
			rm -rf $(NAME)	
			rm -rf $(EXE1:.c=)
			rm -rf $(EXE2:.c=)
			$(MAKE) -C $(LDIR) fclean	

re:			fclean all

.PHONY:		all clean fclean re