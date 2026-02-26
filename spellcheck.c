#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

    char *text_sample[] = {
        "The sun set behind the mountains, casting a golden hue across the valley\0",
        "As the rain fell softly, the sound created a soothing melody in the quiet room\0",
        "She discovered an old book in the attic, its pages filled with forgotten tales of adventure\0",
        "The scent of freshly baked bread wafted through the air, drawing the neighbors outside\0",
        "A cat lounged lazily on the windowsill, basking in the warmth of the afternoon sun\0",
        "He stared at the starry sky, wondering about the mysteries of the universe beyond\0",
        "With a determined heart, she decided to explore the uncharted paths of the forest\0"
    };


// function to disable canonical mode and echo
void disableRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

// function to enable canonical mode and echo
void enableRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

void Read(input){
        read(0, input, 1);
}

int main(){
    enableRawMode();
    int val = rand() % (7);
    char *target = text_sample[val];
    char *input = malloc(sizeof(char));
    printf("\033[7m%s\033[0m", target);
    printf("\e[?1049h\e[50C");
    read(0, input, 1);
    printf("%c\n", *input);
    disableRawMode();
    return 0;



}