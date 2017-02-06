APPNAME=game

PREFIX=/usr/local/snes-sdk
OPTIMIZE=1

CFLAGS=-Wall
ifeq ($(OPTIMIZE),1)
CFLAGS += -O
endif

BINDIR=$(PREFIX)/bin
AS=$(BINDIR)/wla-65816
LD=$(BINDIR)/wlalink
CC=$(BINDIR)/816-tcc
EMU=zsnes

LIBDIR=$(PREFIX)/lib

ASMOBJ = data.obj
COBJ = $(APPNAME).obj snes.obj util.obj map.obj col.obj obj.obj spr.obj com.obj objs.obj bull.obj exp.obj pal.obj

all: $(APPNAME).smc
	$(EMU) $(APPNAME).smc || xset r on

$(APPNAME).smc: $(ASMOBJ) $(COBJ)
	$(LD) -dvSo $(ASMOBJ) $(COBJ) $(APPNAME).smc

%.s: %.c
	$(CC) $(CFLAGS) -I. -o $@ -c $<

%.obj: %.s
	$(AS) -io $< $@
%.obj: %.asm
	$(AS) -io $< $@

clean:
	rm -f $(APPNAME).smc $(APPNAME).sym $(ASMOBJ) $(COBJ) *.s
