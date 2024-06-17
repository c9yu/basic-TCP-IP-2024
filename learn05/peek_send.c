#include <stdio.h>      // 표준 입출력 함수를 사용하기 위한 헤더 파일
#include <unistd.h>     // UNIX 표준 함수들을 사용하기 위한 헤더 파일
#include <stdlib.h>     // 표준 라이브러리 함수들을 사용하기 위한 헤더 파일
#include <string.h>     // 문자열 관련 함수들을 사용하기 위한 헤더 파일
#include <sys/socket.h> // 소켓 관련 함수들을 사용하기 위한 헤더 파일
#include <arpa/inet.h>  // 인터넷 주소 변환 함수들을 사용하기 위한 헤더 파일

// 에러 메시지를 출력하고 프로그램을 종료하는 함수 선언
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;                      // 소켓을 가리키는 파일 디스크립터 변수
    struct sockaddr_in send_adr;   // 서버의 주소 정보를 담을 구조체 변수

    // 실행 시 입력 인자(매개변수)가 3개가 아니면 사용법을 출력하고 프로그램 종료
    if(argc!=3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    // TCP 소켓 생성 (IPv4 인터넷 프로토콜, TCP)
    sock = socket(PF_INET, SOCK_STREAM, 0);

    // 주소 구조체 변수를 0으로 초기화
    memset(&send_adr, 0, sizeof(send_adr));

    // 주소 구조체 변수 설정 (IPv4, IP 주소, 포트 번호)
    send_adr.sin_family = AF_INET;
    send_adr.sin_addr.s_addr = inet_addr(argv[1]);
    send_adr.sin_port = htons(atoi(argv[2]));

    // 서버에 연결 시도, 실패 시 에러 처리
    if(connect(sock, (struct sockaddr*)&send_adr, sizeof(send_adr)) == -1)
        error_handling("connect() error!");

    // 서버에 데이터 전송 (문자열 "123")
    write(sock, "123", strlen("123"));

    // 소켓 닫기
    close(sock);

    return 0;
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수 정의
void error_handling(char *message)
{
    fputs(message, stderr);   // 에러 메시지를 표준 오류 출력(stderr)에 출력
    fputc('\n', stderr);      // 줄 바꿈 문자를 표준 오류 출력에 출력
    exit(1);                  // 프로그램 종료
}

