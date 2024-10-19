NAME = philo
BONUS = philo_bonus
DIR = philo/
BONUS_DIR = philo_bonus/ 

cfiles = philosophers.c
ofiles := $(patsubst %.c, %.o, $(cfiles))
ofiles := $(addprefix $(DIR),$(ofiles))

bcfiles = philosophers_bonus.c
bofiles := $(patsubst %.c, %.o, $(cfiles))
bofiles := $(addprefix $(BONUS_DIR),$(bofiles))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Ofast -pthreads

$(NAME) : $(ofiles)
	$(CC) $(CFLAGS) $(ofiles) -o $(NAME)

$(BONUS) : bonusdir $(bofiles)
	$(CC) $(CFLAGS) $(bofiles) -o $(BONUS)

re : all

all : $(NAME) $(BONUS) clean

clean :
	rm $(ofiles) $(bofiles)

fclean : clean
	rm $(NAME) $(BONUS)
	rmdir $(BONUS_DIR)

bonus : $(BONUS)

bonusdir :
	mkdir -p $(BONUS_DIR)

.PHONY: all clean fclean re bonus bonusdir
