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
    int serv_sock, clnt_sock;           // 서버와 클라이언트 소켓을 가리키는 파일 디스크립터 변수
    char message[BUF_SIZE];             // 데이터를 저장할 버퍼
    int str_len, i;                     // 문자열의 길이와 반복문 제어 변수를 저장할 변수
    
    struct sockaddr_in serv_adr;        // 서버의 주소 정보를 담을 구조체 변수
    struct sockaddr_in clnt_adr;        // 클라이언트의 주소 정보를 담을 구조체 변수
    socklen_t clnt_adr_sz;              // 클라이언트 주소의 크기를 저장할 변수
    FILE * readfp;                      // 클라이언트 소켓을 읽기 모드로 사용할 파일 포인터
    FILE * writefp;                     // 클라이언트 소켓을 쓰기 모드로 사용할 파일 포인터
    
    // 실행 시 입력 인자(매개변수)가 2개가 아니면 사용법을 출력하고 프로그램 종료
    if(argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    
    // TCP 소켓 생성 (IPv4 인터넷 프로토콜, TCP)
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);   
    if(serv_sock == -1)
        error_handling("socket() error");
    
    // 주소 구조체 변수를 0으로 초기화
    memset(&serv_adr, 0, sizeof(serv_adr));
    // 주소 구조체 변수 설정 (IPv4, 모든 IP 주소, 포트 번호)
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    // 소켓과 주소를 바인딩, 실패 시 에러 처리
    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    
    // 소켓을 수신 대기 상태로 설정 (최대 5개의 연결 대기열)
    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");
    
    clnt_adr_sz = sizeof(clnt_adr);

    // 5번 반복하여 클라이언트 연결을 처리
    for(i = 0; i < 5; i++)
    {
        // 클라이언트의 연결 요청을 수락, 새로운 소켓 생성
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
        if(clnt_sock == -1)
            error_handling("accept() error");
        else
            printf("Connected client %d \n", i + 1);
    
        // 클라이언트 소켓을 파일 포인터로 변환 (읽기 모드)
        readfp = fdopen(clnt_sock, "r");
        // 클라이언트 소켓을 파일 포인터로 변환 (쓰기 모드)
        writefp = fdopen(clnt_sock, "w");
    
        // 클라이언트로부터 데이터를 읽어 다시 클라이언트로 전송
        while(!feof(readfp))
        {
            fgets(message, BUF_SIZE, readfp); // 데이터를 읽기
            fputs(message, writefp);          // 데이터를 쓰기
            fflush(writefp);                  // 버퍼를 비워 전송
        }
        // 파일 포인터 닫기
        fclose(readfp);
        fclose(writefp);
    }
    // 서버 소켓 닫기
    close(serv_sock);
    return 0;
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수 정의
void error_handling(char *message)
{
    fputs(message, stderr);   // 에러 메시지를 표준 오류 출력(stderr)에 출력
    fputc('\n', stderr);      // 줄 바꿈 문자를 표준 오류 출력에 출력
    exit(1);                  // 프로그램 종료
}
