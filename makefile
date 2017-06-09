CFLAGS  = -std=c++11 \
	  -O3 \
	  -pipe \
	  -ggdb3 -Wstrict-overflow=5 -fstack-protector-all \
          -W -Wall -Wextra \
	  -Wcast-align \
	  -Wcast-qual \
	  -Wconversion \
	  -Wfloat-equal \
	  -Wformat-y2k \
	  -Winit-self \
	  -Winline \
	  -Winvalid-pch \
	  -Wmissing-declarations \
	  -Wmissing-field-initializers \
	  -Wmissing-format-attribute \
	  -Wmissing-include-dirs \
	  -Wmissing-noreturn \
	  -Wnormalized=nfc \
	  -Woverlength-strings \
	  -Wpacked \
	  -Wpadded \
	  -Wpointer-arith \
	  -Wredundant-decls \
	  -Wshadow \
	  -Wsign-compare \
	  -Wstack-protector \
	  -Wundef \
	  -Wunsafe-loop-optimizations \
	  -Wvolatile-register-var \
	  -Wwrite-strings

#------------------------------------------------------------------------------
.PHONY : all clean

#------------------------------------------------------------------------------
all : fortes

fortes : fortes.cpp
	g++ $(CFLAGS) \
	      -Wno-cast-qual \
              -Wno-padded \
              -Wno-undef \
              -o $@ \
              $^ \
	      -l cgraph

#------------------------------------------------------------------------------
clean :
	$(RM) *.o
