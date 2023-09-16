#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

// É possivel ter multiplas threads num unico processo
// Os processos têm as suas variaveis individuais, no entanto,
// no caso das threads elas partilham todas as variáveis desse processo

// Como retornar o valor de uma thread
void *roll_dice()
{
	int value = (rand() % 6) + 1;
	int* result = malloc(sizeof(int));
	*result = value;
	printf("%d\n", value);
	printf("[thread pointer] %p\n", result);
	return ((void *) result);
}

//Isto nao funciona porque a variavel value é local
// void *roll_dice_wrong()
// {
// 	int value = (rand() % 6) + 1;
// 	printf("%d\n", value);
// 	return ((void *) &value);
// }

int main(int ac, char **av)
{
	int *final;
	srand(time(NULL));
	pthread_t th;
	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
		return 1;
	if (pthread_join(th, (void **)&final) != 0)
		return 2;
	printf("[pointer main] %p\n", final);
	printf("Result: %d\n", *final);
	free(final);
	return 0;
}

