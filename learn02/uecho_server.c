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
    int serv_sock;  // 서버 소켓 디스크립터
    char message[BUF_SIZE];  // 수신 메시지를 저장할 버퍼
    int str_len;  // 수신된 메시지의 길이
    socklen_t clnt_adr_sz;  // 클라이언트 주소 구조체의 크기

    struct sockaddr_in serv_adr, clnt_adr;  // 서버와 클라이언트 주소 구조체

    // 포트 번호가 명령줄 인자로 제공되었는지 확인
    if(argc != 2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    
    // UDP 소켓 생성
    serv_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(serv_sock == -1)
        error_handling("UDP socket creation error");
    
    // 서버 주소 구조체를 0으로 초기화
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;  // 주소 패밀리를 AF_INET(IPv4)로 설정
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);  // 모든 IP 주소로부터의 연결 수락
    serv_adr.sin_port = htons(atoi(argv[1]));  // 포트 번호 설정 (문자열에서 정수로 변환)
    
    // 소켓을 서버 주소에 바인딩
    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");

    // 메시지를 계속해서 수신하고 송신하기 위한 무한 루프 실행
    while(1) 
    {
        clnt_adr_sz = sizeof(clnt_adr);  // 클라이언트 주소 구조체의 크기 설정
        // 클라이언트로부터 메시지 수신
        str_len = recvfrom(serv_sock, message, BUF_SIZE, 0, 
                           (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
        // 수신된 메시지를 클라이언트에게 다시 송신 (에코 서버)
        sendto(serv_sock, message, str_len, 0, 
               (struct sockaddr*)&clnt_adr, clnt_adr_sz);
    }    
    close(serv_sock);  // 서버 소켓 닫기
    return 0;
}

// 에러를 처리하는 함수
void error_handling(char *message)
{
    fputs(message, stderr);  // 에러 메시지를 표준 에러 출력에 출력
    fputc('\n', stderr);  // 표준 에러 출력에 개행 문자 출력
    exit(1);  // 프로그램을 비정상 종료
}
