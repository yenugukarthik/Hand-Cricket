#include <stdint.h>
#include <stdlib.h> 
#include<time.h>
#include<string.h>

#define SW_BASE				0xFF200040
volatile int * KEY_ptr = (int *) 0xFF200050;       // pushbutton KEY address

# define multiplier 122345676
	#define increment 12345
unsigned int seed  = 0 ;	
int random (){
		
		seed = (multiplier*seed + increment) % 234533;
		return seed;

}

int switches(){
    volatile int *SW_switch_ptr = (int *)SW_BASE;
    int SW_value = *(SW_switch_ptr);
    int a=0;
    if(SW_value & 0x1){
        a=0;
    }
    if(SW_value & 0x2){
        a=1;
    }
    if(SW_value & 0x4){
        a=2;
    }
    if(SW_value & 0x8){
        a=3;
    }
    if(SW_value & 0x10){
        a=4;
    }
    if(SW_value & 0x20){
        a=5;
    }
    if(SW_value & 0x40){
        a=6;
    }
    return a;
}

void write_digit(int x,int y,int d){
    char l='0';
    if(d==1)l='1';
    if(d==2)l='2';
    if(d==3)l='3';
    if(d==4)l='4';
    if(d==5)l='5';
    if(d==6)l='6';
    if(d==7)l='7';
    if(d==8)l='8';
    if(d==9)l='9';
    write_char(x,y,l);
}
void write_pixel(int x , int y , int color){
    volatile short *vga_addr = (volatile short *)(0x08000000 + (y << 10) + (x << 1));
    *vga_addr = color;
}

void write_char(int x, int y, char c)
{
    // VGA character buffer
    volatile char *character_buffer = (char *)(0x09000000 + (y << 7) + x);
    *character_buffer = c;
}

void clear_display(){
    // Clear pixel data
    for(int x = 0; x < 320 ; x++) {
        for(int y = 0; y < 240 ; y++) {
            write_pixel(x, y, 0);
        }
    }
    // Clear text area
    for(int x = 0; x < 80 ; x++) {
        for(int y = 0; y < 60 ; y++) {    
            volatile char * char_buffer = (char*)(0x09000000 + (y << 7) + x);
            *char_buffer = 0; // Clear character
        }
    }
}

void clear_screen(){
    for(int x = 0; x < 320 ; x++) {
        for(int y = 0; y < 240 ; y++) {
            write_pixel(x, y, 0);
        }
    }
}

void clear_image(){
    for(int x = 80; x < 240 ; x++) {
        for(int y = 60; y < 180 ; y++) {
            write_pixel(x, y, 0);
        }
    }
}

void write_int(int x,int y,int in){
    int k=in;
    int xc=x;
    if(in==0){
        write_digit(x,y,0);
        return;
    }
    while(k){
        int t=k%10;
        k=k/10;
        write_digit(xc,y,t);
        xc--;
    }
}
void head(){
    clear_image();
    for(int x = 100; x < 220 ; x++){
        write_pixel(x,60,0xFFFFFF);
        write_pixel(x,61,0xFFFFFF);
        write_pixel(x,62,0xFFFFFF);
        write_pixel(x,179,0xFFFFFF);
        write_pixel(x,178,0xFFFFFF);
        write_pixel(x,177,0xFFFFFF);
    }
    for(int y = 60; y < 180 ; y++){
        write_pixel(100,y,0xFFFFFF);
        write_pixel(102,y,0xFFFFFF);
        write_pixel(101,y,0xFFFFFF);
        write_pixel(219,y,0xFFFFFF);
        write_pixel(218,y,0xFFFFFF);
        write_pixel(217,y,0xFFFFFF);
    }
    for(int y = 80; y < 160 ; y++){
        for(int i=0;i<8;i++){
            write_pixel(130+i,y,0xFFFFFF);
            write_pixel(190-i,y,0xFFFFFF);
        }
    }
    for(int x = 130; x < 190 ; x++){
        for(int y = 117; y < 124 ; y++){
             write_pixel(x, y, 0xFFFFFF);
        }
    }
}

void write_string(int x, int y, char s[]){
    int i;
    int xc=x;
    for ( i = 0; i < strlen(s); i++)
    {
        write_char(x, y, s[i]);
        x++;
    }
}

void tail(){
    clear_image();
    for(int x = 100; x < 220 ; x++){
        write_pixel(x,60,0xFFFFFF);
        write_pixel(x,61,0xFFFFFF);
        write_pixel(x,62,0xFFFFFF);
        write_pixel(x,179,0xFFFFFF);
        write_pixel(x,178,0xFFFFFF);
        write_pixel(x,177,0xFFFFFF);
    }
    for(int y = 60; y < 180 ; y++){
        write_pixel(100,y,0xFFFFFF);
        write_pixel(102,y,0xFFFFFF);
        write_pixel(101,y,0xFFFFFF);
        write_pixel(219,y,0xFFFFFF);
        write_pixel(218,y,0xFFFFFF);
        write_pixel(217,y,0xFFFFFF);
    }
    for(int y = 80; y < 160 ; y++){
        for(int x=157;x<164;x++){
           write_pixel(x, y, 0xFFFFFF);
        }
    }
    for(int x = 130; x < 190 ; x++){
        for(int y = 80; y < 88 ; y++){
             write_pixel(x, y, 0xFFFFFF);
        }
    }
}

