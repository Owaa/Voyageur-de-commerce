CC = g++
FLAGS = -lGL -lGLU -lglut -g

NAME = HantTravel
SRC = voyage.cpp obj.cpp main.cpp fourmi.cpp
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $@

%.o: %.cpp
	$(CC) $(FLAGS) -cpp $<

clean:
	@rm $(NAME) *~

