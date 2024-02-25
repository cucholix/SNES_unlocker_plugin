.PHONY: all clean skyline

NAME 			:= $(shell basename $(CURDIR))
NAME_LOWER		:= $(shell echo $(NAME) | tr A-Z a-z)

BUILD_DIR 		:= build

MAKE_NSO		:= nso.mk

all: skyline

skyline:
	$(MAKE) all -f $(MAKE_NSO) MAKE_NSO=$(MAKE_NSO) BUILD=$(BUILD_DIR) TARGET=$(NAME)
	@mkdir -p 01008D300C50C000/exefs
	@cp main.npdm 01008D300C50C000/exefs/main.npdm
	@cp subsdk9 01008D300C50C000/exefs/subsdk9

clean:
	$(MAKE) clean -f $(MAKE_NSO)
	rm -r -f 01008D300C50C000
