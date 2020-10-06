/*============================*
 *======= Jan Zboril =========*
 *jan.zboril@stud.fit.vutbr.cz*
 *===== PROJECT 1, IZP =======*
 *=== PHONE CONTACT LIST =====*
 *====== FIT BUT BRNO ========*
 *=========== 2019 ===========*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//function for changing uppercase to lowercase
void f_jmeno_lowercase(char jmeno[],int delka_jmena){
    int index = 0;
    for(index=0;index<delka_jmena;index++){
        if((jmeno[index]>='A') && (jmeno[index]<='Z')){ //if the letter is uppercase
            jmeno[index] = jmeno[index] + 32; //changing to lowercase - 32 due to ASCII
        }
    }
}

//simple function for writing errors
int chyba(){
    fprintf(stderr, "Chyba");
    exit(0);
}

//function for comparing input list with argument
int f_porovnej(char *jmeno, char *cislo, char *argv){
    
    char znak;
    char porovnavaci[101]=""; // 101 stands for max lenght of input string
    char jmeno_vypis[101];
    int i;
    int delka_jmena;
    int counter=0;
    
    strcpy(jmeno_vypis,jmeno); //for keeping original string for final printf, due to changing string later
    
    if(strstr(cislo,argv)!=NULL){   //comparing argument with string cislo, if cislo includes argument, then list line is printed
        printf("%s %s.\n",jmeno, cislo);
        counter++; //more on line
    }
    else{
        delka_jmena=strlen(jmeno);
        // call function for changing uppercase to lowercase letters in string "jmeno"
        f_jmeno_lowercase(jmeno,delka_jmena);
        

        for(i=0;i<=delka_jmena;i++){    //one number represents multiple letters, this is coversion of letters to their specific numbers
            znak=jmeno[i];      //lazy to wite jemno[i] everywhere
            
            switch(znak){
                case 'a':
                case 'b':
                case 'c':
                    strcat(porovnavaci,"2");    //writing into string which is later compared with line of list. Same is repeated  to row no. 79
                    break;
                case 'd':
                case 'e':
                case 'f':
                    strcat(porovnavaci,"3");
                    break;
                case 'g':
                case 'h':
                case 'i':
                    strcat(porovnavaci,"4");
                    break;
                case 'j':
                case 'k':
                case 'l':
                    strcat(porovnavaci,"5");
                    break;
                case 'm':
                case 'n':
                case 'o':
                    strcat(porovnavaci,"6");
                    break;
                case 'p':
                case 'q':
                case 'r':
                case 's':
                    strcat(porovnavaci,"7");
                    break;
                case 't':
                case 'u':
                case 'v':
                    strcat(porovnavaci,"8");
                    break;
                case 'w':
                case 'x':
                case 'y':
                case 'z':
                    strcat(porovnavaci,"9");
                    break;
                case '+':
                    strcat(porovnavaci,"0");
                    break;
                case ' ':
                    strcat(porovnavaci," ");
                    break;
                default:
                    break;
            }
        }
        
        /*same thing as switch does can be written like this, using ifs:
        
            if((znak=='a')||(znak=='b')||(znak=='c')){
                strcat(porovnavaci,"2");    //writing into string which is later compared witch line of list. Same is repeated for other chars.
            }
            if((znak=='d')||(znak=='e')||(znak=='f')){
                strcat(porovnavaci,"3");
            }
            if((znak=='g')||(znak=='h')||(znak=='i')){
                strcat(porovnavaci,"4");
            }
            if((znak=='j')||(znak=='k')||(znak=='l')){
                strcat(porovnavaci,"5");
            }
            if((znak=='m')||(znak=='n')||(znak=='o')){
                strcat(porovnavaci,"6");
            }
            if((znak=='p')||(znak=='q')||(znak=='r')||(znak=='s')){
                strcat(porovnavaci,"7");
            }
            if((znak=='t')||(znak=='u')||(znak=='v')){
                strcat(porovnavaci,"8");
            }
            if((znak=='w')||(znak=='x')||(znak=='y')||(znak=='z')){
                strcat(porovnavaci,"9");
            }
            if(znak=='+'){
                strcat(porovnavaci,"0");
            }
            if(znak==' '){
                strcat(porovnavaci," ");
            }
        }*/
        
        if(strstr(porovnavaci,argv)!=NULL){ //if the string which is changed into numbers coresponds with argument, print line from the list
            printf("%s %s.\n",jmeno_vypis,cislo);
            counter++;
        }
    }
    return counter;
}


//loads contact from stdin
void f_nacti(char argv[1]){
    const int LIMIT_J=101; //one row in list can be max 100 characters long
    const int LIMIT_C=11; //phone number max lenght
    int i;
    int counter=0, counter_2=0;
    
    char jmeno[LIMIT_J];
    char cislo[LIMIT_C];
    
    while(fgets (jmeno, LIMIT_J, stdin)!=NULL ){    //loads one contact per iteration
            i=strlen(jmeno)-1;            //remove new line from string jmeno
            if(jmeno[i]=='\n'){
                jmeno[i]='\0';
            }
            
            fgets(cislo, LIMIT_C, stdin);          
            i=strlen(cislo)-1;            // remove new line from string cislo
            if(cislo[i]=='\n'){
                cislo[i]='\0';
            }
            
            if(cislo==NULL){
                chyba();
            }
            
            counter_2=f_porovnej(jmeno,cislo,argv);     //if there was no counter_2, then couter would rewrite with every iteration of f_porovnej.
            counter=counter+counter_2;
        }
        
    if(jmeno==NULL){
        chyba();
    }
    
    if(counter==0){     //if the contact is found, the the counter++, if the contact is not found, then counter=0, which prints "Not found".
        printf("Not found");
    }
    
    return;
}

int main(int argc,char *argv[]){
    
    //wrong argument
    if(argc != 2){
        chyba();
    }
    
    //for translation without error
    //argc=argc;
    
    f_nacti(argv[1]);

    return 0;
}
