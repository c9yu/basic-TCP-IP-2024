#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

void error_handling(char *message); // 에러 처리 함수 선언

int main(int argc, char* argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[30]; // 서버로부터 받을 메시지를 저장할 버퍼
    int str_len=0;
    int idx=0, read_len=0;
    
    if(argc!=3){
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }
    
    // TCP 소켓 생성
    sock=socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handling("socket() error");
    
    // 서버 주소 설정
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));
        
    // 서버에 연결
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1) 
        error_handling("connect() error!");

    // 서버로부터 메시지 읽기
    while(read_len=read(sock, &message[idx++], 1))
    {
        if(read_len==-1)
            error_handling("read() error!");
        
        str_len+=read_len;
    }

    // 받은 메시지와 함수 read 호출 횟수 출력
    printf("Message from server: %s \n", message);
    printf("Function read call count: %d \n", str_len);
    close(sock); // 소켓 닫기
    return 0;
}

// 에러 발생 시 처리하는 함수
void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
