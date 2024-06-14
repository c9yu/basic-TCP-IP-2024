#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int status;
    pid_t pid = fork();  // 첫 번째 자식 프로세스 생성

    if (pid == 0)  // 첫 번째 자식 프로세스의 코드
    {
        return 3;  // 종료 상태로 3 반환
    }
    else  // 부모 프로세스의 코드
    {
        printf("Child PID: %d \n", pid);  // 첫 번째 자식 프로세스의 PID 출력
        pid = fork();  // 두 번째 자식 프로세스 생성
        if (pid == 0)  // 두 번째 자식 프로세스의 코드
        {
            exit(7);  // 종료 상태로 7 반환
        }
        else  // 부모 프로세스의 코드
        {
            printf("Child PID: %d \n", pid);  // 두 번째 자식 프로세스의 PID 출력
            wait(&status);  // 첫 번째 자식 프로세스의 종료 상태 대기
            if (WIFEXITED(status))  // 정상 종료되었는지 확인
                printf("Child send one: %d \n", WEXITSTATUS(status));  // 첫 번째 자식 프로세스의 종료 코드 출력

            wait(&status);  // 두 번째 자식 프로세스의 종료 상태 대기
            if (WIFEXITED(status))  // 정상 종료되었는지 확인
                printf("Child send two: %d \n", WEXITSTATUS(status));  // 두 번째 자식 프로세스의 종료 코드 출력
            sleep(30);  // 30초 대기
        }
    }
    return 0;
}
