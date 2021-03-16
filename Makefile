

OS_PATH = ./os-base
LIB_PATH = ./lib
APP_PATH = ./application-test

PATHS = $(OS_PATH) $(APP_PATH) $(LIB_PATH)


all: OS LIB APP
	@echo done

OS LIB APP:
	@cd $($@_PATH) && $(MAKE)

TO_CLEAN = $(addsuffix _clean, $(PATHS))

clean: $(TO_CLEAN)
	@echo done

%_clean: %
	@cd ./$< && $(MAKE) clean