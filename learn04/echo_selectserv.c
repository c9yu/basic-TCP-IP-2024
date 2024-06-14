#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE 100
void error_handling(char *buf);  // 에러 핸들링 함수 선언

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    struct timeval timeout;
    fd_set reads, cpy_reads;

    socklen_t adr_sz;
    int fd_max, str_len, fd_num, i;
    char buf[BUF_SIZE];

    // 사용법을 잘못 입력한 경우
    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    // 서버 소켓 생성
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;  // 주소 체계 설정
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);  // 모든 IP로부터 연결 허용
    serv_adr.sin_port = htons(atoi(argv[1]));  // 포트 번호 설정

    // 소켓 바인딩
    if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    // 소켓 리슨
    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    FD_ZERO(&reads);  // reads 셋 초기화
    FD_SET(serv_sock, &reads);  // 서버 소켓을 reads 셋에 추가
    fd_max = serv_sock;  // fd_max 값을 서버 소켓으로 설정

    while (1)
    {
        cpy_reads = reads;  // cpy_reads 셋을 reads 셋으로 초기화
        timeout.tv_sec = 5;  // 타임아웃을 5초로 설정
        timeout.tv_usec = 5000;  // 타임아웃의 마이크로초 부분을 5000으로 설정

        // 파일 디스크립터 감시
        if ((fd_num = select(fd_max + 1, &cpy_reads, 0, 0, &timeout)) == -1)
            break;

        if (fd_num == 0)  // 타임아웃이 발생한 경우
            continue;

        for (i = 0; i < fd_max + 1; i++)
        {
            if (FD_ISSET(i, &cpy_reads))  // 파일 디스크립터 i가 설정되었는지 확인
            {
                if (i == serv_sock)  // 새로운 연결 요청이 있는 경우
                {
                    adr_sz = sizeof(clnt_adr);
                    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);  // 클라이언트 연결 수락
                    FD_SET(clnt_sock, &reads);  // 클라이언트 소켓을 reads 셋에 추가
                    if (fd_max < clnt_sock)
                        fd_max = clnt_sock;  // fd_max 값을 클라이언트 소켓으로 갱신
                    printf("connected client: %d \n", clnt_sock);
                }
                else  // 데이터 수신이 있는 경우
                {
                    str_len = read(i, buf, BUF_SIZE);  // 클라이언트로부터 데이터 읽기
                    if (str_len == 0)  // 연결이 종료된 경우
                    {
                        FD_CLR(i, &reads);  // reads 셋에서 파일 디스크립터 제거
                        close(i);  // 소켓 닫기
                        printf("closed client: %d \n", i);
                    }
                    else
                    {
                        write(i, buf, str_len);  // 클라이언트로 데이터 에코
                    }
                }
            }
        }
    }
    close(serv_sock);  // 서버 소켓 닫기
    return 0;
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void error_handling(char *buf)
{
    fputs(buf, stderr);
    fputc('\n', stderr);
    exit(1);
}
