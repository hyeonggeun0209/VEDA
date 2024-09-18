CC = gcc
CFLAGS = -Wall

all: server client

server: server.c
	$(CC) $(CFLAGS) -o server server.c

client: client.c
	$(CC) $(CFLAGS) -o client client.c

clean:
	rm -f server client

run_server:
	./server

run_client:
	@if [ -z "$(filter-out $@,$(MAKECMDGOALS))" ]; then \
		echo "IP 주소를 지정해야 합니다. 'make run_client <서버_IP>' 형식으로 실행하세요."; \
		echo "예: make run_client 127.0.0.1"; \
	else \
		./client $(filter-out $@,$(MAKECMDGOALS)); \
	fi

%:
	@:

.PHONY: all clean run_server run_client