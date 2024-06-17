#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 30
void error_handling(char *message); // 에러 메시지를 출력하고 프로그램을 종료하는 함수 선언

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in recv_adr;

	if(argc!=3) {
		// 인자(argument)가 부족할 경우 사용법 출력 후 프로그램 종료
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	 }

	sock=socket(PF_INET, SOCK_STREAM, 0); // TCP 소켓 생성
	memset(&recv_adr, 0, sizeof(recv_adr)); // recv_adr 구조체를 0으로 초기화
	recv_adr.sin_family=AF_INET; // 주소 체계를 IPv4로 설정
	recv_adr.sin_addr.s_addr=inet_addr(argv[1]); // IP 주소 설정
	recv_adr.sin_port=htons(atoi(argv[2])); // 포트 번호 설정

	if(connect(sock, (struct sockaddr*)&recv_adr, sizeof(recv_adr))==-1)
		// 서버에 연결 요청
		error_handling("connect() error!"); // 연결 실패 시 에러 메시지 출력

	write(sock, "123", strlen("123")); // 일반 데이터 전송
	send(sock, "4", strlen("4"), MSG_OOB); // 긴급 데이터 전송
	write(sock, "567", strlen("567")); // 일반 데이터 전송
	send(sock, "890", strlen("890"), MSG_OOB); // 긴급 데이터 전송
	close(sock); // 소켓 닫기
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr); // 에러 메시지 출력
	fputc('\n', stderr); // 개행 문자 출력
	exit(1); // 프로그램 종료
}
