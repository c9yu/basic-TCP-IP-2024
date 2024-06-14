#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

// SIGCHLD 신호를 처리하는 핸들러 함수
void read_childproc(int sig)
{
    int status;
    pid_t id = waitpid(-1, &status, WNOHANG);  // 자식 프로세스의 종료 상태를 비동기로 확인
    if (WIFEXITED(status))  // 자식 프로세스가 정상 종료되었는지 확인
    {
        printf("Removed proc id: %d \n", id);  // 종료된 자식 프로세스의 PID 출력
        printf("Child send: %d \n", WEXITSTATUS(status));  // 자식 프로세스의 종료 코드 출력
    }
}

int main(int argc, char *argv[])
{
    pid_t pid;
    struct sigaction act;
    act.sa_handler = read_childproc;  // SIGCHLD 신호에 대해 read_childproc 함수 등록
    sigemptyset(&act.sa_mask);  // 신호 마스크를 비움
    act.sa_flags = 0;  // 추가 플래그 설정 없음
    sigaction(SIGCHLD, &act, 0);  // SIGCHLD 신호에 대한 새로운 동작 설정

    pid = fork();  // 첫 번째 자식 프로세스 생성
    if (pid == 0)  // 첫 번째 자식 프로세스의 코드
    {
        puts("Hi! I'm child process");
        sleep(10);  // 10초 동안 대기
        return 12;  // 종료 상태로 12 반환
    }
    else  // 부모 프로세스의 코드
    {
        printf("Child proc id: %d \n", pid);  // 첫 번째 자식 프로세스의 PID 출력
        pid = fork();  // 두 번째 자식 프로세스 생성
        if (pid == 0)  // 두 번째 자식 프로세스의 코드
        {
            puts("Hi! I'm child process");
            sleep(10);  // 10초 동안 대기
            exit(24);  // 종료 상태로 24 반환
        }
        else  // 부모 프로세스의 코드
        {
            int i;
            printf("Child proc id: %d \n", pid);  // 두 번째 자식 프로세스의 PID 출력
            for (i = 0; i < 5; i++)  // 5번 반복
            {
                puts("wait...");
                sleep(5);  // 5초 동안 대기
            }
        }
    }
    return 0;
}

/*
root@my_linux:/home/swyoon/tcpip# gcc remove_zombie.c -o zombie
root@my_linux:/home/swyoon/tcpip# ./zombie
Hi! I'm child process
Child proc id: 9529 
Hi! I'm child process
Child proc id: 9530 
wait...
wait...
Removed proc id: 9530 
Child send: 24 
wait...
Removed proc id: 9529 
Child send: 12 
wait...
wait...
*/
