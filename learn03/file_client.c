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
    int sd;  // 소켓 디스크립터
    FILE *fp;  // 파일 포인터
    
    char buf[BUF_SIZE];  // 버퍼
    int read_cnt;  // 읽은 바이트 수
    struct sockaddr_in serv_adr;  // 서버 주소 구조체

    // IP 주소와 포트 번호가 명령줄 인자로 제공되었는지 확인
    if(argc != 3) {
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }
    
    // 파일을 바이너리 쓰기 모드로 열기
    fp = fopen("receive.dat", "wb");
    if (fp == NULL)
        error_handling("File open error");

    // TCP 소켓 생성
    sd = socket(PF_INET, SOCK_STREAM, 0);   
    if(sd == -1)
        error_handling("socket() error");

    // 서버 주소 구조체를 0으로 초기화
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;  // 주소 패밀리를 AF_INET(IPv4)로 설정
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);  // IP 주소 설정
    serv_adr.sin_port = htons(atoi(argv[2]));  // 포트 번호 설정 (문자열에서 정수로 변환)

    // 서버에 연결 요청
    if(connect(sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect() error");

    // 서버로부터 데이터를 읽어 파일에 저장
    while((read_cnt = read(sd, buf, BUF_SIZE)) != 0)
        fwrite((void*)buf, 1, read_cnt, fp);

    puts("Received file data");  // 데이터 수신 완료 메시지 출력
    // 서버에 "Thank you" 메시지 전송
    write(sd, "Thank you", 10);

    fclose(fp);  // 파일 닫기
    close(sd);  // 소켓 닫기
    return 0;
}

// 에러를 처리하는 함수
void error_handling(char *message)
{
    fputs(message, stderr);  // 에러 메시지를 표준 에러 출력에 출력
    fputc('\n', stderr);  // 표준 에러 출력에 개행 문자 출력
    exit(1);  // 프로그램을 비정상 종료
}
