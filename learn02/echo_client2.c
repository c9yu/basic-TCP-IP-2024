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
    int sock; // 클라이언트 소켓 파일 디스크립터
    char message[BUF_SIZE]; // 서버와 주고받을 메시지를 저장할 버퍼
    int str_len, recv_len, recv_cnt; // 송수신된 문자열의 길이와 부분 수신된 문자열의 길이를 저장할 변수
    struct sockaddr_in serv_adr; // 서버 주소 정보를 담을 구조체

    // 프로그램 실행 시 IP 주소와 포트 번호를 인자로 받지 않은 경우 사용법 출력 후 종료
    if(argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }
    
    // 클라이언트 소켓 생성 (IPv4, TCP)
    sock = socket(PF_INET, SOCK_STREAM, 0);   
    if(sock == -1)
        error_handling("socket() error");
    
    // 서버 주소 구조체 초기화 및 설정
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET; // IPv4
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]); // 입력받은 IP 주소
    serv_adr.sin_port = htons(atoi(argv[2])); // 입력받은 포트 번호
    
    // 서버에 연결 요청
    if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect() error!");
    else
        puts("Connected..........."); // 연결 성공 메시지 출력
    
    while(1) 
    {
        // 사용자로부터 메시지 입력 받기
        fputs("Input message(Q to quit): ", stdout);
        fgets(message, BUF_SIZE, stdin);
        
        // 'Q' 또는 'q'를 입력하면 루프 종료
        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;

        // 서버로 메시지 전송
        str_len = write(sock, message, strlen(message));
        
        // 서버로부터 메시지 수신
        recv_len = 0;
        while(recv_len < str_len)
        {
            recv_cnt = read(sock, &message[recv_len], BUF_SIZE - 1);
            if(recv_cnt == -1)
                error_handling("read() error!");
            recv_len += recv_cnt;
        }
        
        message[recv_len] = 0; // 문자열 끝에 NULL 추가
        printf("Message from server: %s", message); // 수신된 메시지 출력
    }
    
    close(sock); // 소켓 닫기
    return 0;
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수 정의
void error_handling(char *message)
{
    fputs(message, stderr); // 에러 메시지 출력
    fputc('\n', stderr);
    exit(1); // 프로그램 종료
}
