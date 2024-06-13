#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30  // 수신 메시지를 저장할 버퍼 크기
void error_handling(char *message);  // 에러 처리 함수 프로토타입

int main(int argc, char *argv[])
{
    int sock;  // 클라이언트 소켓 디스크립터
    char message[BUF_SIZE];  // 수신 메시지를 저장할 버퍼
    int str_len;  // 수신된 메시지의 길이
    socklen_t adr_sz;  // 서버 주소 구조체의 크기

    struct sockaddr_in serv_adr, from_adr;  // 서버와 클라이언트 주소 구조체

    // IP 주소와 포트 번호가 명령줄 인자로 제공되었는지 확인
    if(argc != 3){
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }
    
    // UDP 소켓 생성
    sock = socket(PF_INET, SOCK_DGRAM, 0);   
    if(sock == -1)
        error_handling("socket() error");
    
    // 서버 주소 구조체를 0으로 초기화
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;  // 주소 패밀리를 AF_INET(IPv4)로 설정
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);  // IP 주소 설정
    serv_adr.sin_port = htons(atoi(argv[2]));  // 포트 번호 설정 (문자열에서 정수로 변환)
    
    // 메시지를 계속해서 송신하고 수신하기 위한 무한 루프 실행
    while(1)
    {
        fputs("Insert message(q to quit): ", stdout);  // 메시지 입력 요청 출력
        fgets(message, sizeof(message), stdin);  // 사용자로부터 메시지 입력 받기
        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))  // 입력된 메시지가 'q' 또는 'Q'이면
            break;  // 루프 탈출 (프로그램 종료)
        
        // 서버로 메시지 송신
        sendto(sock, message, strlen(message), 0, 
               (struct sockaddr*)&serv_adr, sizeof(serv_adr));
        adr_sz = sizeof(from_adr);  // 서버 주소 구조체의 크기 설정
        // 서버로부터 메시지 수신
        str_len = recvfrom(sock, message, BUF_SIZE, 0, 
                           (struct sockaddr*)&from_adr, &adr_sz);

        message[str_len] = 0;  // 수신된 메시지의 끝에 NULL 문자 추가
        printf("Message from server: %s", message);  // 수신된 메시지 출력
    }    
    close(sock);  // 클라이언트 소켓 닫기
    return 0;
}

// 에러를 처리하는 함수
void error_handling(char *message)
{
    fputs(message, stderr);  // 에러 메시지를 표준 에러 출력에 출력
    fputc('\n', stderr);  // 표준 에러 출력에 개행 문자 출력
    exit(1);  // 프로그램을 비정상 종료
}
