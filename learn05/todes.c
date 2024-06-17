#include <stdio.h>
#include <fcntl.h>  // 파일 제어를 위한 헤더 파일

int main(void)
{
   FILE *fp;  // 파일 포인터 선언
   int fd = open("data.dat", O_WRONLY | O_CREAT | O_TRUNC);  // 파일 열기

   if (fd == -1) {  // 파일 열기 실패 시 오류 처리
      fputs("file open error", stdout);  // 오류 메시지 출력
      return -1;  // 프로그램 종료
   }
   
   printf("First file descriptor: %d \n", fd);  // 첫 번째 파일 디스크립터 출력
   fp = fdopen(fd, "w");  // 파일 디스크립터를 파일 포인터로 변환하여 파일 열기
   fputs("TCP/IP SOCKET PROGRAMMING \n", fp);  // 파일 포인터를 사용하여 문자열 쓰기
   printf("Second file descriptor: %d \n", fileno(fp));  // 두 번째 파일 디스크립터 출력 (파일 포인터를 파일 디스크립터로 변환하여 출력)
   fclose(fp);  // 파일 포인터 닫기 (파일도 함께 닫힘)
   
   return 0;  // 프로그램 정상 종료
}
#include <stdio.h>
#include <fcntl.h>  // 파일 제어를 위한 헤더 파일

int main(void)
{
   FILE *fp;  // 파일 포인터 선언
   int fd = open("data.dat", O_WRONLY | O_CREAT | O_TRUNC);  // 파일 열기

   if (fd == -1) {  // 파일 열기 실패 시 오류 처리
      fputs("file open error", stdout);  // 오류 메시지 출력
      return -1;  // 프로그램 종료
   }
   
   printf("First file descriptor: %d \n", fd);  // 첫 번째 파일 디스크립터 출력
   fp = fdopen(fd, "w");  // 파일 디스크립터를 파일 포인터로 변환하여 파일 열기
   fputs("TCP/IP SOCKET PROGRAMMING \n", fp);  // 파일 포인터를 사용하여 문자열 쓰기
   printf("Second file descriptor: %d \n", fileno(fp));  // 두 번째 파일 디스크립터 출력 (파일 포인터를 파일 디스크립터로 변환하여 출력)
   fclose(fp);  // 파일 포인터 닫기 (파일도 함께 닫힘)
   
   return 0;  // 프로그램 정상 종료
}
