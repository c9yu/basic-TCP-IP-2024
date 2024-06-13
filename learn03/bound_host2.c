#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30  // 버퍼 크기 정의
void error_handling(char *message);  // 에러 처리 함수 프로토타입

int main(int argc, char *argv[])
{
    int sock;  // 소켓 디스크립터
    char msg1[] = "Hi!";  // 첫 번째 전송 메시지
    char msg2[] = "I'm another UDP host!";  // 두 번째 전송 메시지
    char msg3[] = "Nice to meet you";  // 세 번째 전송 메시지

    struct sockaddr_in your_adr;  // 서버 주소 구조체
    socklen_t your_adr_sz;  // 서버 주소 구조체 크기

    // IP 주소와 포트 번호가 명령줄 인자로 제공되었는지 확인
    if(argc != 3){
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }
    
    // UDP 소켓 생성
    sock = socket(PF_INET, SOCK_DGRAM, 0);   
    if(sock == -1)
        error_handling("socket() error");
    
    // 서버 주소 구조체를 0으로 초기화
    memset(&your_adr, 0, sizeof(your_adr));
    your_adr.sin_family = AF_INET;  // 주소 패밀리를 AF_INET(IPv4)로 설정
    your_adr.sin_addr.s_addr = inet_addr(argv[1]);  // IP 주소 설정
    your_adr.sin_port = htons(atoi(argv[2]));  // 포트 번호 설정 (문자열에서 정수로 변환)
    
    // 서버로 메시지 전송
    sendto(sock, msg1, sizeof(msg1), 0, 
           (struct sockaddr*)&your_adr, sizeof(your_adr));
    sendto(sock, msg2, sizeof(msg2), 0, 
           (struct sockaddr*)&your_adr, sizeof(your_adr));
    sendto(sock, msg3, sizeof(msg3), 0, 
           (struct sockaddr*)&your_adr, sizeof(your_adr));
    
    close(sock);  // 소켓 닫기
    return 0;
}

// 에러를 처리하는 함수
void error_handling(char *message)
{
    fputs(message, stderr);  // 에러 메시지를 표준 에러 출력에 출력
    fputc('\n', stderr);  // 표준 에러 출력에 개행 문자 출력
    exit(1);  // 프로그램을 비정상 종료
}

/*
root@my_linux:/home/swyoon/tcpip# gcc bound_host2.c -o host2
root@my_linux:/home/swyoon/tcpip# ./host2
Usage : ./host2 <IP> <port>
root@my_linux:/home/swyoon/tcpip# ./host2 127.0.0.1 9190
root@my_linux:/home/swyoon/tcpip# 
*/

// 이 주석 블록은 소스 파일을 컴파일하고 실행하는 예제를 보여줍니다. 
// 컴파일 명령어와 프로그램 실행 예제를 포함하며, 프로그램이 실행된 후의 상태를 보여줍니다.
