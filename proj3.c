/*          Jan Zboril
 *          xzbori20
 *          FIT VUT Brno
 *          IZP 2019/2020
 *          Projekt 3 - Pruchod bludistem
 *          14. 12. 2019 
 */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

///////////////////////////////////
// inicializace funkci

void f_vypis_help();
void f_chyba();
void f_load_dimension();
void f_ini_blud();
int f_load_blud();
int f_test_arg_test();
int f_test_arg_path();
int f_test_RC();
void free_map();

///////////////////////////////////
// struktura Map do ktere se nacita mapa bludiste

typedef struct {
  int rows;
  int cols;
  unsigned char *cells;
} Map;
Map mapa;

///////////////////////////////////
// soubor s mapou bludiste
FILE *soubor;

///////////////////////////////////
// funkce main spousti prislusne ukony podle zadaneho argumentu. Resi hlavne spravnost argmunetu, pro prehlednost nektere
// pokrocile vlastnosti argumentu kontroluji jine fuknce volane funkci main

int main(int argc, char **argv){
    
    //printf("debug>> pocet argumentu je %d\n",argc);
    
    if(argc==2 && 0==strcmp("--help",argv[1])){
        f_vypis_help();
        return 0;
    }
    else if(argc==3 && 0==strcmp("--test",argv[1])){
        int overeni=f_test_arg_test(argv[argc-1]);      //volani overovaci funkce
        if(overeni==1){                             //pokud overovaci funkce vrati 1 - problem, ukonceni programu s 1
            f_chyba();
            return 1;            
        }
        else{
//               888
//             DODELAT
//               888
            f_load_dimension(argv[argc-1]);     //pro nacteni velikosti pole a jeho inicializaci
            f_load_blud();
            printf("Valid");
            free_map();
            fclose(soubor);
            return 0;
            

        }

    }
    else if(argc==5 && (0==strcmp("--lpath",argv[1]) || 0==strcmp("--rpath",argv[1]))){
        int overeni = f_test_arg_path(argv[2],argv[3],argv[4]);
        if(overeni==1){                             //pokud overovaci funkce vrati 1 - problem, ukonceni programu s 1
            f_chyba();
            return 1;            
        }
        else{
            f_load_dimension(argv[argc-1]);     //pro nacteni velikosti pole a jeho inicializaci
            f_load_blud();                 //pro nacteni hodnot do bludiste
            free_map();
            fclose(soubor);
            return 0;
        }
    }
    else{
        f_chyba();
        return 1;
    }
    //printf("debug>> argument main %s\n",argv[argc-1]);
    return 0;
}

///////////////////////////////////
// uvolni pamet pro bunky mapy
void free_map(){
    free(mapa.cells);
    return;
}

///////////////////////////////////
// volano v pripade chyby
void f_chyba(){
    fprintf(stderr,"Chyba");
    return;
}

///////////////////////////////////
// funkce overujici, jestli argument pri zadani --test je spravny - 
// format zapisu, platny textovy soubor
int f_test_arg_test(char *arg){                 //overuje, ze argumet je soubor typu .txt
    char *string = strrchr(arg, '.');
        //hleda posledni . v retezci arg, pokud najde ok, pokud ne vraci NULL
    if( string != NULL )
{                      //pokud predchozi radek nasel
        int pravda=strcmp(string, ".txt");      //zkontroluj jestli to je .txt
        if(pravda==0)                           //jestli ano, vrat 0
        return 0;

    }
    return 1;                              //jestli cokoliv z predchozich selhalo, vrati 1
}
///////////////////////////////////
// funkce overujici, jestli argument pri zadani --lpath nebo --rpath je spravny - 
// format zapisu, platny textovy soubor
int f_test_arg_path(char *R,char *C,char *nazev_souboru){
    if(1==f_test_arg_test(nazev_souboru)){
        return 1;
    }
    if(1==f_test_RC(R)){
        return 1;
    }
    if(1==f_test_RC(C)){
        return 1;
    }
    else return 0;
}

///////////////////////////////////
// funkce overujici, jestli cislo je opravdu cislo nebo neni zaporne
int f_test_RC(char *cislo){
    int number;
    int chyba;
    //printf("%s\n",*string);           debugging print
    chyba=sscanf(cislo,"%d",&number);
    if(chyba!=1){
        return 1;               //sscanf return int with value of amount of successfull scans
    }
    if(number<0){
        return 1;               //sscanf return int with value of amount of successfull scans
    }
    //printf("%g\n",number);            debugging print  
    return 0;
}

///////////////////////////////////
// tiskne napovedu programu, nic vic
void f_vypis_help(){
    printf("Prijatelne argumenty:\n"
            "--help\n"
            "Vypise napovedu a ukonci program\n"
            "--test soubor.txt\n"
            "Vypise, jestli je tabulka v souboru platna a ukonci program\n"
            "--lpath R C soubor.txt\n"
            "Nacte tabulku Vypise policka pruchodu tabulkou. Vyprazdni pamet pro tabulku\n"
            "R C jsou cisla radku a sloupcu startovniho policka\n");
    return;
}

///////////////////////////////////
// funkce otevre soubor a nacte z nej pocet radku a sloupcu tabulky
// pote vola fuknci pro inicializaci bludiste
void f_load_dimension(char *nazev_souboru){
    
    //printf("debug>> f_load_dimension nazev souboru %s\n",nazev_souboru);
    char ccol,crow;
    int col,row;
    
    soubor = fopen(nazev_souboru,"r");
    
    if(soubor == NULL){
        f_chyba();
        return;
    }
    else{
       ccol = fgetc(soubor);    //nacitani ze souboru
       crow = fgetc(soubor);        //je dvakrat protoze mezera
       crow = fgetc(soubor);
       
       //printf("debug>> radky sloupce %c %c\n",ccol,crow);
       
       col = (int)ccol-'0';     //prevod z char na int
       row = (int)crow-'0';
       
       //printf("debug>> radky sloupce %d %d\n",col,row);
       mapa.cols=col;
       mapa.rows=row;
       
       
       
       f_ini_blud(col,row);
       
       return;
    }
}

///////////////////////////////////
// alokuje pamet pro bunky bludiste
void f_ini_blud(int cols, int rows){        //incializuje pamet pro pole bludiste
    mapa.cells = malloc((cols*rows)*(sizeof(int)));
    if(mapa.cells==NULL){
        f_chyba();
    }
    else{
        //printf("debug>> uspesna inicializace\n");
        return;
    }

}
///////////////////////////////////
// Nacita hodnoty ze souboru do bunek mapy bludiste
int f_load_blud(){
    
    char znak;
    unsigned int counter=-1;
    
    //printf("debug>> hello\n");
    int size=mapa.rows*mapa.cols;
    //printf("debug>> size=%d\n",size);
    do{
        znak=fgetc(soubor);
        if(znak == '0' || znak == '1' || znak == '2' || znak == '3' || znak == '4' || znak == '5' || znak == '6' || znak == '7'){
            counter++;
            mapa.cells[counter]=znak;
            mapa.cells[counter] = (int)mapa.cells[counter]-'0';
            //printf("debug>> znak je %d\n",mapa.cells[counter]);
        }

    }while(znak!=EOF);
    
    for(int k=0;k<size;k++){
        //printf("%d",mapa.cells[k]);       Vypis mapy
    }
   // printf("\n");
    return 0;
}
