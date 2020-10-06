/** \file Proj3.h
 * 
 */


/** \mainpage Proj3.h
 * \author Jan Zboril
 * \version 1.0
 * \date 20. 12. 2019
 * \brief hlavickovy soubor pro praci s bludistem
 *        ak. rok 2018/19
 */


/** \def PROJ3_H
 * priradi PROJ3_H
 */
#ifndef PROJ3_H
#define PROJ3_H


/** \brief Struktura Map pro ulozeni map bludiste
 * 
 * řádky jsou v paměti uloženy za sebou, každý řádek je pole jeho buňek. Buňka je typu unsigned char. Implementujte podpůrné funkce tohoto typu (inicializace mapy, načtení mapy, uvolnění mapy)
 *  \struct Map
 *  \var Map::rows
 *      pocet radku mapy
 *  \var Map::cols
 *      pocet sloupcu mapy
 *  \var Map::*cells
 *      ukazatel na pole bunek
 */
typedef struct {
    int rows;
    int cols;
    unsigned char *cells;
} Map;



/** \enum borders
 * \brief bitove vahy jednotlivych hranic
 */
enum borders { BLEFT=0x1, BRIGHT=0x2, BTOP=0x4, BBOTTOM=0x4 };

/** \brief Funkce pro uvolneni mista v pameti
 *  \param argument 1 Map *map
 *  \pre existuje platny ukazatel na Map
 *  \post uvolni alokovanou pamet pro Map
*/
void free_map(Map *map);

/** \brief Funkce pro nacteni mapy
 *  \param const char *filename
 *       - platny ukazatel na soubor
 *  \param Map *map
 *     - platny ukazatel na mapu
 *  \pre existuje platny ukazatel na Map a file
 *  \post Do Map *map se nactou udaje o polickach
 *  \return 0, pokud funkce probehla vporadku
*/
int load_map(const char *filename, Map *map);

/** \brief Funkce pro testovani hranice
 *  \param Map *map
 *     - platny ukazatel na mapu
 * \param int r
 *      - kolikaty radek
 * \param int c
 *      - kolikaty sloupec
 * \param int border
 *      - jakou hranici testuji
 *  \pre existuje platny ukazatel na Map, r a c je cislo v rozmezi velikosti mapy, border je v rozmezi 1-4
 *  \return true, pokud na dane hranici je stena
 *  \return false, pokud na hranici neni stena
*/
bool isborder(Map *map, int r, int c, int border);


/** \brief zjistuje, jestli policko na dane souradnici ma spodni hranici
 *  \return true or false depending on map size
 *  \param int r
 *      - radek testovaneho policka
 *  \param int f
 *      - sloupec testovaneho policka
 */
bool hasbottom(int r, int c);


/** \brief funkce vracejici, která hranice se má po vstupu do bludiště následovat 
 *  \return 1, pravá při vstupu zleva do bludiště na lichém řádku,
 *  \return 2, dolní při vstupu zleva do bludiště na sudém řádku,
 *  \return 3, levá při vstupu shora do bludiště,
 *  \return 4, pravá při vstupu zespodu do bludiště,
 *  \return 5, horní při vstupu zprava do bludiště, pokud má políčko horní hranici a
 *  \return 6, levá při vstupu zprava do bludiště, pokud má políčko dolní hranici.
 *  \pre Map *map je platny ukazatel, leftright je 0 nebo 1, r a c je cislo v rozmezi velikosti mapy
 *  \post program vi, jak dale postupovat pri hledani cesty bludistem
 *  \param Map *mapu
 *      - ukazatel na mapu
 *  \param int r
 *      - startovni policko radek
 *  \param int c
 *      - startovni policko sloupec
 *  \param leftright
 *      - pravidlo prave nebo leve ruky
 */
int start_border(Map *map, int r, int c, int leftright);


/** \brief Testuje platnost mapy
 *  \pre Map *map je platny ukazatel
 *  \param map *map
 *      - ukazatel na mapu
 *  \return 0, pokud je mapa v poradku a platna
 *  \return 1, pokud je mapa neplatna nebo spatne
 */
int check_map(Map *map);


/** \brief Nacte mapu ze souboru a otetuje jeji platnost viz funkce check_map()
 *  \pre *filename a *map jsou platne ukazatele
 *  \post pokud vrati 1, pak program vypise chybu a ukonci se
 *  \param const char *filename
 *      - ukazatel na nazev souboru
 *  \param Map map
 *      - ukazatel na mapu
 * \return 1, pokud je mapa neplatna
 * \return 0, pokud je mapa platna
 */
int load_and_check_map(const char *filename, Map *map);


/** \brief testuje, jestli je policko za hranici mapy
 *  \pre *filename a *map jsou platne ukazatele
 *  \post pokud vrati true, pak program vypise chybu a ukonci se
 *  \param int r
 *      - na jakem radku je policko
 *  \param int c
 *      - na jakem sloupci je policko
 *  \param Map map
 *      - ukazatel na mapu
 *  \return true, pokud je policko mimo hranice mapy
 *  \return false, pokud neni policko mimo hranice mapy
 */
bool is_out(Map *map, int r, int c);


/** \brief Vypise cestu bludiste
 *  \pre Map *map je platny ukazatel
 *  \pre r a c neni mimo hranice mapy - testuje is_out()
 *  \pre int leftright je 0 nebo 1
 *  \post program se uspesne ukonci
 *  \param Map *map
 *      - ukazatel na Map
 *  \param int r
 *      - startovni radek
 *  \param int c
 *      - startovni sloupec
 *  \param int leftright
 *      - urcuje, jestli pouzit pravou nebo levou cestu
 */
void print_path(Map *map, int r, int c, int leftright);

#endif
