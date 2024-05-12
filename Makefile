# ----------------------------
# Makefile Options
# ----------------------------

NAME = agon-graphics
DESCRIPTION = "Test for the Agon Light C Compiler"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

EMULATOR_DIR=/home/james/fab-agon-emulator
EMULATOR_BIN=fab-agon-emulator
EMULATOR_FLAGS=--scale 2000
EMULATOR_SDCARD=~/.agon-sdcard
SD_CARD=/media/james/H1N_SD
# ----------------------------

include $(shell cedev-config --makefile)

.PHONY: emulate dist_sd inst_emu inst_sd

autoexec.txt: all
	echo "cd $(NAME)" > $(BINDIR)/autoexec.txt
	echo "load $(TARGETBIN)" >> $(BINDIR)/autoexec.txt
	echo "run" >> $(BINDIR)/autoexec.txt

inst_emu: $(BINDIR)/$(TARGETBIN)
	mkdir -p $(EMULATOR_SDCARD)/$(NAME)
	cp $(BINDIR)/$(TARGETBIN) $(EMULATOR_SDCARD)/$(NAME)
	cp $(BINDIR)/autoexec.txt $(EMULATOR_SDCARD)

inst_sd: $(BINDIR)/$(TARGETBIN)
	mkdir -p $(SD_CARD)/$(NAME)
	cp $(BINDIR)/$(TARGETBIN) $(SD_CARD)/$(NAME)
	cp $(BINDIR)/autoexec.txt $(SD_CARD)

dist_sd: autoexec.txt inst_sd

emulate: autoexec.txt inst_emu
	cd $(EMULATOR_DIR) && ./$(EMULATOR_BIN) $(EMULATOR_FLAGS)
