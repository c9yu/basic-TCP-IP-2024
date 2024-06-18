#include <stdio.h>
#include <pthread.h>

void * thread_summation(void * arg); // 스레드가 실행할 함수 선언

int sum = 0; // 합계 값을 저장할 전역 변수

int main(int argc, char *argv[])
{
	pthread_t id_t1, id_t2; // 스레드 식별자
	int range1[] = {1, 5};  // 첫 번째 스레드의 합산 범위
	int range2[] = {6, 10}; // 두 번째 스레드의 합산 범위
	
	// 첫 번째 스레드 생성 및 실행
	pthread_create(&id_t1, NULL, thread_summation, (void *)range1);
	// 두 번째 스레드 생성 및 실행
	pthread_create(&id_t2, NULL, thread_summation, (void *)range2);

	// 첫 번째 스레드 종료 대기
	pthread_join(id_t1, NULL);
	// 두 번째 스레드 종료 대기
	pthread_join(id_t2, NULL);

	// 최종 합계 출력
	printf("result: %d \n", sum);
	return 0;
}

// 스레드가 실행할 함수 정의
void * thread_summation(void * arg) 
{
	int start = ((int*)arg)[0]; // 합산 시작 값
	int end = ((int*)arg)[1];   // 합산 종료 값

	// 시작 값부터 종료 값까지의 합을 계산
	while (start <= end)
	{
		sum += start; // 전역 변수 sum에 더하기
		start++;
	}
	return NULL;
}
