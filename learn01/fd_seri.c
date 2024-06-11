#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>

int main(void)
{
    int fd1, fd2, fd3;

    // TCP 소켓을 생성하여 파일 디스크립터 fd1에 저장합니다.
    fd1 = socket(PF_INET, SOCK_STREAM, 0);

    // "test.dat" 파일을 생성하고 쓰기 전용으로 엽니다. 파일 디스크립터를 fd2에 저장합니다.
    fd2 = open("test.dat", O_CREAT | O_WRONLY | O_TRUNC);

    // UDP 소켓을 생성하여 파일 디스크립터 fd3에 저장합니다.
    fd3 = socket(PF_INET, SOCK_DGRAM, 0);

    // 각 파일 디스크립터의 값을 출력합니다.
    printf("file descriptor 1: %d\n", fd1);
    printf("file descriptor 2: %d\n", fd2);
    printf("file descriptor 3: %d\n", fd3);

    // 파일 디스크립터를 닫습니다.
    close(fd1);
    close(fd2);
    close(fd3);

    return 0;
}
