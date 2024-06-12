#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024 // 버퍼 크기 정의
#define RLT_SIZE 4 // 결과 크기 정의
#define OPSZ 4 // 피연산자 크기 정의
void error_handling(char *message); // 에러 처리 함수 선언

int main(int argc, char *argv[])
{
    int sock; // 클라이언트 소켓 파일 디스크립터
    char opmsg[BUF_SIZE]; // 서버에 보낼 메시지를 저장할 버퍼
    int result, opnd_cnt, i; // 결과 값, 피연산자 개수, 반복 변수
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

    // 피연산자 개수 입력 받기
    fputs("Operand count: ", stdout);
    scanf("%d", &opnd_cnt);
    opmsg[0] = (char)opnd_cnt;
    
    // 각 피연산자 값을 입력 받고 버퍼에 저장
    for(i = 0; i < opnd_cnt; i++)
    {
        printf("Operand %d: ", i + 1);
        scanf("%d", (int*)&opmsg[i * OPSZ + 1]);
    }
    fgetc(stdin); // 개행 문자 제거
    // 연산자 입력 받기
    fputs("Operator: ", stdout);
    scanf("%c", &opmsg[opnd_cnt * OPSZ + 1]);
    
    // 서버에 메시지 전송
    write(sock, opmsg, opnd_cnt * OPSZ + 2);
    
    // 서버로부터 결과 수신
    read(sock, &result, RLT_SIZE);
    
    // 결과 출력
    printf("Operation result: %d \n", result);
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
