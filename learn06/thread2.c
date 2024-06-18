#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// 스레드가 실행할 함수 선언
void* thread_main(void *arg);

int main(int argc, char *argv[]) 
{
	pthread_t t_id;          // 스레드 식별자
	int thread_param = 5;    // 스레드 매개변수
	void *thr_ret;           // 스레드 반환값을 저장할 포인터
	
	// 스레드 생성 및 실행
	if (pthread_create(&t_id, NULL, thread_main, (void*)&thread_param) != 0)
	{
		puts("pthread_create() error");  // 스레드 생성 실패 시 오류 메시지 출력
		return -1;  // 프로그램 종료
	}; 	

	// 스레드 종료 대기 및 반환값 수신
	if (pthread_join(t_id, &thr_ret) != 0)
	{
		puts("pthread_join() error");  // 스레드 조인 실패 시 오류 메시지 출력
		return -1;  // 프로그램 종료
	};

	// 스레드가 반환한 메시지 출력
	printf("Thread return message: %s \n", (char*)thr_ret);
	free(thr_ret);  // 동적 할당된 메모리 해제
	return 0;
}

// 스레드가 실행할 함수 정의
void* thread_main(void *arg) 
{
	int i;
	int cnt = *((int*)arg);  // 스레드 매개변수 가져오기
	char *msg = (char *)malloc(sizeof(char) * 50);  // 동적 메모리 할당
	strcpy(msg, "Hello, I'am thread~ \n");  // 메시지 저장

	for (i = 0; i < cnt; i++)
	{
		sleep(1);  // 1초 대기
		puts("running thread");  // 스레드 실행 중 메시지 출력
	}
	return (void*)msg;  // 스레드 종료 시 메시지 반환
}
