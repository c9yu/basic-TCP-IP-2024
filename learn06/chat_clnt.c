#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define BUF_SIZE 100
#define NAME_SIZE 20

void * send_msg(void * arg);   // 메시지를 전송하는 스레드 함수
void * recv_msg(void * arg);   // 메시지를 수신하는 스레드 함수
void error_handling(char * msg);  // 오류 처리 함수

char name[NAME_SIZE]="[DEFAULT]";  // 기본 이름 버퍼
char msg[BUF_SIZE];  // 메시지 버퍼

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    pthread_t snd_thread, rcv_thread;
    void * thread_return;
    
    // 올바른 명령행 인수인지 확인
    if(argc!=4) {
        printf("사용법 : %s <IP> <port> <이름>\n", argv[0]);
        exit(1);
    }
    
    // 사용자 이름 설정
    sprintf(name, "[%s]", argv[3]);
    
    // 소켓 생성
    sock=socket(PF_INET, SOCK_STREAM, 0);
    
    // 서버 주소 구조체 초기화
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));
    
    // 서버에 연결
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
        error_handling("connect() 오류");
    
    // 메시지 전송 및 수신을 위한 스레드 생성
    pthread_create(&snd_thread, NULL, send_msg, (void*)&sock);
    pthread_create(&rcv_thread, NULL, recv_msg, (void*)&sock);
    
    // 스레드 종료까지 대기
    pthread_join(snd_thread, &thread_return);
    pthread_join(rcv_thread, &thread_return);
    
    // 소켓 닫기
    close(sock);  
    return 0;
}

// 메시지 전송 스레드 함수
void * send_msg(void * arg)
{
    int sock=*((int*)arg);
    char name_msg[NAME_SIZE+BUF_SIZE];
    while(1) 
    {
        // 사용자 입력 받기
        fgets(msg, BUF_SIZE, stdin);
        
        // 사용자가 종료하고자 할 경우 소켓 닫고 스레드 종료
        if(!strcmp(msg,"q\n")||!strcmp(msg,"Q\n")) 
        {
            close(sock);
            exit(0);
        }
        
        // 이름과 메시지를 합쳐서 전송할 메시지 구성
        sprintf(name_msg,"%s %s", name, msg);
        
        // 서버로 메시지 전송
        write(sock, name_msg, strlen(name_msg));
    }
    return NULL;
}

// 메시지 수신 스레드 함수
void * recv_msg(void * arg)
{
    int sock=*((int*)arg);
    char name_msg[NAME_SIZE+BUF_SIZE];
    int str_len;
    while(1)
    {
        // 서버로부터 메시지 수신
        str_len=read(sock, name_msg, NAME_SIZE+BUF_SIZE-1);
        
        // 읽기 오류 처리
        if(str_len==-1) 
            return (void*)-1;
        
        // 수신된 메시지 널 종료 처리
        name_msg[str_len]=0;
        
        // 수신된 메시지 출력
        fputs(name_msg, stdout);
    }
    return NULL;
}

// 오류 처리 함수
void error_handling(char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}
