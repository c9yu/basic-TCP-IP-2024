#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30  // 수신 메시지를 저장할 버퍼 크기
void error_handling(char *message);  // 에러 처리 함수 프로토타입

int main(int argc, char *argv[])
{
    int sock;  // 소켓 디스크립터
    char message[BUF_SIZE];  // 수신 메시지를 저장할 버퍼
    struct sockaddr_in my_adr, your_adr;  // 서버와 클라이언트 주소 구조체
    socklen_t adr_sz;  // 클라이언트 주소 구조체의 크기
    int str_len, i;  // 수신된 메시지의 길이 및 루프 카운터

    // 포트 번호가 명령줄 인자로 제공되었는지 확인
    if(argc != 2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    
    // UDP 소켓 생성
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock == -1)
        error_handling("socket() error");
    
    // 서버 주소 구조체를 0으로 초기화
    memset(&my_adr, 0, sizeof(my_adr));
    my_adr.sin_family = AF_INET;  // 주소 패밀리를 AF_INET(IPv4)로 설정
    my_adr.sin_addr.s_addr = htonl(INADDR_ANY);  // 모든 IP 주소로부터의 연결 수락
    my_adr.sin_port = htons(atoi(argv[1]));  // 포트 번호 설정 (문자열에서 정수로 변환)
    
    // 소켓을 서버 주소에 바인딩
    if(bind(sock, (struct sockaddr*)&my_adr, sizeof(my_adr)) == -1)
        error_handling("bind() error");
    
    // 3개의 메시지를 수신하고 출력하기 위한 루프
    for(i = 0; i < 3; i++)
    {
        sleep(5);  // 5초 지연
        adr_sz = sizeof(your_adr);  // 클라이언트 주소 구조체의 크기 설정
        // 클라이언트로부터 메시지 수신
        str_len = recvfrom(sock, message, BUF_SIZE, 0, 
                           (struct sockaddr*)&your_adr, &adr_sz);     
        
        // 수신된 메시지 출력
        printf("Message %d: %s \n", i + 1, message);
    }
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
root@my_linux:/home/swyoon/tcpip# gcc bound_host1.c -o host1
root@my_linux:/home/swyoon/tcpip# ./host1 
Usage : ./host1 <port>
root@my_linux:/home/swyoon/tcpip# ./host1 9190
Message 1: Hi! 
Message 2: I'm another UDP host! 
Message 3: Nice to meet you 
root@my_linux:/home/swyoon/tcpip# 
*/

// 이 주석 블록은 소스 파일을 컴파일하고 실행하는 예제를 보여줍니다. 
// 컴파일 명령어와 프로그램 실행 예제, 프로그램이 수신한 메시지를 출력합니다.
