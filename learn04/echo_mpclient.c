#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);  // 에러 핸들링 함수 선언
void read_routine(int sock, char *buf);  // 데이터 읽기 함수 선언
void write_routine(int sock, char *buf);  // 데이터 쓰기 함수 선언

int main(int argc, char *argv[])
{
    int sock;
    pid_t pid;
    char buf[BUF_SIZE];
    struct sockaddr_in serv_adr;

    // 사용법을 잘못 입력한 경우
    if (argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    // 소켓 생성
    sock = socket(PF_INET, SOCK_STREAM, 0);  
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;  // 주소 체계 설정
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);  // 서버 IP 주소 설정
    serv_adr.sin_port = htons(atoi(argv[2]));  // 포트 번호 설정

    // 서버에 연결
    if (connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect() error!");

    pid = fork();  // 새로운 프로세스 생성
    if (pid == 0)  // 자식 프로세스인 경우
        write_routine(sock, buf);  // 데이터 쓰기 함수 호출
    else  // 부모 프로세스인 경우
        read_routine(sock, buf);  // 데이터 읽기 함수 호출

    close(sock);  // 소켓 닫기
    return 0;
}

// 데이터 읽기 함수
void read_routine(int sock, char *buf)
{
    while (1)
    {
        int str_len = read(sock, buf, BUF_SIZE);  // 서버로부터 데이터 읽기
        if (str_len == 0)  // 데이터가 없으면 함수 종료
            return;

        buf[str_len] = 0;  // 문자열의 끝에 null 문자 추가
        printf("Message from server: %s", buf);  // 서버로부터 받은 메시지 출력
    }
}

// 데이터 쓰기 함수
void write_routine(int sock, char *buf)
{
    while (1)
    {
        fgets(buf, BUF_SIZE, stdin);  // 표준 입력으로부터 데이터 읽기
        if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n"))  // 'q' 또는 'Q' 입력 시
        {    
            shutdown(sock, SHUT_WR);  // 쓰기 종료
            return;
        }
        write(sock, buf, strlen(buf));  // 서버로 데이터 쓰기
    }
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
