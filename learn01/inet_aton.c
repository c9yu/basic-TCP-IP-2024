#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

// 에러 처리 함수 선언
void error_handling(char *message);

int main(int argc, char *argv[])
{
    char *addr = "127.232.124.79"; // IPv4 주소 문자열
    struct sockaddr_in addr_inet; // sockaddr_in 구조체 변수
    
    // inet_aton 함수를 사용하여 IPv4 주소를 네트워크 바이트 순서의 정수로 변환
    if (!inet_aton(addr, &addr_inet.sin_addr))
        error_handling("Conversion error"); // 변환 중 오류가 발생한 경우 에러 처리
    else
        // 변환된 네트워크 바이트 순서의 정수를 출력
        printf("Network ordered integer address: %#x \n", addr_inet.sin_addr.s_addr);
    
    return 0;
}

// 에러 처리 함수 정의
void error_handling(char *message)
{
    // 에러 메시지 출력
    fputs(message, stderr);
    fputc('\n', stderr);
    // 프로그램 종료
    exit(1);
}
