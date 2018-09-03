
# gcc compiler
MAKE = make
CC  = gcc
CPP = g++
LD  = ld

# target
TARGET_BIN = msg-server

# flagsst 
CFLAGS += -Wall -g -fPIC -std=c++11
CPPFLAGS += $(CFLAGS)
LDFLAGS += -lpthread -lcoevent -lpthread -lcolib

# source files
C_SRCS = $(wildcard ./*.c)
CPP_SRCS = $(wildcard ./*.cpp)
ASM_SRCS = $(wildcard ./*.S)

C_OBJS = $(C_SRCS:.c=.c.o)
CPP_OBJS = $(CPP_SRCS:.cpp=.cpp.o)
ASM_OBJS = $(ASM_SRCS:.S=.S.o)

NULL ?=#
ifneq ($(strip $(CPP_OBJS)), $(NULL))
FINAL_CC = $(CPP)
else
FINAL_CC = $(CC)
CPPFLAGS = $(CFLAGS)
endif

export FINAL_CC
export NULL
export CPPFLAGS
export CFLAGS
export CC
export CPP
export LD

# default target
.PHONY:all
all: $(TARGET_BIN)
	@echo "	<< $(TARGET_BIN) made >>"

# automatic compiler
-include $(C_OBJS:.o=.d)
-include $(CPP_OBJS:.o=.d)

%.cpp.o: %.cpp
	$(CPP) -c $(CPPFLAGS) $*.cpp -o $*.cpp.o
	@$(CPP) -MM $(CPPFLAGS) $*.cpp > $*.cpp.d
	@mv -f $*.cpp.d $*.cpp.d.tmp
	@sed -e 's|.*:|$*.cpp.o:|' < $*.cpp.d.tmp > $*.cpp.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.cpp.d.tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $*.cpp.d
	@rm -f $*.cpp.d.tmp

%.c.o: %.c
	$(CC) -c $(CFLAGS) $*.c -o $*.c.o
	@$(CC) -MM $(CFLAGS) $*.c > $*.c.d
	@mv -f $*.c.d $*.c.d.tmp
	@sed -e 's|.*:|$*.c.o:|' < $*.c.d.tmp > $*.c.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.c.d.tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $*.c.d
	@rm -f $*.c.d.tmp

%.S.o: %.S
	$(CC) -c $*.S $*.S.o

# server
$(TARGET_BIN): $(C_OBJS) $(CPP_OBJS)
	@echo ""
	@echo $@ -- $^
	@echo "$(LD) -r -o $@.o *.o"
	@$(LD) -r -o $@.o $(C_OBJS) $(CPP_OBJS)
	$(FINAL_CC) $@.o -o $@ $(LDFLAGS)
	chmod +x $@

.PHONY: clean
clean:
#	@rm -f $(C_OBJS) $(CPP_OBJS) $(PROG_NAME) clist.txt cpplist.txt *.d *.d.* *.o
	-@find -name '*.o' | xargs -I [] rm [] >> /dev/null
	-@find -name '*.d' | xargs -I [] rm [] >> /dev/null
#	-@find -name '*.so' | xargs -I [] rm [] >> /dev/null
	-@rm -f $(TARGET_BIN)
	@echo "	<< $(TARGET_BIN) cleaned >>"

.PHONY: test
test:
	@echo 'test'
	@echo $(CPP_OBJS) $(C_OBJS)

