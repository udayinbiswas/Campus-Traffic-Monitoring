g++ -I/usr/include/python2.6 t2.cpp -o t2 -lpython2.6
g++ -I/usr/include/python2.6 t1.cpp -o t1 -lpython2.6
g++ -I/usr/include/python2.6 -I/opt/libpqxx/include/ -L/opt/libpqxx/lib/ sendSMS.cpp -o sendsms -lpqxx -lpq -lpython2.6
