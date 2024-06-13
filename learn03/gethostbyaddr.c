#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

// 에러를 처리하는 함수 프로토타입
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int i;  // 반복문을 위한 변수
    struct hostent *host;  // 호스트 정보를 저장할 구조체
    struct sockaddr_in addr;  // 주소 정보를 저장할 구조체

    // IP 주소가 명령줄 인자로 제공되었는지 확인
    if(argc != 2) {
        printf("Usage : %s <IP>\n", argv[0]);
        exit(1);
    }

    // 주소 구조체를 0으로 초기화
    memset(&addr, 0, sizeof(addr));
    // 명령줄 인자로 받은 IP 주소를 네트워크 바이트 순서로 변환하여 구조체에 저장
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    // IP 주소를 이용하여 호스트 정보 가져오기
    host = gethostbyaddr((char*)&addr.sin_addr, 4, AF_INET);
    if(!host)
        error_handling("gethost... error");

    // 호스트의 공식 이름 출력
    printf("Official name: %s \n", host->h_name);

    // 호스트의 별칭들 출력
    for(i = 0; host->h_aliases[i]; i++)
        printf("Aliases %d: %s \n", i+1, host->h_aliases[i]);
    
    // 주소 타입 출력 (IPv4인지 IPv6인지 확인)
    printf("Address type: %s \n", 
        (host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");

    // 호스트의 IP 주소들 출력
    for(i = 0; host->h_addr_list[i]; i++)
        printf("IP addr %d: %s \n", i+1,
                    inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));    
    
    return 0;
}

// 에러를 처리하는 함수
void error_handling(char *message)
{
    fputs(message, stderr);  // 에러 메시지를 표준 에러 출력에 출력
    fputc('\n', stderr);  // 표준 에러 출력에 개행 문자 출력
    exit(1);  // 프로그램을 비정상 종료
}
