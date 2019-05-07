default: kv server

KV_FILES = $(filter-out server.cpp, $(wildcard *.cpp))
kv: ${KV_FILES}
				clang++ -std=c++11 -stdlib=libc++ -Wc++11-extensions ${KV_FILES} -o kv

SERVER_FILES = $(filter-out main.cpp, $(wildcard *.cpp))
server: ${SERVER_FILES}
				clang++ -std=c++11 -stdlib=libc++ -Wc++11-extensions ${SERVER_FILES} -o server

clean:
				rm kv server

.PHONY:clean
