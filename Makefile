make:
	clang -I./inc/json -O1 json/*.c -c
	clang++ -I./inc/json -I./inc -std=c++14 -O1 main.cpp -c 
	clang++ *.o -o epoll_sim -lpthread 

clean:
	rm *.o epoll_sim 
	touch ___client_events ___device_updates
	rm ___client_events ___device_updates
