#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#define BUF_SIZE 30
void error_handling(char *message); // 에러 메시지를 출력하고 프로그램을 종료하는 함수 선언
void urg_handler(int signo); // 긴급 메시지를 처리하는 시그널 핸들러 함수 선언

int acpt_sock; // 클라이언트 연결을 수락하는 소켓
int recv_sock; // 데이터 수신을 위한 소켓

int main(int argc, char *argv[])
{
	struct sockaddr_in recv_adr, serv_adr;
	int str_len, state;
	socklen_t serv_adr_sz;
	struct sigaction act;
	char buf[BUF_SIZE];

	if(argc!=2) {
		// 인자(argument)가 부족할 경우 사용법 출력 후 프로그램 종료
		printf("Usage : %s <port>\n", argv[0]); 
		exit(1);	
	}
	
	act.sa_handler = urg_handler; // 긴급 메시지를 처리하는 핸들러 설정
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0; 
	
	acpt_sock = socket(PF_INET, SOCK_STREAM, 0); // TCP 소켓 생성
	memset(&recv_adr, 0, sizeof(recv_adr)); // recv_adr 구조체를 0으로 초기화
	recv_adr.sin_family = AF_INET; // 주소 체계를 IPv4로 설정
	recv_adr.sin_addr.s_addr = htonl(INADDR_ANY); // 모든 IP로부터의 연결을 허용
	recv_adr.sin_port = htons(atoi(argv[1])); // 포트 번호 설정

	if(bind(acpt_sock, (struct sockaddr*)&recv_adr, sizeof(recv_adr)) == -1)
		// 소켓에 주소 할당
		error_handling("bind() error");
	listen(acpt_sock, 5); // 연결 대기열을 5로 설정

	serv_adr_sz = sizeof(serv_adr);
	recv_sock = accept(acpt_sock, (struct sockaddr*)&serv_adr, &serv_adr_sz); // 클라이언트 연결 수락
	
	fcntl(recv_sock, F_SETOWN, getpid()); // 현재 프로세스를 소켓의 소유자로 설정
	state = sigaction(SIGURG, &act, 0); // SIGURG 시그널을 urg_handler로 처리하도록 설정
	
	while((str_len = recv(recv_sock, buf, sizeof(buf), 0)) != 0) // 데이터 수신
	{
		if(str_len == -1)
			continue;
		buf[str_len] = 0;
		puts(buf); // 수신한 데이터 출력
	}
	close(recv_sock); // 데이터 수신 소켓 닫기
	close(acpt_sock); // 연결 수락 소켓 닫기
	return 0; 
}

void urg_handler(int signo)
{
	int str_len;
	char buf[BUF_SIZE];
	str_len = recv(recv_sock, buf, sizeof(buf)-1, MSG_OOB); // 긴급 데이터 수신
	buf[str_len] = 0;
	printf("Urgent message: %s \n", buf); // 긴급 메시지 출력
}

void error_handling(char *message)
{
	fputs(message, stderr); // 에러 메시지 출력
	fputc('\n', stderr); // 개행 문자 출력
	exit(1); // 프로그램 종료
}
