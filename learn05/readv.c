#include <stdio.h>      // 표준 입출력 함수를 사용하기 위한 헤더 파일
#include <sys/uio.h>    // 벡터 입출력 함수를 사용하기 위한 헤더 파일

#define BUF_SIZE 100    // 버퍼 크기를 100바이트로 정의

int main(int argc, char *argv[])
{
    struct iovec vec[2];       // 두 개의 iovec 구조체 배열을 선언
    char buf1[BUF_SIZE] = {0,}; // 첫 번째 버퍼, 0으로 초기화
    char buf2[BUF_SIZE] = {0,}; // 두 번째 버퍼, 0으로 초기화
    int str_len;               // 읽어들인 총 바이트 수를 저장할 변수

    // 첫 번째 iovec 구조체 초기화 (버퍼의 시작 주소와 길이)
    vec[0].iov_base = buf1;    // 버퍼1의 시작 주소
    vec[0].iov_len = 5;        // 버퍼1의 길이 (5바이트 읽기)

    // 두 번째 iovec 구조체 초기화 (버퍼의 시작 주소와 길이)
    vec[1].iov_base = buf2;    // 버퍼2의 시작 주소
    vec[1].iov_len = BUF_SIZE; // 버퍼2의 길이 (최대 BUF_SIZE 바이트 읽기)

    // 벡터 입출력을 사용하여 데이터를 읽기 (표준 입력, 파일 디스크립터 0)
    str_len = readv(0, vec, 2);

    // 총 읽어들인 바이트 수를 출력
    printf("Read bytes: %d \n", str_len);

    // 첫 번째 버퍼에 저장된 메시지를 출력
    printf("First message: %s \n", buf1);

    // 두 번째 버퍼에 저장된 메시지를 출력
    printf("Second message: %s \n", buf2);

    return 0;
}

/*
실행 예시:
swyoon@my_linux:~/tcpip$ gcc readv.c -o rv
swyoon@my_linux:~/tcpip$ ./rv
I like TCP/IP socket programming~
Read bytes: 34 
First message: I lik 
Second message: e TCP/IP socket programming~
*/
