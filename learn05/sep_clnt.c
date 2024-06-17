#include <stdio.h>      // 표준 입출력 함수를 사용하기 위한 헤더 파일
#include <stdlib.h>     // 표준 라이브러리 함수들을 사용하기 위한 헤더 파일
#include <string.h>     // 문자열 관련 함수들을 사용하기 위한 헤더 파일
#include <unistd.h>     // UNIX 표준 함수들을 사용하기 위한 헤더 파일
#include <arpa/inet.h>  // 인터넷 주소 변환 함수들을 사용하기 위한 헤더 파일
#include <sys/socket.h> // 소켓 관련 함수들을 사용하기 위한 헤더 파일

#define BUF_SIZE 1024   // 버퍼 크기를 1024바이트로 정의

int main(int argc, char *argv[])
{
    int sock;                      // 클라이언트 소켓을 가리키는 파일 디스크립터 변수
    char buf[BUF_SIZE];            // 데이터를 저장할 버퍼
    struct sockaddr_in serv_addr;  // 서버의 주소 정보를 담을 구조체 변수

    FILE *readfp;                  // 소켓을 읽기 모드로 사용할 파일 포인터
    FILE *writefp;                 // 소켓을 쓰기 모드로 사용할 파일 포인터
    
    // TCP 소켓 생성 (IPv4 인터넷 프로토콜, TCP)
    sock = socket(PF_INET, SOCK_STREAM, 0);

    // 주소 구조체 변수를 0으로 초기화
    memset(&serv_addr, 0, sizeof(serv_addr));
    // 주소 구조체 변수 설정 (IPv4, 서버 IP 주소, 포트 번호)
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
  
    // 서버에 연결 시도
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    // 소켓을 파일 포인터로 변환 (읽기 모드)
    readfp = fdopen(sock, "r");
    // 소켓을 파일 포인터로 변환 (쓰기 모드)
    writefp = fdopen(sock, "w");
  
    // 서버로부터 메시지를 읽어 표준 출력에 출력
    while(1)
    {
        if(fgets(buf, sizeof(buf), readfp) == NULL) 
            break;
        fputs(buf, stdout);
        fflush(stdout);
    }  

    // 서버로 메시지 전송
    fputs("FROM CLIENT: Thank you! \n", writefp);
    fflush(writefp);

    // 파일 포인터 닫기
    fclose(writefp); 
    fclose(readfp);
    
    return 0;
}

/*
이 프로그램은 클라이언트 역할을 수행하여 서버와 연결을 맺고 메시지를 주고받습니다.
1. 소켓을 생성합니다.
2. 서버 주소를 설정합니다.
3. 서버에 연결을 시도합니다.
4. 소켓을 파일 포인터로 변환하여 읽기와 쓰기 모드로 사용합니다.
5. 서버로부터 메시지를 읽어 표준 출력에 출력합니다.
6. 서버로 메시지를 전송합니다.
7. 파일 포인터를 닫습니다.
*/
