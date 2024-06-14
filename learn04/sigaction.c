#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// SIGALRM 신호를 처리하는 핸들러 함수
void timeout(int sig)
{
    if (sig == SIGALRM)  // 신호가 SIGALRM인지 확인
        puts("Time out!");
    alarm(2);  // 2초 후에 다시 SIGALRM 신호 발생
}

int main(int argc, char *argv[])
{
    int i;
    struct sigaction act;  // 신호 처리를 위한 sigaction 구조체 선언
    act.sa_handler = timeout;  // SIGALRM 신호에 대해 timeout 함수 등록
    sigemptyset(&act.sa_mask);  // 신호 마스크를 비움
    act.sa_flags = 0;  // 추가 플래그 설정 없음
    sigaction(SIGALRM, &act, 0);  // SIGALRM 신호에 대한 새로운 동작 설정

    alarm(2);  // 2초 후에 SIGALRM 신호 발생

    for (i = 0; i < 3; i++)
    {
        puts("wait...");
        sleep(100);  // 100초 동안 대기 (신호 발생 시 대기 중단)
    }
    return 0;
}