void write_seg(int score){
    int score_2=score/10;
    int score_1=score%10;
    
char seg7[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x40};
volatile int * HEX5_4_ptr = (volatile int *) 0xFF200030; // HEX5_HEX4 address
*(HEX5_4_ptr) = seg7[score_1 & 0xF] | seg7[score_2 & 0xF] << 8 | seg7[16] << 16;
}


int main(){
    clear_display();

    char wel[]="super over";
    write_string(35,10,wel);
    char str[]="For heads chose switch 1 for tails switch 0";
    write_string(10,40,str);
    char str1[]="after choosing the switch press 0 button";
    write_string(10,42,str1);
    int k=0;
    while(1){
        if (*KEY_ptr != 0){
            k=switches();
            break;
        }
    }
    clear_display();
    if(k==0){
        char str2[]="tails is the call";
        write_string(25,10,str2);
        }else{
        char str2[]="heads is the call";
        write_string(25,10,str2);
    }
    
        for(int i=0;i<30;i++){
            head();
            for(int j=0;j<1000000;j++){
                j++;
            }
            tail();
            for(int j=0;j<1000000;j++){
                j++;
            }
        }
    clear_display();
    int toss=random();
    toss%=2;
    int tw=0;
    if(toss==k){
        char str2[]="u won the toss ";
        char str3[]="you will get all ten wickets for chasing the score";
        write_string(25,8,str2);
        write_string(15,10,str3);
        tw=1;
    }else{
        char str2[]="u lost the toss ";
        char str3[]="you will get only one wicket to chase the score";
        write_string(25,8,str2);
        write_string(15,10,str3);
    }

    if(toss==1){
        head();
    }else{
        tail();
    }

    char but[]="press the button zero to continue";
    write_string(10,50,but);

    while(1){
        if (*KEY_ptr != 0){
            break;
        }
    }
    
        clear_display();
        int target=(random()%10)+12;
        write_int(10,10,target);
        char trg[]="is the target you are going to chase";
        char ins[]="instructions for batting";
        char ins1[]="you will get 6 deliveries to chase the given target";
        char ins2[]="for each delivery you have to chose switch between 0 and 6";
        char ins3[]="the computer bowls to u with some random number between 0 and 6";
        char ins4[]="if you and  computer chooses same number you will be out";
        char ins5[]="in all other cases the number you chose will be added to your score";
        write_string(11,10,trg);
        write_string(10,12,ins);
        write_string(10,16,ins1);
        write_string(10,18,ins2);
        write_string(10,20,ins3);
        write_string(10,22,ins4);
        write_string(10,24,ins5);
    for(int j=0;j<1000000000;j++){
                j++;
            }
    int score =0;
        char but1[]="press the button zero to continue";
        write_string(10,50,but1);
        int off=1;
        while(1){
        if (*KEY_ptr != 0){
            int off=0;
            break;
        }
    }
    int outf=0;
    clear_display();
    for(int i=0;i<=6;i++){
        char sc[]="score :";
        write_string(5,5,sc);
        char del[]="delivery :";
        write_string(60,5,del);
        write_int(14,5,score);
        write_digit(70,5,i);

        while(1){
            if (*KEY_ptr != 0 && off){
            k=switches();
            off=0;
            break;
        }
        if (*KEY_ptr == 0 )off=1;
        }

        int de=random()%7;

        for(int i=0;i<30000000;i++){
            i++;
        }

        if(de == k){
            if(tw==0){
                outf=1;
            }
            char cur[]="u scored";
            if(i!=0)write_string(10,25,cur);
            if(i!=0)write_digit(19,25,0);
            char cur2[]="in previous delivery";
            if(i!=0)write_string(21,25,cur2);
        }else{
            score+=k;
            char cur[]="u scored";
            if(i!=0)write_string(10,25,cur);
            if(i!=0)write_digit(19,25,k);
            char cur2[]="in previous delivery";
            if(i!=0)write_string(21,25,cur2);
        }

        if(score >= target ){
            break;
        }
        char str4[]="for next deleviry choose the switch and press button zero";
        write_string(10,45,str4);
        write_seg(score);
}

clear_display();    
    if(outf){
        char out[]="u got out";
        write_string(35,10,out);
    }

    if(score>=target){
        char won[]="you won";
        write_string(36,10,won);
    }else{
        char won[]="you lost";
        write_string(36,10,won);
    }


    char score2[]="your score";
    write_string(10,40,score2);
    write_int(22,40,score);
    char score1[]="target";
    write_string(60,40,score1);
    write_int(68,40,target);
}


/*if (*KEY_ptr != 0){
            k=switches();
            break;
        }*/