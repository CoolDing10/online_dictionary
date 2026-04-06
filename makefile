all:bin ./bin/client ./bin/server
bin:
	mkdir ./bin
./bin/client:client.c online_dic.c
	gcc -g -Wall -o $@ $^
./bin/server:server.c 
	gcc -g -Wall -o $@ $^ -lsqlite3
.PHONY:clean
clean:
	rm -rf ./bin