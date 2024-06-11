#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    char *addr1 = "127.212.124.78"; // 올바른 IPv4 주소
    char *addr2 = "127.212.124.256"; // 잘못된 IPv4 주소(최대 255까지)

    // inet_addr 함수를 사용하여 주어진 IPv4 주소를 네트워크 바이트 순서의 정수로 변환
    unsigned long conv_addr = inet_addr(addr1);
    // 변환 결과가 INADDR_NONE일 경우 오류가 발생했음을 출력
    if (conv_addr == INADDR_NONE)
        printf("Error occurred!\n");
    // 변환 결과가 정상적으로 반환된 경우 네트워크 바이트 순서의 정수를 출력
    else
        printf("Network ordered integer address: %#lx\n", conv_addr);
    
    // 잘못된 IPv4 주소에 대해서도 같은 과정을 반복
    conv_addr = inet_addr(addr2);
    if (conv_addr == INADDR_NONE)
        printf("Error occurred!\n");
    else
        printf("Network ordered integer address: %#lx\n\n", conv_addr);
    
    return 0;
}
