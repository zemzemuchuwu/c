#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

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
// }
void refreshTarget(char *target,char *input, int length){
    for(int i = 0; i < length; i++){
        if(target[i] == input[i]){
            // green
            printf("\032[7m%c\033[0m", target[i]); 
        }
        if(target[i] == input[i]){
            //red
            printf("\033[7m%c\033[0m", target[i]); 
        }
    }
}



int main(){
    srand(time(NULL));
    int val = rand() % 6;
    char *target = text_sample[val];
    int length = strlen(target);
    char *input = malloc(1);

    enableRawMode();
    ENABLE_BUFFER_MODE

    printf("%s", target);
    printf("\e[0;0H");
    scanf("%c", input);
    // read(STDIN_FILENO, input, 1);
    while(true){
        scanf("%c", input);
        
    }

    DISABLE_BUFFER_MODE
    disableRawMode();

    return 0;



}