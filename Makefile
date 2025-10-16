bank_system : main.o AccountSystems.o Accounts.o Account.o
	g++ main.o AccountSystems.o Accounts.o Account.o -o bank_system

main.o : main.cpp AccountSystems.h Accounts.h Account.h
	g++ -Wall -c main.cpp

AccountSystems.o : AccountSystems.cpp AccountSystems.h Accounts.h Account.h
	g++ -Wall -c AccountSystems.cpp

Accounts.o : Accounts.cpp Accounts.h Account.h
	g++ -Wall -c Accounts.cpp

Account.o : Account.cpp Account.h
	g++ -Wall -c Account.cpp

clean :
	rm -f *.o bank_system
