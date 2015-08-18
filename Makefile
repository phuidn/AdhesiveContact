# THE MAKEFILE

# where your source is
SRCDIR=src
# executable name
PROGNAME=adcon
# path for executable, .o and .d files
BUILDPATH = build

CC = mpicc
FLAGS = -lpetsc -lm -std=gnu99 -Wall -pedantic -ggdb
#LIB = -I /opt/local/include/ -L /opt/local/lib
LIB = -I/usr/local/petsc-3.4.4/arch-linux2-gcc-debug/include -I/usr/local/petsc-3.4.4/include -L/usr/local/petsc-3.4.4/arch-linux2-gcc-debug/lib

# list of SCRDIR/ and its subdirectories
VPATH = $(shell find $(SRCDIR)/ -type d -name '*')
# c files in VPATH directories (with path)
SRCS = $(shell find $(SRCDIR)/ -name '*.c')
# replace .c with .o
OBJS_DIR = $(patsubst %.c, %.o, $(SRCS))
# remove path from .o's, add BUILDPATH as a prefix
OBJS = $(addprefix $(BUILDPATH)/, $(notdir $(OBJS_DIR)))

# default build: use the .o files to make the executable, then copy executable to a useful place
$(BUILDPATH)/$(PROGNAME): $(OBJS)
	$(CC) $(FLAGS) $(LIB) $(OBJS) -o $@
	@cp $(BUILDPATH)/$(PROGNAME) ./$(PROGNAME) 

# if there are .d files in BUILDPATH, use them 
-include $(OBJS:.o=.d)

# for each .c file, compile it into a .o file and generate a .d file listing its dependencies
# sed appends BUILDPATH to the .o file in the .d file so make knows what it's referring to
$(BUILDPATH)/%.o: %.c
	$(CC) $(FLAGS) $(LIB) -c $< -o $@
	@$(CC) -MM $(FLAGS) $(LIB) $< > $(@D)/$*.d.tmp
	@sed -e 's/\(.*\):/$(@D)\/\1:/' < $(@D)/$*.d.tmp > $(@D)/$*.d
	@rm $(@D)/$*.d.tmp

clean:
	-@rm $(BUILDPATH)/*.o $(BUILDPATH)/*.d $(BUILDPATH)/$(PROGNAME) 2>/dev/null || true
