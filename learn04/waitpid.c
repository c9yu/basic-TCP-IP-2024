#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int status;
    pid_t pid = fork();  // 새로운 프로세스 생성

    if (pid == 0)  // 자식 프로세스인 경우
    {
        sleep(15);  // 15초 동안 대기
        return 24;  // 종료 상태로 24 반환
    }
    else  // 부모 프로세스인 경우
    {
        while (!waitpid(-1, &status, WNOHANG))  // 자식 프로세스의 상태를 비동기로 확인
        {
            sleep(3);  // 3초 동안 대기
            puts("sleep 3sec.");  // 3초 대기 메시지 출력
        }

        if (WIFEXITED(status))  // 자식 프로세스가 정상 종료되었는지 확인
            printf("Child send %d \n", WEXITSTATUS(status));  // 자식 프로세스의 종료 코드 출력
    }
    return 0;
}

/*
root@my_linux:/home/swyoon/tcpip# gcc waitpid.c -o waitpid
root@my_linux:/home/swyoon/tcpip# ./waitpid
sleep 3sec.
sleep 3sec.
sleep 3sec.
sleep 3sec.
sleep 3sec.
Child send 24 
*/
