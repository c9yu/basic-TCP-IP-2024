#include <stdio.h>
#include <pthread.h>

// 스레드가 실행할 함수 선언
void* thread_main(void *arg);

int main(int argc, char *argv[]) 
{
	pthread_t t_id;          // 스레드 식별자
	int thread_param = 5;    // 스레드 매개변수

	// 스레드 생성 및 실행
	if (pthread_create(&t_id, NULL, thread_main, (void*)&thread_param) != 0)
	{
		puts("pthread_create() error");  // 스레드 생성 실패 시 오류 메시지 출력
		return -1;  // 프로그램 종료
	}; 
	
	sleep(10);  // 메인 스레드 대기 (10초)
	puts("end of main");  // 메인 함수 종료 메시지 출력
	return 0;
}

// 스레드가 실행할 함수 정의
void* thread_main(void *arg) 
{
	int i;
	int cnt = *((int*)arg);  // 스레드 매개변수 가져오기

	for (i = 0; i < cnt; i++)
	{
		sleep(1);  // 1초 대기
		puts("running thread");  // 스레드 실행 중 메시지 출력
	}
	return NULL;  // 스레드 종료
}
