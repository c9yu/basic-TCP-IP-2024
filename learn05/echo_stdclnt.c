#include <stdio.h>      // 표준 입출력 함수를 사용하기 위한 헤더 파일
#include <stdlib.h>     // 표준 라이브러리 함수들을 사용하기 위한 헤더 파일
#include <string.h>     // 문자열 관련 함수들을 사용하기 위한 헤더 파일
#include <unistd.h>     // UNIX 표준 함수들을 사용하기 위한 헤더 파일
#include <arpa/inet.h>  // 인터넷 주소 변환 함수들을 사용하기 위한 헤더 파일
#include <sys/socket.h> // 소켓 관련 함수들을 사용하기 위한 헤더 파일

#define BUF_SIZE 1024   // 버퍼 크기를 1024바이트로 정의
void error_handling(char *message); // 에러 메시지를 출력하고 프로그램을 종료하는 함수 선언

int main(int argc, char *argv[])
{
    int sock;                      // 클라이언트 소켓을 가리키는 파일 디스크립터 변수
    char message[BUF_SIZE];        // 데이터를 저장할 버퍼
    int str_len;                   // 문자열의 길이를 저장할 변수
    struct sockaddr_in serv_adr;   // 서버의 주소 정보를 담을 구조체 변수
    FILE * readfp;                 // 소켓을 읽기 모드로 사용할 파일 포인터
    FILE * writefp;                // 소켓을 쓰기 모드로 사용할 파일 포인터

    // 실행 시 입력 인자(매개변수)가 3개가 아니면 사용법을 출력하고 프로그램 종료
    if(argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }
    
    // TCP 소켓 생성 (IPv4 인터넷 프로토콜, TCP)
    sock = socket(PF_INET, SOCK_STREAM, 0);   
    if(sock == -1)
        error_handling("socket() error");
    
    // 주소 구조체 변수를 0으로 초기화
    memset(&serv_adr, 0, sizeof(serv_adr));
    // 주소 구조체 변수 설정 (IPv4, 서버 IP 주소, 포트 번호)
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));
    
    // 서버에 연결 시도, 실패 시 에러 처리
    if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect() error!");
    else
        puts("Connected...........");

    // 소켓을 파일 포인터로 변환 (읽기 모드)
    readfp = fdopen(sock, "r");
    // 소켓을 파일 포인터로 변환 (쓰기 모드)
    writefp = fdopen(sock, "w");    

    // 무한 루프를 통해 사용자로부터 메시지를 입력받고 서버에 전송
    while(1) 
    {
        // 메시지 입력 요청 출력
        fputs("Input message(Q to quit): ", stdout);
        // 사용자로부터 메시지 입력받기
        fgets(message, BUF_SIZE, stdin);
        // 입력받은 메시지가 'q'나 'Q'이면 루프 종료
        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;

        // 입력받은 메시지를 서버로 전송
        fputs(message, writefp);
        fflush(writefp); // 버퍼를 비워 전송

        // 서버로부터 메시지를 읽어 출력
        fgets(message, BUF_SIZE, readfp);
        printf("Message from server: %s", message);
    }    
    // 파일 포인터 닫기
    fclose(writefp);
    fclose(readfp);
    return 0;
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수 정의
void error_handling(char *message)
{
    fputs(message, stderr);   // 에러 메시지를 표준 오류 출력(stderr)에 출력
    fputc('\n', stderr);      // 줄 바꿈 문자를 표준 오류 출력에 출력
    exit(1);                  // 프로그램 종료
}
