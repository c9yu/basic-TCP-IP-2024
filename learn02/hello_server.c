#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// 에러 메시지를 출력하고 프로그램을 종료하는 함수 선언
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int serv_sock; // 서버 소켓 파일 디스크립터
    int clnt_sock; // 클라이언트 소켓 파일 디스크립터

    struct sockaddr_in serv_addr; // 서버 주소 정보를 담을 구조체
    struct sockaddr_in clnt_addr; // 클라이언트 주소 정보를 담을 구조체
    socklen_t clnt_addr_size; // 클라이언트 주소 구조체의 크기

    char message[] = "Hello World!"; // 클라이언트로 전송할 메시지
    
    // 프로그램 실행 시 포트 번호를 인자로 받지 않은 경우 사용법 출력 후 종료
    if(argc != 2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    
    // 소켓 생성 (IPv4, TCP)
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket() error");
    
    // 서버 주소 구조체 초기화 및 설정
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET; // IPv4
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 모든 IP 주소에서의 연결을 허용
    serv_addr.sin_port = htons(atoi(argv[1])); // 프로그램 실행 시 입력받은 포트 번호
    
    // 소켓에 주소와 포트 번호를 바인딩
    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error"); 
    
    // 연결 요청 대기열 생성
    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");
    
    // 클라이언트 연결 요청 수락
    clnt_addr_size = sizeof(clnt_addr);  
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if(clnt_sock == -1)
        error_handling("accept() error");  
    
    // 클라이언트로 메시지 전송
    write(clnt_sock, message, sizeof(message));
    
    // 클라이언트와 서버 소켓 닫기
    close(clnt_sock);    
    close(serv_sock);
    return 0;
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수 정의
void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
