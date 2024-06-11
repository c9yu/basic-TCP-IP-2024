#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    unsigned short host_port = 0x1234; 
    // 호스트 바이트 순서의 포트 번호 (16비트)
    unsigned short net_port; 
    // 네트워크 바이트 순서의 포트 번호를 저장할 변수
    unsigned long host_addr = 0x12345678; 
    // 호스트 바이트 순서의 IP 주소 (32비트)
    unsigned long net_addr; 
    // 네트워크 바이트 순서의 IP 주소를 저장할 변수

    // htons 함수를 사용하여 호스트 바이트 순서의 포트 번호를 네트워크 바이트 순서로 변환
    net_port = htons(host_port);
    // htonl 함수를 사용하여 호스트 바이트 순서의 IP 주소를 네트워크 바이트 순서로 변환
    net_addr = htonl(host_addr);

    // 결과 출력
    printf("Host ordered port: %#x \n", host_port); 
    // 호스트 바이트 순서의 포트 번호 출력
    printf("Network ordered port: %#x \n", net_port); 
    // 네트워크 바이트 순서의 포트 번호 출력
    printf("Host ordered address: %#lx \n", host_addr); 
    // 호스트 바이트 순서의 IP 주소 출력
    printf("Network ordered address: %#lx \n", net_addr); 
    // 네트워크 바이트 순서의 IP 주소 출력

    return 0;
}
