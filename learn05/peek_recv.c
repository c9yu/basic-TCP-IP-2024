#include <stdio.h>      // 표준 입출력 함수를 사용하기 위한 헤더 파일
#include <unistd.h>     // UNIX 표준 함수들을 사용하기 위한 헤더 파일
#include <stdlib.h>     // 표준 라이브러리 함수들을 사용하기 위한 헤더 파일
#include <string.h>     // 문자열 관련 함수들을 사용하기 위한 헤더 파일
#include <sys/socket.h> // 소켓 관련 함수들을 사용하기 위한 헤더 파일
#include <arpa/inet.h>  // 인터넷 주소 변환 함수들을 사용하기 위한 헤더 파일

#define BUF_SIZE 30     // 버퍼 크기를 30바이트로 정의
void error_handling(char *message); // 에러 메시지를 출력하고 프로그램을 종료하는 함수 선언

int main(int argc, char *argv[])
{
    int acpt_sock, recv_sock;           // 소켓을 가리키는 파일 디스크립터 변수
    struct sockaddr_in acpt_adr, recv_adr; // 서버와 클라이언트의 주소 정보를 담을 구조체 변수
    int str_len, state;                 // 수신한 문자열의 길이와 상태를 저장할 변수
    socklen_t recv_adr_sz;              // 수신할 주소의 크기를 저장할 변수
    char buf[BUF_SIZE];                 // 데이터를 저장할 버퍼

    // 실행 시 입력 인자(매개변수)가 2개가 아니면 사용법을 출력하고 프로그램 종료
    if(argc!=2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    // TCP 소켓 생성 (IPv4 인터넷 프로토콜, TCP)
    acpt_sock = socket(PF_INET, SOCK_STREAM, 0);

    // 주소 구조체 변수를 0으로 초기화
    memset(&acpt_adr, 0, sizeof(acpt_adr));

    // 주소 구조체 변수 설정 (IPv4, 모든 IP 주소, 포트 번호)
    acpt_adr.sin_family = AF_INET;
    acpt_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    acpt_adr.sin_port = htons(atoi(argv[1]));

    // 소켓과 주소를 바인딩, 실패 시 에러 처리
    if(bind(acpt_sock, (struct sockaddr*)&acpt_adr, sizeof(acpt_adr)) == -1)
        error_handling("bind() error");

    // 소켓을 수신 대기 상태로 설정 (최대 5개의 연결 대기열)
    listen(acpt_sock, 5);

    // 클라이언트의 주소 크기를 설정
    recv_adr_sz = sizeof(recv_adr);

    // 클라이언트의 연결 요청을 수락, 새로운 소켓 생성
    recv_sock = accept(acpt_sock, (struct sockaddr*)&recv_adr, &recv_adr_sz);

    while(1)
    {
        // 비차단 모드로 데이터를 피킹 (MSG_PEEK|MSG_DONTWAIT 플래그 사용)
        str_len = recv(recv_sock, buf, sizeof(buf)-1, MSG_PEEK|MSG_DONTWAIT);
        if(str_len > 0)
            break; // 데이터가 있으면 루프 종료
    }

    buf[str_len] = 0; // 문자열 끝에 null 문자 추가
    printf("Buffering %d bytes: %s \n", str_len, buf); // 버퍼에 저장된 데이터 출력

    // 데이터를 다시 읽기 (이번에는 MSG_PEEK 플래그 없이)
    str_len = recv(recv_sock, buf, sizeof(buf)-1, 0);
    buf[str_len] = 0; // 문자열 끝에 null 문자 추가
    printf("Read again: %s \n", buf); // 읽은 데이터 출력

    // 소켓 닫기
    close(acpt_sock);
    close(recv_sock);

    return 0;
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수 정의
void error_handling(char *message)
{
    fputs(message, stderr);   // 에러 메시지를 표준 오류 출력(stderr)에 출력
    fputc('\n', stderr);      // 줄 바꿈 문자를 표준 오류 출력에 출력
    exit(1);                  // 프로그램 종료
}

