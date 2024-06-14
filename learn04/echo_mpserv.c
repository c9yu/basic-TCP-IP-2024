#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);  // 에러 핸들링 함수 선언
void read_childproc(int sig);  // 자식 프로세스 종료 핸들러 함수 선언

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    
    pid_t pid;
    struct sigaction act;
    socklen_t adr_sz;
    int str_len, state;
    char buf[BUF_SIZE];
    
    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    act.sa_handler = read_childproc;  // SIGCHLD 신호에 대해 read_childproc 함수 등록
    sigemptyset(&act.sa_mask);  // 신호 마스크를 비움
    act.sa_flags = 0;  // 추가 플래그 설정 없음
    state = sigaction(SIGCHLD, &act, 0);  // SIGCHLD 신호에 대한 새로운 동작 설정

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);  // 서버 소켓 생성
    memset(&serv_adr, 0, sizeof(serv_adr));  // 서버 주소 구조체 초기화
    serv_adr.sin_family = AF_INET;  // 주소 체계 설정
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);  // 모든 IP로부터 연결 허용
    serv_adr.sin_port = htons(atoi(argv[1]));  // 포트 번호 설정
    
    if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");  // 바인딩 에러 처리
    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");  // 리슨 에러 처리
    
    while (1)
    {
        adr_sz = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);  // 클라이언트 연결 수락
        if (clnt_sock == -1)
            continue;
        else
            puts("new client connected...");

        pid = fork();  // 새로운 프로세스 생성
        if (pid == -1)
        {
            close(clnt_sock);
            continue;
        }
        if (pid == 0)  // 자식 프로세스인 경우
        {
            close(serv_sock);  // 서버 소켓 닫기
            while ((str_len = read(clnt_sock, buf, BUF_SIZE)) != 0)  // 클라이언트로부터 데이터 읽기
                write(clnt_sock, buf, str_len);  // 클라이언트로 데이터 쓰기
            
            close(clnt_sock);  // 클라이언트 소켓 닫기
            puts("client disconnected...");
            return 0;
        }
        else  // 부모 프로세스인 경우
            close(clnt_sock);  // 클라이언트 소켓 닫기
    }
    close(serv_sock);  // 서버 소켓 닫기
    return 0;
}

// 자식 프로세스 종료를 처리하는 함수
void read_childproc(int sig)
{
    pid_t pid;
    int status;
    pid = waitpid(-1, &status, WNOHANG);  // 종료된 자식 프로세스 확인
    printf("removed proc id: %d \n", pid);  // 종료된 자식 프로세스의 PID 출력
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
