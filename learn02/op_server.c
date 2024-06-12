#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024 // 버퍼 크기 정의
#define OPSZ 4 // 피연산자 크기 정의
void error_handling(char *message); // 에러 처리 함수 선언
int calculate(int opnum, int opnds[], char oprator); // 계산 함수 선언

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock; // 서버와 클라이언트 소켓 파일 디스크립터
    char opinfo[BUF_SIZE]; // 클라이언트로부터 받은 연산 정보를 저장할 버퍼
    int result, opnd_cnt, i; // 연산 결과, 피연산자 개수, 반복 변수
    int recv_cnt, recv_len; // 수신한 데이터의 길이와 수신한 바이트 수
    struct sockaddr_in serv_adr, clnt_adr; // 서버와 클라이언트 주소 정보를 담을 구조체
    socklen_t clnt_adr_sz; // 클라이언트 주소 구조체 크기

    // 프로그램 실행 시 포트 번호를 인자로 받지 않은 경우 사용법 출력 후 종료
    if(argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    
    // 서버 소켓 생성 (IPv4, TCP)
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);   
    if(serv_sock == -1)
        error_handling("socket() error");
    
    // 서버 주소 구조체 초기화 및 설정
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET; // IPv4
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY); // 모든 IP 주소에서 연결 허용
    serv_adr.sin_port = htons(atoi(argv[1])); // 입력받은 포트 번호

    // 소켓에 주소 할당
    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    
    // 연결 요청 대기
    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");    
    clnt_adr_sz = sizeof(clnt_adr);

    // 5명의 클라이언트와의 연결을 처리
    for(i = 0; i < 5; i++)
    {
        opnd_cnt = 0;
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz); // 연결 수락
        read(clnt_sock, &opnd_cnt, 1); // 피연산자 개수 수신
        
        recv_len = 0;
        while((opnd_cnt * OPSZ + 1) > recv_len) // 모든 연산 정보를 수신할 때까지 반복
        {
            recv_cnt = read(clnt_sock, &opinfo[recv_len], BUF_SIZE - 1);
            recv_len += recv_cnt;
        }
        // 연산 수행 및 결과 전송
        result = calculate(opnd_cnt, (int*)opinfo, opinfo[recv_len - 1]);
        write(clnt_sock, (char*)&result, sizeof(result));
        close(clnt_sock); // 클라이언트 소켓 닫기
    }
    close(serv_sock); // 서버 소켓 닫기
    return 0;
}

// 연산을 수행하는 함수
int calculate(int opnum, int opnds[], char op)
{
    int result = opnds[0], i;
    
    switch(op)
    {
    case '+':
        for(i = 1; i < opnum; i++) result += opnds[i];
        break;
    case '-':
        for(i = 1; i < opnum; i++) result -= opnds[i];
        break;
    case '*':
        for(i = 1; i < opnum; i++) result *= opnds[i];
        break;
    }
    return result;
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수 정의
void error_handling(char *message)
{
    fputs(message, stderr); // 에러 메시지 출력
    fputc('\n', stderr);
    exit(1); // 프로그램 종료
}
