#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024 // 버퍼 크기 정의
void error_handling(char *message); // 에러 처리 함수 선언

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock; // 서버와 클라이언트 소켓 파일 디스크립터
    char message[BUF_SIZE]; // 클라이언트와 주고받을 메시지를 저장할 버퍼
    int str_len, i; // 수신된 문자열의 길이와 클라이언트 인덱스를 저장할 변수
    
    struct sockaddr_in serv_adr; // 서버 주소 정보를 담을 구조체
    struct sockaddr_in clnt_adr; // 클라이언트 주소 정보를 담을 구조체
    socklen_t clnt_adr_sz; // 클라이언트 주소 구조체 크기를 저장할 변수
    
    // 프로그램 실행 시 포트 번호를 인자로 받지 않은 경우 사용법 출력 후 종료
    if(argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    
    // 서버 소켓 생성 (IPv4, TCP)
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);   
    if(serv_sock == -1)
        error_handling("socket() error");
    
    // 서버 주소 구조체 초기화 및 설정
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET; // IPv4
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY); // 모든 IP 주소에서의 연결을 허용
    serv_adr.sin_port = htons(atoi(argv[1])); // 입력받은 포트 번호
    
    // 서버 소켓에 주소 할당
    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    
    // 연결 요청 대기 큐 생성
    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");
    
    clnt_adr_sz = sizeof(clnt_adr); // 클라이언트 주소 구조체 크기 설정

    // 5명의 클라이언트를 순차적으로 처리
    for(i = 0; i < 5; i++)
    {
        // 클라이언트의 연결 요청 수락
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
        if(clnt_sock == -1)
            error_handling("accept() error");
        else
            printf("Connected client %d \n", i + 1);
    
        // 클라이언트로부터 메시지를 읽고 다시 보내는 에코 처리
        while((str_len = read(clnt_sock, message, BUF_SIZE)) != 0)
            write(clnt_sock, message, str_len);

        close(clnt_sock); // 클라이언트 소켓 닫기
    }

    close(serv_sock); // 서버 소켓 닫기
    return 0;
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수 정의
void error_handling(char *message)
{
    fputs(message, stderr); // 에러 메시지 출력
    fputc('\n', stderr);
    exit(1); // 프로그램 종료
}
