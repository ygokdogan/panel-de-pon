#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void clearScreen();
void printBoard();
void addRandomRow();

const int MAX_SIZE = 20;
int ROW, COL;

int mode = -1, move = -1;
int i, j, randNum, x1, y1, x2, y2;
int transpositionCount = 0, explosionCount = 0;
int isValidPlay, isGameEnded;
int currRow, countH, countV;

char elements[5] = {'*', '/', '+', '%', 'O'};
char board[100][100];

int main(){
    printf("\n\n\t\tPANEL DE PON\n\nOYUN KURALLARI:\n");
    printf("1 - BUTUN KOORDINATLARIN FORMATI (x,y) OLMALIDIR.\n");
    printf("2 - OYUN TAHTASININ BUYUKLUGU MAKSIMUM 20x20 OLABILIR.\n");
    printf("3 - KOORDINATLARIN INDEXLERI 1-SATIR veya 1-SUTUN ARALIGINDA OLMAK ZORUNDADIR.\n");
    printf("4 - NOKTA KARAKTERI BIR ELEMENTI DEGIL BOSLUGU IFADE EDER.\n\n");
    
    srand(time(NULL));

    printf("Oyun modu icin 1, kontrol modu icin 2 giriniz: ");
    scanf("%d", &mode);
    while(mode < 1 || mode > 2){
        printf("1 ve 2 disinda bir deger girdiniz. Lutfen oyun modu icin 1, kontrol modu icin 2 giriniz: ");
        scanf("%d", &mode);
    }

    printf("Oyun alani boyutlarini giriniz (N M): ");
    scanf("%d %d", &ROW, &COL);
    while((ROW <= 0 || ROW > MAX_SIZE) || (COL <= 0 || COL > MAX_SIZE)){
        printf("Oyun alani boyutu 20x20'den buyuk olamaz. Boyutlari tekrar giriniz: ");
        scanf("%d %d", &ROW, &COL);
    }

    for(i = 0; i < ROW; i++){
        for(j = 0; j < COL; j++){
            board[i][j] = '.';
        }
    }

    if(mode == 2){
        printf("Tahtanin elemanlarini manuel olarak giriniz: \n");

        for(i = ROW - 1; i > (ROW - 1) / 2; i--){
            for(j = 0; j < COL; j++){
                printf("Eleman [%d, %d]: ", i, j);
                scanf(" %c", &board[i][j]);
            }
        }
    }
    else{
        for(i = ROW - 1; i > (ROW - 1) / 2; i--){
            for(j = 0; j < COL; j++){
                randNum = rand() % 5;
                board[i][j] = elements[randNum];
            }
        }
    }

    printBoard();

    isGameEnded = 0;
    while(isGameEnded == 0){
        do{
            printf("Yer degisikligi icin 1, patlama icin 2, cikmak icin 0 giriniz: ");
            scanf("%d", &move);
        }while(move < 0 || move > 2);

        isValidPlay = 1;

        if(move == 0){
            isGameEnded = 1;
        }
        else if(move == 1){
            printf("Koordinatlar(x1,y1 x2,y2): ");
            scanf("%d,%d %d,%d", &x1, &y1, &x2, &y2);

            if (x1 < 1 || x1 > ROW || x2 < 1 || x2 > ROW || y1 < 1 || y1 > COL || y2 < 1 || y2 > COL) {
                isValidPlay = 0;
                printf("Sinirlar icerisinde bir koordinat girmediniz.\n");
            }

            if(isValidPlay == 1){
                x1--; y1--;
                x2--; y2--;

                if (board[x1][y1] == '.' || board[x2][y2] == '.') {
                    isValidPlay = 0;
                    printf("Bos hucreyle degisim yapilamaz.\n");
                }

                int yDif = y2 - y1;
                int xDif = x2 - x1;
                int xSqrd = xDif * xDif;
                int ySqrd = yDif * yDif;
                
                if((xSqrd + ySqrd) > 1 && isValidPlay == 1){
                    isValidPlay = 0;
                    printf("Yan yana hucrelerle degisim yapmalisiniz.\n");
                }
                
                char tmp = board[x2][y2];
                board[x2][y2] = board[x1][y1];
                board[x1][y1] = tmp;

                transpositionCount++;
            }
        }
        else{
            printf("Koordinatlar(x,y): ");
            scanf("%d,%d", &x1, &y1);

            isValidPlay = 1;
            if(x1 < 1 || x1 > ROW || y1 < 1 || y1 > COL){
                isValidPlay = 0;
                printf("Sinirlar icinde bir koordinat girmediniz. Lutfen koordinatlari (x,y) seklinde girdiginizden emin olun veya tekrar deneyin.\n");
            }

            x1--; y1--;
            if(board[x1][y1] == '.'){
                isValidPlay = 0;
                printf("Girdiginiz koordinatta herhangi bir eleman yok, lutfen tekrar deneyiniz.\n");
            }

            if(isValidPlay == 1){
                countH = 1; countV = 1;

                i = y1+1;
                while(i < COL && board[x1][i] == board[x1][y1]){
                    countH++;
                    i++;
                }

                i = x1+1;
                while(i < ROW && board[i][y1] == board[x1][y1]){
                    countV++;
                    i++;
                }

                if(countH >= 3 && countV >= 3){
                    if(countH >= countV){
                        countV = 0;
                    }
                    else{
                        countH = 0;
                    }
                }

                if(countH >= 3){
                    for(i = y1; i < y1 + countH; i++){
                        board[x1][i] = '.';
                    }
                    explosionCount += countH;
                }

                if(countV >= 3){
                    for(i = x1; i < x1 + countV; i++){
                        board[i][y1] = '.';
                    }
                    explosionCount += countV;
                }
            }
            
        }

        if(isGameEnded == 0 && isValidPlay == 1){
            for(j = 0; j < COL; j++){
                currRow = ROW - 1;

                for(i = ROW - 1; i >= 0; i--){
                    if(board[i][j] != '.'){
                        board[currRow][j] = board[i][j];
                        if(currRow != i){
                            board[i][j] = '.';
                        }
                        currRow--;
                    }
                }

                for(i = currRow; i >= 0; i--){
                    board[i][j] = '.';
                }
            }
        }

        if(isValidPlay == 1){
            if(mode == 1){
                clearScreen();
            }
            printBoard();
            sleep(3);
            if(mode == 1){
                clearScreen();
            }
            if(move == 1){
                addRandomRow();
            }
            printBoard();
        }

        i = 0;
        while(i < COL && isGameEnded == 0){
            if(board[0][i] != '.'){
                isGameEnded = 1;
            }
            i++;
        }
        
        move = -1;
    }
    
    clearScreen();
    printBoard();
    printf("\t\tOYUN SONLANDI\n");
}  

void printBoard(){
    int i, j;

    printf("------------------TAHTA------------------\n");
    printf("  ");
    for(i = 0; i < COL; i++){
        printf("%d ", i+1);
    }
    printf("\n");

    for(i = 0; i < ROW; i++){
        printf("%d ", i+1);
        for(j = 0; j < COL; j++){
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }

    printf("\nYer degistirme sayisi: %d\n", transpositionCount);
    printf("Toplam patlatilan element: %d\n\n", explosionCount);
}

void addRandomRow(){
    int i, j;

    for(i = 0; i < ROW - 1; i++){
        for(j = 0; j < COL; j++){
            board[i][j] = board[i+1][j];
        }
    }

    for(i = 0; i < COL; i++){
        randNum = rand() % 5;
        board[ROW - 1][i] = elements[randNum];
    }
}

void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}