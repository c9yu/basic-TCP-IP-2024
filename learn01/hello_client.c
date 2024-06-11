#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message); // 에러 처리 함수 선언

int main(int argc, char* argv[])
{
    int sock;
    struct sockaddr_in serv_addr; // 서버 주소 정보를 담는 구조체
    char message[30]; // 서버로부터 받을 메시지를 저장할 배열
    int str_len;
    
    // 사용법 출력
    if(argc!=3){
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }
    
    // TCP 소켓 생성
    sock=socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handling("socket() error");
    
    // serv_addr 구조체 초기화
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET; // IPv4 주소 체계 사용
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]); // 서버 IP 주소 설정
    serv_addr.sin_port=htons(atoi(argv[2])); // 서버 포트 번호 설정
        
    // 서버에 연결
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1) 
        error_handling("connect() error!");
    
    // 서버로부터 메시지 읽기
    str_len=read(sock, message, sizeof(message)-1);
    if(str_len==-1)
        error_handling("read() error!");
    
    // 받은 메시지 출력
    printf("Message from server: %s \n", message);  
    close(sock); // 소켓 닫기
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr); // 표준 오류 스트림에 메시지 출력
    fputc('\n', stderr); // 개행 출력
    exit(1); // 프로그램 종료
}
