#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define ENABLE_BUFFER_MODE printf("\e[?1049h");
#define DISABLE_BUFFER_MODE printf("\e[?1049l");

    char *text_sample[] = {
        "The sun set behind the mountains, casting a golden hue across the valley\0",
        "As the rain fell softly, the sound created a soothing melody in the quiet room\0",
        "She discovered an old book in the attic, its pages filled with forgotten tales of adventure\0",
        "The scent of freshly baked bread wafted through the air, drawing the neighbors outside\0",
        "A cat lounged lazily on the windowsill, basking in the warmth of the afternoon sun\0",
        "He stared at the starry sky, wondering about the mysteries of the universe beyond\0",
        "With a determined heart, she decided to explore the uncharted paths of the forest\0"
    };

    struct Pos{
        int x;
        int y;
    };

    struct Pos pos = {0, 0};

    struct buf{
        char* buf;
        int len;
    }typedef Buf;

    struct winsize w;

    char name[] = "spellcheck\0";

// function to disable canonical mode and echo
void enableRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

// function to enable canonical mode and echo
void disableRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

// void Read(input){
//         read(0, input, 1);
// }{

void append (Buf* buf, char* str, int size)
{   
    int i = buf->len;
    buf->len = buf->len + size;

    buf->buf = (char*)realloc(buf->buf, buf->len);
    for(int j=0; j < size; j++, i++){
        buf->buf[i] = str[j];
    }
}
void drawTop(Buf* buf){
    int i = 0;

    buf->buf = (char*)realloc(buf->buf, ((w.ws_col/2) - 5));
    buf->len += (w.ws_col/2) - 5;
    for(; i < ((w.ws_col/2) - 5); i++){
        buf->buf[i] = ' ';
        
    }
    append (buf, name, 10);
    i += 10;

    buf->len += (w.ws_col/2) - 5;
    buf->buf = (char*)realloc(buf->buf, buf->len);
    for(; i < ((w.ws_col)); i++){
        buf->buf[i] = ' ';
        
    }
}

void drawBody(Buf* buf, char* target){
    append(buf, target, strlen(target));
    for(int i = 0; i < buf->len; i++){
        append(buf, " ", 1);
    }
}



// void changeStr(char* buf.buf, char* input, int *i){
//     char temp1[] = "\e[32m";
//     char temp2[] = "\e[0m";
//     char temp3[] = "\e[31m";
//     if(buf.buf[*i] == *input){
//         strcat(temp1, input);
//         strcat(temp1, temp2);
//         buf.buf[*i] = *temp1;
//         *i = *i + strlen(temp1);
//     }
//     else {
//         strcat(temp3, input);
//         strcat(temp3, temp2);
//         buf.buf[*i] = *temp3;   
//         *i = *i + strlen(temp3);
//     }
// }



void refreshTarget(char *target, char *input, int x, int y, bool *init){
    // printf("\e[0;%dH", (len/2));
    // printf("spellcheck");

    struct buf buf = {0, 0};
    drawTop(&buf);
    drawBody(&buf, target);
    // if(init == false){
    //     printf("\e[1;2H");
    // }
    // if(init){
    //     changeStr(buf.buf, input, &size);
    //     printf("\e[%d;%dH", )
    // }
    // *init = true;
    write(1, buf.buf, buf.len);

    free(buf.buf);

   


}



int main(){
    srand(time(NULL));
    int val = rand() % 6;
    char *target = text_sample[val];
    char *input = malloc(1);
    bool init = false;

    // printf("%d\n%d", w.ws_col, w.ws_row);
    // system("clear");

    enableRawMode();
    // ENABLE_BUFFER_MODE

    // printf("%s", target);
    printf("\e[0;0H");
    // scanf("%c", input);
    // read(STDIN_FILENO, input, 1);
    while(true){
        
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
            perror("ioctl");
            exit(EXIT_FAILURE);
        }

        
        refreshTarget( target, input, w.ws_col, w.ws_row, &init);
        sleep(5);
    }
    DISABLE_BUFFER_MODE
    disableRawMode();

    return 0;



}


