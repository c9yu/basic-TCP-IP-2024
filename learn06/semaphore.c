#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void * read(void * arg); // 사용자 입력을 받는 함수 선언
void * accu(void * arg); // 입력된 값을 합산하는 함수 선언

static sem_t sem_one; // 세마포어 변수 선언
static sem_t sem_two; // 세마포어 변수 선언
static int num; // 공유 변수 선언

int main(int argc, char *argv[])
{
	pthread_t id_t1, id_t2; // 스레드 식별자 선언
	sem_init(&sem_one, 0, 0); // 세마포어 초기화
	sem_init(&sem_two, 0, 1); // 세마포어 초기화

	// 스레드 생성 및 실행
	pthread_create(&id_t1, NULL, read, NULL);
	pthread_create(&id_t2, NULL, accu, NULL);

	// 스레드 종료 대기
	pthread_join(id_t1, NULL);
	pthread_join(id_t2, NULL);

	// 세마포어 파괴
	sem_destroy(&sem_one);
	sem_destroy(&sem_two);
	return 0;
}

// 사용자 입력을 받는 함수 정의
void * read(void * arg)
{
	int i;
	for (i = 0; i < 5; i++)
	{
		fputs("Input num: ", stdout); // 사용자에게 입력 요청

		sem_wait(&sem_two); // 세마포어 대기
		scanf("%d", &num); // 사용자 입력 받기
		sem_post(&sem_one); // 세마포어 신호
	}
	return NULL;
}

// 입력된 값을 합산하는 함수 정의
void * accu(void * arg)
{
	int sum = 0, i;
	for (i = 0; i < 5; i++)
	{
		sem_wait(&sem_one); // 세마포어 대기
		sum += num; // 입력된 값을 합산
		sem_post(&sem_two); // 세마포어 신호
	}
	printf("Result: %d \n", sum); // 합산 결과 출력
	return NULL;
}
