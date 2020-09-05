CXX=gcc

SRCDIR=.
OBJDIR=.

_INCDIRS=../include

INCDIRS=$(addprefix -I,$(_INCDIRS))

_LIBDIRS=../lib

LIBDIRS=$(addprefix -L,$(_LIBDIRS))

_LIBS=smpl
LIBS=$(addprefix -l,$(_LIBS))

CXXFLAGS=-O3 -Wall $(INCDIRS)

_COMMA=,
_RPATHS=$(addprefix -Wl$(_COMMA)-rpath$(_COMMA),$(_LIBDIRS))
LDFLAGS=-O3 $(INCDIRS) $(LIBDIRS) $(_RPATHS) $(LIBS)

_SRCFILES=parse_string.c \
					dynamic_string.c

SRCS=$(addprefix $(SRCDIR)/,$(_SRCFILES))

_OBJFILES=$(_SRCFILES:%.c=%.o)
OBJS=$(addprefix $(OBJDIR)/,$(_OBJFILES))

EXES=$(_SRCFILES:%.c=%.exe)

all: $(EXES)

%.exe : $(OBJDIR)/%.o
	$(CXX) $< -o $@ $(LDFLAGS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CXX) $< -c -o $@ $(CXXFLAGS)

.SECONDARY: $(OBJS)
.PHONY: clean

clean:
	rm $(OBJDIR)/*.o
	rm *.exe
