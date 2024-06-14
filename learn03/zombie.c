#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t pid = fork();  // 새로운 프로세스 생성

    if (pid == 0)  // 자식 프로세스인 경우
    {
        puts("Hi I'm a child process");  // 자식 프로세스에서 메시지 출력
    }
    else  // 부모 프로세스인 경우
    {
        printf("Child Process ID: %d \n", pid);  // 자식 프로세스의 PID 출력
        sleep(30);  // 30초 동안 대기
    }

    if (pid == 0)  // 자식 프로세스인 경우
        puts("End child process");  // 자식 프로세스 종료 메시지 출력
    else  // 부모 프로세스인 경우
        puts("End parent process");  // 부모 프로세스 종료 메시지 출력

    return 0;
}
