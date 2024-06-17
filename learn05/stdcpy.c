#include <stdio.h>      // 표준 입출력 함수를 사용하기 위한 헤더 파일
#define BUF_SIZE 3      // 버퍼 크기를 3바이트로 정의

int main(int argc, char* argv[])
{
    FILE *fp1;          // 입력 파일을 가리킬 파일 포인터
    FILE *fp2;          // 출력 파일을 가리킬 파일 포인터
    char buf[BUF_SIZE]; // 데이터를 저장할 버퍼

    // "news.txt" 파일을 읽기 모드로 열기
    fp1 = fopen("news.txt", "r");
    // "cpy.txt" 파일을 쓰기 모드로 열기, 파일이 없으면 생성, 기존 파일이 있으면 덮어쓰기
    fp2 = fopen("cpy.txt", "w");

    // "news.txt"에서 데이터를 읽어 "cpy.txt"에 쓰기
    while (fgets(buf, BUF_SIZE, fp1) != NULL)
        fputs(buf, fp2);

    // 파일 포인터 닫기
    fclose(fp1);
    fclose(fp2);

    return 0;
}
