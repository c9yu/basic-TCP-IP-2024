#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// 에러 메시지를 출력하고 프로그램을 종료하는 함수 선언
void error_handling(char *message);

int main(int argc, char* argv[])
{
    int sock; // 클라이언트 소켓 파일 디스크립터
    struct sockaddr_in serv_addr; // 서버 주소 정보를 담을 구조체
    char message[30]; // 서버로부터 받을 메시지를 저장할 버퍼
    int str_len; // 수신된 문자열의 길이를 저장할 변수
    
    // 프로그램 실행 시 IP 주소와 포트 번호를 인자로 받지 않은 경우 사용법 출력 후 종료
    if(argc != 3){
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }
    
    // 소켓 생성 (IPv4, TCP)
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handling("socket() error");
    
    // 서버 주소 구조체 초기화 및 설정
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET; // IPv4
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // 입력받은 IP 주소
    serv_addr.sin_port = htons(atoi(argv[2])); // 입력받은 포트 번호
    
    // 서버에 연결 요청
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) 
        error_handling("connect() error!");
    
    // 서버로부터 메시지 수신
    str_len = read(sock, message, sizeof(message) - 1);
    if(str_len == -1)
        error_handling("read() error!");
    
    // 수신된 메시지 출력
    printf("Message from server: %s \n", message);  
    
    // 소켓 닫기
    close(sock);
    return 0;
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수 정의
void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
