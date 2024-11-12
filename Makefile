all:
	@g++ main.cpp -o app -lGL -lglut

.PHONY: run
run:
	@g++ main.cpp -o app -lGL -lglut
	@./app

.PHONY: test
test:
	@echo There is nothing to test in this project

.PHONY: pull
pull:
ifeq ($(shell git rev-parse --is-inside-work-tree 2>/dev/null),true)
	@git reset --hard
	@git clean -fdx
	@git pull --ff-only
else
	@echo "No git repository found in the current directory"
endif

.PHONY: clean
clean:
	@rm -rf app