#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Lyric {
    int timeSec;

    // 메모리 모자르면 크기 줄여야함
    char lyric[100];
};

FILE* lyricsFile;
FILE equalizerFile;
int command = 0;
int inputStatus = -1;
int curTimeSec = 0;
int isPlaying = 0;
struct Lyric nowShowLyric, nextShowLyric;



void readLyric(int *timeSec, char *str) {
    // 가사를 한 줄 읽어온다.
    if (!feof(lyricsFile)) {
        fscanf(lyricsFile, "[%d]%[^\n]\n", timeSec, str);
    }
}

// 가사 파일에서 초 수 파싱
int parseLyric(char *str) {
    int i = 1, j = 0;
    char timeSec[4];
    while(str[i] != ']') {
        timeSec[i - 1] = str[i];
        i++;
    }
    timeSec[i - 1] = '\0';

    while(str[++i] != '\0') {
        str[j++] = str[i];
    }
    str[j] = '\0';
    return atoi(timeSec);
}

int main() {
    int menu;
    char fileName[3];
    printf("1.Ne-Yo\n");
    printf("2.Love Me Like You\n");
    printf("3.Sugar\n");
    printf("4.Last Christmas\n");
    printf("파일을 선택해주세요.");

    scanf("%d", &menu);
    fileName[0] = menu + '0';
    fileName[1] = '\0';
    lyricsFile = fopen(fileName, "r");

    readLyric(&nowShowLyric.timeSec, nowShowLyric.lyric);
    readLyric(&nextShowLyric.timeSec, nextShowLyric.lyric);
    printf("%s\n", nowShowLyric.lyric);

    while (!feof(lyricsFile)) {
        sleep(1);
        curTimeSec++;

        // 다음 가사 출력할 시간이 되었다면 다음 가사를 현재 가사로 옮겨오고, 다음 가사를 읽어들인다.
        if (curTimeSec == nextShowLyric.timeSec/* - 1*/) {
            nowShowLyric = nextShowLyric;

            readLyric(&nextShowLyric.timeSec, nextShowLyric.lyric);
            printf("%s\n", nowShowLyric.lyric);
        }
    }
    fclose(lyricsFile);

    isPlaying = 1;
    curTimeSec = 0;
}
