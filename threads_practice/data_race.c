#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

//Colocar codigo em assembly: cc -S <file>.c

//Data races
int mails = 0;
void* routine()
{
	for (int i = 0; i < 1000000; i++)
		mails++;
	//read mails 
	//increment 
	//write mails
}

int main(int ac, char **av)
{
	srand(time(NULL));
	pthread_t t1, t2;
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return 1;
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return 2;
	if (pthread_join(t1, NULL) != 0)
		return 3;
	if (pthread_join(t2, NULL) != 0)
		return 4;
	printf("Numbers of mails: %d\n", mails);
	return 0;
}

	//O output é: "Numbers of mails: 998925".
	//----------------------------------------
	//-  thread1  -   thread 2   -   Action
	//----------------------------------------
	//            -              -
	//    29 (1º) -              -    READ
	//            -              -
	//----------------------------------------
	//            -              -
	//            -     29 (2º)  -    READ
	//            -              -
	//----------------------------------------
	//            -              -
	//    29 (3º) -              -  INCREMENT
	//            -              -
	//----------------------------------------
	//            -              -
	//    30 (4º) -              -    WRITE
	//            -              -
	//----------------------------------------
	//            -              -
	//    30 (5º) -              -    READ
	//            -              -
	//----------------------------------------
	//            -              -
	//    30 (6º) -              -  INCREMENT
	//            -              -
	//----------------------------------------
	//            -              -
	//    31 (7º) -              -    WRITE
	//            -              -
	//----------------------------------------
	//            -              -
	//            -     29 (8º)  -  INCREMENT
	//            -              -
	//----------------------------------------
	//            -              -
	//            -     30 (9º)  -    WRITE
	//            -              -
	//----------------------------------------

	//Deste modo, fomos de 31 para 30, perdendo assim
	// um dos incrementos