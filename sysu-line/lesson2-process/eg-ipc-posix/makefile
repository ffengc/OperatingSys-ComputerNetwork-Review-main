all:producer consumer

producer: producer.cc
	g++ -o $@ $^ -std=c++11
consumer: consumer.cc
	g++ -o $@ $^ -std=c++11

.PHONY:clean
clean:
	rm -f producer consumer