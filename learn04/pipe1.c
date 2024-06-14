#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 30

int main(int argc, char *argv[])
{
    int fds[2];  // 파이프 파일 디스크립터 배열
    char str[] = "Who are you?";  // 전송할 문자열
    char buf[BUF_SIZE];  // 데이터를 읽어올 버퍼
    pid_t pid;

    pipe(fds);  // 파이프 생성
    pid = fork();  // 새로운 프로세스 생성

    if (pid == 0)  // 자식 프로세스인 경우
    {
        write(fds[1], str, sizeof(str));  // 파이프의 쓰기 끝에 데이터 쓰기
    }
    else  // 부모 프로세스인 경우
    {
        read(fds[0], buf, BUF_SIZE);  // 파이프의 읽기 끝에서 데이터 읽기
        puts(buf);  // 읽어온 데이터 출력
    }

    return 0;
}
