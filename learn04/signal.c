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

// SIGINT 신호를 처리하는 핸들러 함수
void keycontrol(int sig)
{
    if (sig == SIGINT)  // 신호가 SIGINT인지 확인
        puts("CTRL+C pressed");
}

int main(int argc, char *argv[])
{
    int i;
    signal(SIGALRM, timeout);  // SIGALRM 신호에 대해 timeout 함수 등록
    signal(SIGINT, keycontrol);  // SIGINT 신호에 대해 keycontrol 함수 등록
    alarm(2);  // 2초 후에 SIGALRM 신호 발생

    for (i = 0; i < 3; i++)
    {
        puts("wait...");
        sleep(100);  // 100초 동안 대기 (신호 발생 시 대기 중단)
    }
    return 0;
}
