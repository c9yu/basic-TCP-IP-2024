#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 30

int main(int argc, char *argv[])
{
    int fds[2];  // 파이프 파일 디스크립터 배열
    char str1[] = "Who are you?";  // 자식 프로세스에서 보낼 문자열
    char str2[] = "Thank you for your message";  // 부모 프로세스에서 보낼 문자열
    char buf[BUF_SIZE];  // 데이터를 읽어올 버퍼
    pid_t pid;

    pipe(fds);  // 파이프 생성
    pid = fork();  // 새로운 프로세스 생성

    if (pid == 0)  // 자식 프로세스인 경우
    {
        write(fds[1], str1, sizeof(str1));  // 파이프의 쓰기 끝에 데이터 쓰기
        sleep(2);  // 2초 동안 대기
        read(fds[0], buf, BUF_SIZE);  // 파이프의 읽기 끝에서 데이터 읽기
        printf("Child proc output: %s \n", buf);  // 읽어온 데이터 출력
    }
    else  // 부모 프로세스인 경우
    {
        read(fds[0], buf, BUF_SIZE);  // 파이프의 읽기 끝에서 데이터 읽기
        printf("Parent proc output: %s \n", buf);  // 읽어온 데이터 출력
        write(fds[1], str2, sizeof(str2));  // 파이프의 쓰기 끝에 데이터 쓰기
        sleep(3);  // 3초 동안 대기
    }

    return 0;
}
