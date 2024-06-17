#include <stdio.h>      // 표준 입출력 함수를 사용하기 위한 헤더 파일
#include <stdlib.h>     // 표준 라이브러리 함수들을 사용하기 위한 헤더 파일
#include <string.h>     // 문자열 관련 함수들을 사용하기 위한 헤더 파일
#include <unistd.h>     // UNIX 표준 함수들을 사용하기 위한 헤더 파일
#include <arpa/inet.h>  // 인터넷 주소 변환 함수들을 사용하기 위한 헤더 파일
#include <sys/socket.h> // 소켓 관련 함수들을 사용하기 위한 헤더 파일

#define BUF_SIZE 1024   // 버퍼 크기를 1024바이트로 정의

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;          // 서버와 클라이언트 소켓을 가리키는 파일 디스크립터 변수
    FILE * readfp;                     // 클라이언트 소켓을 읽기 모드로 사용할 파일 포인터
    FILE * writefp;                    // 클라이언트 소켓을 쓰기 모드로 사용할 파일 포인터
    
    struct sockaddr_in serv_adr, clnt_adr; // 서버와 클라이언트의 주소 정보를 담을 구조체 변수
    socklen_t clnt_adr_sz;             // 클라이언트 주소의 크기를 저장할 변수
    char buf[BUF_SIZE] = {0,};         // 데이터를 저장할 버퍼

    // TCP 소켓 생성 (IPv4 인터넷 프로토콜, TCP)
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);

    // 주소 구조체 변수를 0으로 초기화
    memset(&serv_adr, 0, sizeof(serv_adr));
    // 주소 구조체 변수 설정 (IPv4, 모든 IP 주소, 포트 번호)
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));
    
    // 소켓과 주소를 바인딩
    bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr));
    // 소켓을 수신 대기 상태로 설정 (최대 5개의 연결 대기열)
    listen(serv_sock, 5);
    clnt_adr_sz = sizeof(clnt_adr); 

    // 클라이언트의 연결 요청을 수락, 새로운 소켓 생성
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
    
    // 클라이언트 소켓을 파일 포인터로 변환 (읽기 모드)
    readfp = fdopen(clnt_sock, "r");
    // 클라이언트 소켓을 파일 포인터로 변환 (쓰기 모드)
    writefp = fdopen(dup(clnt_sock), "w");
    
    // 클라이언트로 메시지 전송
    fputs("FROM SERVER: Hi~ client? \n", writefp);
    fputs("I love all of the world \n", writefp);
    fputs("You are awesome! \n", writefp);
    fflush(writefp); // 버퍼를 비워 전송
    
    // 쓰기 소켓의 절반을 닫아 더 이상 데이터를 보낼 수 없도록 함
    shutdown(fileno(writefp), SHUT_WR);
    // 쓰기 파일 포인터 닫기
    fclose(writefp);
    
    // 클라이언트로부터 메시지 읽어 출력
    fgets(buf, sizeof(buf), readfp);
    fputs(buf, stdout); 
    // 읽기 파일 포인터 닫기
    fclose(readfp);
    return 0;
}

/*
실행 예시:
swyoon@my_linux:~/tcpip$ gcc sep_serv2.c -o serv2
swyoon@my_linux:~/tcpip$ ./serv2 9190
FROM CLIENT: Thank you! 
*/
