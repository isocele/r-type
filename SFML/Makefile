LIGHT_GREEN = "\033[1;32m"
RESET = "\033[0m"

all: build
	@$(MAKE) -j4 -s -C build

build:
	@cmake -E make_directory build
	@cd build \
	&& conan install .. --build missing -s compiler.libcxx=libstdc++11\
	&& cmake .. -G "Unix Makefiles"

clean:
	@if [ -d build ]; then $(MAKE) -s -C build/ clean; fi

fclean: clean
	@rm -rf build
	@echo -e $(LIGHT_GREEN) \
		 "Removed build directory" \
		 $(RESET)

re: fclean all

.PHONY: all clean fclean re build
