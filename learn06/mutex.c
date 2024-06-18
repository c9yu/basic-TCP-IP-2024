#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREAD 100 // 생성할 스레드의 수

void * thread_inc(void * arg); // 증가 스레드 함수 선언
void * thread_des(void * arg); // 감소 스레드 함수 선언

long long num = 0; // 공유 변수 선언
pthread_mutex_t mutex; // 뮤텍스 변수 선언

int main(int argc, char *argv[]) 
{
	pthread_t thread_id[NUM_THREAD]; // 스레드 식별자 배열
	int i;
	
	pthread_mutex_init(&mutex, NULL); // 뮤텍스 초기화

	for (i = 0; i < NUM_THREAD; i++)
	{
		if (i % 2) // 홀수 인덱스인 경우
			pthread_create(&(thread_id[i]), NULL, thread_inc, NULL); // 증가 스레드 생성
		else       // 짝수 인덱스인 경우
			pthread_create(&(thread_id[i]), NULL, thread_des, NULL); // 감소 스레드 생성
	}	

	for (i = 0; i < NUM_THREAD; i++)
		pthread_join(thread_id[i], NULL); // 모든 스레드 종료 대기

	printf("result: %lld \n", num); // 최종 결과 출력
	pthread_mutex_destroy(&mutex); // 뮤텍스 파괴
	return 0;
}

// 증가 스레드 함수 정의
void * thread_inc(void * arg) 
{
	int i;
	pthread_mutex_lock(&mutex); // 뮤텍스 잠금
	for (i = 0; i < 50000000; i++) // 5000만 번 반복
		num += 1; // 공유 변수 증가
	pthread_mutex_unlock(&mutex); // 뮤텍스 잠금 해제
	return NULL;
}

// 감소 스레드 함수 정의
void * thread_des(void * arg)
{
	int i;
	for (i = 0; i < 50000000; i++) // 5000만 번 반복
	{
		pthread_mutex_lock(&mutex); // 뮤텍스 잠금
		num -= 1; // 공유 변수 감소
		pthread_mutex_unlock(&mutex); // 뮤텍스 잠금 해제
	}
	return NULL;
}

/*
컴파일 및 실행 방법:
$ gcc mutex.c -D_REENTRANT -o mutex -lpthread
$ ./mutex
result: 0
*/

