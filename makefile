SHELL := pwsh -NoProfile
CXX = g++
TARGET = intrusion

OBJDIR := obj/
DEPDIR := $(OBJDIR)deps/

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=$(OBJDIR)%.o)
DEPS := $(SRCS:%.cpp=$(DEPDIR)%.d)

CFLAGS := -Wall -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

$(TARGET) : $(OBJS)
	$(CXX)  $^ -o $@ $(CFLAGS)

$(OBJDIR)%.o : %.cpp $(DEPDIR)%.d | $(DEPDIR)
	$(CXX) -MMD -MT $@ -MP -MF $(DEPDIR)$*.d -o $@ -c $<

$(DEPS):

clean:
	del obj\*.o
	del obj\deps\*.d
	del *.exe

include $(wildcard $(DEPS))