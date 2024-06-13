#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30  // 버퍼 크기 정의
void error_handling(char *message);  // 에러 처리 함수 프로토타입

int main(int argc, char *argv[])
{
    int serv_sd, clnt_sd;  // 서버와 클라이언트 소켓 디스크립터
    FILE * fp;  // 파일 포인터
    char buf[BUF_SIZE];  // 버퍼
    int read_cnt;  // 읽은 바이트 수

    struct sockaddr_in serv_adr, clnt_adr;  // 서버와 클라이언트 주소 구조체
    socklen_t clnt_adr_sz;  // 클라이언트 주소 구조체 크기

    // 포트 번호가 명령줄 인자로 제공되었는지 확인
    if(argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    // 파일을 바이너리 읽기 모드로 열기
    fp = fopen("file_server.c", "rb");  
    if (fp == NULL)
        error_handling("File open error");

    // TCP 소켓 생성
    serv_sd = socket(PF_INET, SOCK_STREAM, 0);   
    if(serv_sd == -1)
        error_handling("socket() error");

    // 서버 주소 구조체를 0으로 초기화
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;  // 주소 패밀리를 AF_INET(IPv4)로 설정
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);  // 모든 IP 주소로부터의 연결 수락
    serv_adr.sin_port = htons(atoi(argv[1]));  // 포트 번호 설정 (문자열에서 정수로 변환)

    // 소켓을 서버 주소에 바인딩
    if(bind(serv_sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");

    // 소켓을 수신 대기 상태로 설정
    if(listen(serv_sd, 5) == -1)
        error_handling("listen() error");

    // 클라이언트 연결 요청 수락
    clnt_adr_sz = sizeof(clnt_adr);    
    clnt_sd = accept(serv_sd, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
    if(clnt_sd == -1)
        error_handling("accept() error");

    // 파일 내용을 클라이언트로 전송
    while(1)
    {
        read_cnt = fread((void*)buf, 1, BUF_SIZE, fp);  // 파일에서 BUF_SIZE 바이트 읽기
        if(read_cnt < BUF_SIZE)  // 읽은 바이트 수가 BUF_SIZE보다 작으면
        {
            write(clnt_sd, buf, read_cnt);  // 읽은 만큼 클라이언트에 전송
            break;  // 루프 탈출
        }
        write(clnt_sd, buf, BUF_SIZE);  // BUF_SIZE만큼 클라이언트에 전송
    }

    // 전송 완료 후 소켓의 출력 스트림을 종료
    shutdown(clnt_sd, SHUT_WR);  
    // 클라이언트로부터 메시지 수신
    read(clnt_sd, buf, BUF_SIZE);  
    printf("Message from client: %s \n", buf);

    // 파일 닫기
    fclose(fp);
    // 소켓 닫기
    close(clnt_sd); 
    close(serv_sd); 

    return 0;
}

// 에러를 처리하는 함수
void error_handling(char *message)
{
    fputs(message, stderr);  // 에러 메시지를 표준 에러 출력에 출력
    fputc('\n', stderr);  // 표준 에러 출력에 개행 문자 출력
    exit(1);  // 프로그램을 비정상 종료
}
