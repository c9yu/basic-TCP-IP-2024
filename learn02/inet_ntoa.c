#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in addr1, addr2;  // 두 개의 sockaddr_in 구조체를 선언합니다.
    char *str_ptr;  // 문자열 포인터를 선언합니다.
    char str_arr[20];  // 문자열 배열을 선언합니다.

    // addr1과 addr2에 각각 0x1020304와 0x1010101 값을 네트워크 바이트 순서로 저장합니다.
    addr1.sin_addr.s_addr = htonl(0x1020304);
    addr2.sin_addr.s_addr = htonl(0x1010101);
    
    // addr1의 IP 주소를 점-십진수 표기법으로 변환하고 str_ptr가 가리키도록 합니다.
    str_ptr = inet_ntoa(addr1.sin_addr);
    // str_ptr가 가리키는 문자열을 str_arr에 복사합니다.
    strcpy(str_arr, str_ptr);
    // str_ptr가 가리키는 문자열을 출력합니다.
    printf("Dotted-Decimal notation1: %s \n", str_ptr);
    
    // addr2의 IP 주소를 점-십진수 표기법으로 변환합니다.
    // inet_ntoa 함수는 정적으로 할당된 버퍼를 사용하기 때문에 이전의 값이 덮어쓰여집니다.
    inet_ntoa(addr2.sin_addr);
    // str_ptr가 가리키는 현재 문자열을 출력합니다. (이 문자열은 addr2의 IP 주소입니다.)
    printf("Dotted-Decimal notation2: %s \n", str_ptr);
    // str_arr에 저장된 문자열을 출력합니다. (이 문자열은 addr1의 초기 IP 주소입니다.)
    printf("Dotted-Decimal notation3: %s \n", str_arr);
    
    return 0;
}

/*
root@com:/home/swyoon/tcpip# gcc inet_ntoa.c -o ntoa
root@com:/home/swyoon/tcpip# ./ntoa
Dotted-Decimal notation1: 1.2.3.4 
Dotted-Decimal notation2: 1.1.1.1 
Dotted-Decimal notation3: 1.2.3.4 
*/

/*
주석 설명:
inet_ntoa 함수는 내부적으로 정적으로 할당된 버퍼를 사용하여 IP 주소를 문자열로 변환합니다.
따라서 이 함수가 호출될 때마다 같은 버퍼가 사용되어 이전 값이 덮어쓰여집니다.
코드에서 str_ptr와 str_arr의 값을 확인해보면, 두 번째 inet_ntoa 호출 이후 str_ptr는
새로운 IP 주소 문자열을 가리키지만, str_arr는 여전히 복사된 첫 번째 IP 주소 문자열을 가리킵니다.
이러한 특성 때문에 두 번째 inet_ntoa 호출 후 str_ptr가 가리키는 값은 변경되지만
str_arr는 변경되지 않습니다.
*/
