CXX = g++
CXXFLAGS = -Wall -Wextra -O3 -std=c++11

SRCDIR = ./src
SRCS   = $(wildcard $(SRCDIR)/*.cpp)
OBJS   = $(subst .cpp,.o, $(SRCS))

all: nw

nw: $(OBJS)
	$(CXX) -o $@ $^

$(SRCDIR)/%.o: %.h %.cpp

clean:
	rm -f $(SRCDIR)/*.o
