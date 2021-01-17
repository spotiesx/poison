#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

struct card {
    int value;
    int color;
};

int is_letter(char a){
	if (a >= 'A' && a <= 'Z')	return 1;
	if (a >= 'a' && a <= 'z')	return 1;
	return 0;
}

int is_number(char a) {
	if ((a >= '0' && a <= '9'))	return 1;
	return 0;
}

void deal(string lines[], int counted_card[], card cards[][100], int color_counter[], int end_of_for);
void print_stats(int players_number, int pile_number, int hd_card_counted[], int pile_card_counted[]);
void check_green(int players_number, int pile_number, card players_card[][100], card pile_card[][100], int hd_card_counted[], int pile_card_counted[]);
void check_other(int different, int color_counter[], const char* color[]);
void values(int different, int players_number, int pile_number, int* hd_card_counted, int* pile_card_counted, card players_card[][100], card pile_card[][100], const char* color[]);
void check_state(int explosion_threshold, int active_player, int players_number, int pile_number, int* hd_card_counted, int* pile_card_counted, card pile_card[][100]);
void easy_move(int explosion_threshold, int active_player, int players_number, int pile_number, int* hd_card_counted, int* pile_card_counted, card pile_card[][100], card players_card[][100], const char* color[]);
void end_of_round(card players_card[][100], int players_number, int pile_number, int hd_card_counted[], const char* color[]);


int main(){
    const char* color[] = {"green","blue", "red", "violet", "yellow", "white", "black"};
    int color_counter[] = {0,0,0,0,0,0,0};
    
    string control_lines[3];
    for(int i=0; i<3; i++){
        getline(cin, control_lines[i]);
    }
    int active_player = (int)control_lines[0][control_lines[0].length()-1] - 48;
    int players_number = (int)control_lines[1][control_lines[1].length()-1] - 48;

    int explosion_threshold, m=0;
    char exp_thr[4];
    for(int i=22; i<control_lines[2].length(); i++){
        if(is_number(control_lines[2][i])){
            exp_thr[m] = control_lines[2][i];
            m++;
        }
    }
    explosion_threshold = atoi(exp_thr);

    card players_card[10][100];
    card pile_card[10][100];
    for(int i=0; i<10; i++){
        for(int j=0; j<100; j++){
            players_card[i][j] = {0,0};
            pile_card[i][j] = {0,0};
        }
    }

    string cards[10];
    string pile[10];
    int hd_card_counted[10];
    int pile_card_counted[10];

    /*string* cards;
    cards = (string*)malloc(players_number*2*sizeof(string));
    int* hd_card_counted;
    hd_card_counted = (int*)malloc(players_number*2*sizeof(int));*/

    for(int i=0; i<10; i++){
        pile[i]="";
        cards[i]="";
        pile_card_counted[i]=0;
        hd_card_counted[i]=0;
        for(int j=0; j<100; j++){
            players_card[i][j] = {0,0};
            pile_card[i][j] = {0,0};
        }
    }

    string temp_line;
    for(int i=0; i<players_number*2;i++){
        getline(cin, temp_line);
        cards[i] = temp_line;
    }

    deal(cards, hd_card_counted, players_card, color_counter, players_number*2);

    int pile_number=0;
    for(int i=1; i<7; i++){
        if(color_counter[i] != 0){
            pile_number++;
        }
    }

    /*string* pile;
    pile = (string*)malloc(pile_number*2*sizeof(string));
    int* pile_card_counted;
    pile_card_counted = (int*)malloc(pile_number*2*sizeof(int));*/

    for(int i=0; i<pile_number;i++){
        getline(cin, temp_line);
        pile[i]=temp_line;
    }

    deal(pile, pile_card_counted, pile_card, color_counter, pile_number);
   
    print_stats(players_number*2, pile_number, hd_card_counted, pile_card_counted);

    check_green(players_number, pile_number, players_card, pile_card, hd_card_counted, pile_card_counted);

    int different=0;
    check_other(different, color_counter, color);

    values(different, players_number, pile_number, hd_card_counted, pile_card_counted, players_card, pile_card, color);

    check_state(explosion_threshold, active_player, players_number, pile_number, hd_card_counted, pile_card_counted, pile_card);

    easy_move(explosion_threshold, active_player, players_number, pile_number, hd_card_counted, pile_card_counted, pile_card, players_card, color);

    end_of_round(players_card, players_number, pile_number, hd_card_counted, color);
    
    return 0;
}

void deal(string lines[], int counted_card[], card cards[][100], int color_counter[], int end_of_for){
    int value, line_card_number=0, k=0;
    for(int i=0; i<end_of_for; i++){
        if(lines[i]!=""){
            k=0;
            line_card_number = 0;
            for(int j=14; j<lines[i].length(); j++){
                if(is_number(lines[i][j]) && (!is_number(lines[i][j-1]))){
                    if(is_number(lines[i][j+1])){
                        value = (10 * ((int)lines[i][j] - 48)) + ((int)lines[i][j+1] - 48);
                        cards[i][k].value = value;
                        j=j+2;
                    }
                    else{
                        value = ((int)lines[i][j] - 48);
                        cards[i][k].value = value;
                        j++;
                    }
                    line_card_number++;
                }


                if(is_letter(lines[i][j]) && lines[i][j-1] == ' '){
                    switch (lines[i][j]){
                        case 'g':
                            color_counter[0]++;
                            cards[i][k].color = 0;
                            k++;
                            j=j+4;
                            break;
                        case 'r':
                            cards[i][k].color = 2;
                            color_counter[2]++;
                            k++;
                            j=j+2;
                            break;
                        case 'y':
                            cards[i][k].color = 4;
                            color_counter[4]++;
                            k++;
                            j=j+5;
                            break;
                        case 'v':
                            cards[i][k].color = 3;
                            color_counter[3]++;
                            k++;
                            j=j+5;
                            break;
                        case 'w':
                            cards[i][k].color = 5;
                            color_counter[5]++;
                            k++;
                            j=j+4;
                            break;
                        case 'b':
                            if(lines[i][j+2]=='u'){
                                cards[i][k].color = 1;
                                color_counter[1]++;
                                k++;
                                j=j+3;
                            }
                            else{
                                cards[i][k].color = 6;
                                color_counter[6]++;
                                k++;
                                j=j+4;
                            }
                            break;
                    }
                }    
            };
            counted_card[i] = line_card_number;
        }
    }
}

void print_stats(int players_number, int pile_number, int hd_card_counted[], int pile_card_counted[]){
    int n=1;
    for(int i=0; i<players_number; i++){
        if(i%2==0){
            cout << n << " player has " << hd_card_counted[i] << " cards on hand" << endl;
        }
        else{
            cout << n << " player has " << hd_card_counted[i] << " cards in front of him" << endl;
            n++;
        }
    }
    for(int i=0; i<pile_number; i++){
        cout << "there are " << pile_card_counted[i] << " cards on " << i+1 << " pile" << endl;
    }
}

void check_green(int players_number, int pile_number, card players_card[][100], card pile_card[][100], int hd_card_counted[], int pile_card_counted[]){
    int green = 0, green_value = 0, if_different_green = 0;
    for(int i=0; i<players_number*2; i++){
        for(int j=0; j<hd_card_counted[i]; j++){
            if(players_card[i][j].color == 0){
                if(green_value!=players_card[i][j].value){
                    if_different_green++;
                }
                green_value = players_card[i][j].value;
                green++;
            }
        }
    }
    for(int i=0; i<pile_number; i++){
        for(int j=0; j<pile_card_counted[i]; j++){
            if(pile_card[i][j].color == 0){
                if(green_value!=pile_card[i][j].value){
                    if_different_green++;
                }
                green_value = pile_card[i][j].value;
                green++;
            }
        }
    }
    
    if((green!=0) && (if_different_green==1)){
        cout << "Found " << green << " green cards, all with " << green_value << " value" << endl;
    }
    else if(if_different_green > 1){
        cout << "Different green cards values occurred" << endl;
    }
    else if(green==0){
        cout << "Green cards does not exist" << endl;
    }
}

void check_other(int different, int color_counter[], const char* color[]){
    for(int i=2; i<7; i++){
        if(color_counter[i]!=0){
            if(color_counter[i]!=color_counter[i-1]){
                different++;
            }
        }
    }
    if(different==0){
        cout << "The number cards of all colors is equal: " << color_counter[1] << endl;
    }
    else{
        cout << "At least two colors with a different number of cards were found:" << endl;
        for(int i=1; i<7; i++){
            if(color_counter[i]!=0){
                cout << color[i] << " cards are " << color_counter[i] << endl; 
            }
        }
    }
}
void values(int different, int players_number, int pile_number, int* hd_card_counted, int* pile_card_counted, card players_card[][100], card pile_card[][100], const char* color[]){
    int t=0;
    if(different==0){
        int tab[100];
        for(int i=0; i<100; i++){
            tab[i]=0;
        }
        for(int i=0; i<players_number*2; i++){
            for(int j=0; j<hd_card_counted[i]; j++){
                if((players_card[i][j].value!=0) && (players_card[i][j].color == 1)){
                    tab[t] = players_card[i][j].value;
                    t++;
                }
            }
        }
        for(int i=0; i<pile_number; i++){
            for(int j=0; j<pile_card_counted[i]; j++){
                if((pile_card[i][j].value!=0) && (pile_card[i][j].color == 1)){
                    tab[t] = pile_card[i][j].value;
                    t++;
                }
            }
        }
        int cache, exchange;
        do{
            exchange=0;
            for(int i=0; i<t; i++){
                if (tab[i]>tab[i+1]){
                    exchange = exchange + 1;
                    cache = tab[i];
                    tab[i] = tab[i+1];
                    tab[i+1] = cache;  
                }        
            }    
        }while(exchange!=0);
        cout << "The values of cards of all colors are identical:" << endl;
        for(int i=0; i<=t; i++){
            if(tab[i]!=0){
                cout << tab[i] << " ";
            }
        }
        cout<<endl;
    }
    else{
        int b=0,r=0,v=0,y=0,w=0,black=0;
        int tab2[6][100];
        for(int i=0; i<6; i++){
            for(int j=0; j<100; j++){
                tab2[i][j]=0;
            }
        }
        for(int i=0; i<players_number*2; i++){
            for(int j=0; j<hd_card_counted[i];j++){
                if(players_card[i][j].color != 0){
                                switch (players_card[i][j].color){
                                    case 1:
                                        tab2[0][b]=players_card[i][j].value;
                                        b++;
                                        break;
                                    case 2:
                                        tab2[1][r]=players_card[i][j].value;
                                        r++;
                                        break;
                                    case 3:
                                        tab2[2][v]=players_card[i][j].value;
                                        v++;
                                        break;
                                    case 4:
                                        tab2[3][y]=players_card[i][j].value;
                                        y++;
                                        break;
                                    case 5:
                                        tab2[4][w]=players_card[i][j].value;
                                        w++;
                                        break;
                                    case 6:
                                        tab2[5][black]=players_card[i][j].value;
                                        black++;
                                        break;
                                }
                }   
            } 
        }
        for(int i=0; i<pile_number; i++){
            for(int j=0; j<pile_card_counted[i];j++){
                if(pile_card[i][j].color != 0){
                                switch (pile_card[i][j].color){
                                    case 1:
                                        tab2[0][b]=pile_card[i][j].value;
                                        b++;
                                        break;
                                    case 2:
                                        tab2[1][r]=pile_card[i][j].value;
                                        r++;
                                        break;
                                    case 3:
                                        tab2[2][v]=pile_card[i][j].value;
                                        v++;
                                        break;
                                    case 4:
                                        tab2[3][y]=pile_card[i][j].value;
                                        y++;
                                        break;
                                    case 5:
                                        tab2[4][w]=pile_card[i][j].value;
                                        w++;
                                        break;
                                    case 6:
                                        tab2[5][black]=pile_card[i][j].value;
                                        black++;
                                        break;
                                }
                }   
            } 
        }
        for(int p=0; p< 6; p++) {
            for (int i = 0; i < 100; i++) {
                for (int j = i +1; j < 100; ++j) {
                    if (tab2[p][i] > tab2[p][j])  {
                        int swap = tab2[p][i];
                        tab2[p][i] = tab2[p][j];
                        tab2[p][j] = swap;
                    }
                }
            } 
        }
        
        cout << "The values of cards of all colors are not identical:" << endl;
        for(int i=0; i<6; i++){
            cout << color[i+1] << " cards values: ";
            for(int j=0; j<100; j++){
                if(tab2[i][j]!=0){
                    cout << tab2[i][j] << " ";
                }
            }
            cout << endl;
        }
    }
}

void check_state(int explosion_threshold, int active_player, int players_number, int pile_number, int* hd_card_counted, int* pile_card_counted, card pile_card[][100]){
    int is_ok=0;
    int player_number_card[10];
    /*int* player_number_card;
    player_number_card = (int*)malloc(players_number*2*sizeof(int));*/
    int pile_different_color[10];
    int pile_explosion[10];
    for(int i=0; i<10; i++){
        player_number_card[i]=0;
        pile_different_color[i]=0;
        pile_explosion[i]=0;
    }
    int c=0, max_card=0, min_card=100;
    for(int i=0; i<players_number; i++){
        player_number_card[i]=0;
    }
    for(int i=0; i<players_number*2;i++){
        player_number_card[c] += hd_card_counted[i];
        if(i%2==1){
            c++;
        }
    }
    for(int i=0; i<players_number; i++){
        if(i+1<active_player){
            player_number_card[i]++;
        }
        if(player_number_card[i]>max_card){
            max_card = player_number_card[i];
        }
        else if(player_number_card[i]<min_card){
            min_card = player_number_card[i];
        }
    }
    if(max_card-min_card>1){
        is_ok++;
        cout << "The number of players cards on hand is wrong" << endl;
    }
    int pile_color=0, two_colors=0, pile_value;
    for(int i=0; i<pile_number; i++){
        pile_different_color[i] = 0;
        pile_explosion[i] = 0;
        pile_color=0;
        pile_value=0;
        two_colors=0;
        for(int j=0; j<pile_card_counted[i]; j++){
            if(pile_card[i][j].color!=0){
                if(pile_color != pile_card[i][j].color){
                    two_colors++;
                }
                pile_color = pile_card[i][j].color;
            }
            pile_value = pile_value + pile_card[i][j].value;
        }
        if(two_colors>1){
            is_ok++;
            pile_different_color[i] = 1;
        }
        if(pile_value > explosion_threshold){
            is_ok++;
            pile_explosion[i] = 1;
        }
    }
    for(int i=0; i<pile_number; i++){
        if(pile_different_color[i]!=0){
            cout << "Two different colors were found on the " << i+1 << " pile" << endl;
        }
    }
    for(int i=0; i<pile_number; i++){
        if(pile_explosion[i]!=0){
            cout << "Pile number " << i+1 << " should explode earlier" << endl;
        }
    }
    if(is_ok==0){
        cout << "Current state of the game is ok" << endl;
    }
}

void easy_move(int explosion_threshold, int active_player, int players_number, int pile_number, int* hd_card_counted, int* pile_card_counted, card pile_card[][100], card players_card[][100], const char* color[]){
    card played_card;
    if(active_player!=players_number){
        cout << "active player = " << active_player+1 << endl;
    }
    else{
        cout << "active player = 1" << endl;
    }
    cout << "players number = " << players_number << endl;
    cout << "explosion threshold = " << explosion_threshold << endl;
    for(int i=0; i<players_number*2; i++){
        if((i/2+1)==active_player){
                played_card = players_card[i][0];
                hd_card_counted[i]-= 1;
                for(int j=0; j<hd_card_counted[i]; j++){
                    players_card[i][j]=players_card[i][j+1];
                }
                break;
        }
    }
    int pile_color, pile_value=0, explosion_cards = 0, booom=0;
    card back_to_deck[100];
    for(int i=0; i<pile_number; i++){
        if(played_card.color!=0){
            pile_color=0;
            for(int j=0; j<pile_card_counted[i]; j++){
                if(pile_card[i][j].color!=0){
                    pile_color = pile_card[i][j].color;
                }
            }
            if(played_card.color==pile_color){
                pile_card_counted[i] += 1; 
                pile_card[i][pile_card_counted[i]-1]=played_card; 
                for(int j=0; j<pile_card_counted[i]; j++){
                    pile_value = pile_value + pile_card[i][j].value;
                }
                if(pile_value > explosion_threshold){
                    for(int j=0; j<pile_card_counted[i]; j++){
                        back_to_deck[j] = pile_card[i][j];
                        pile_card[i][j] = {0,0};
                        explosion_cards++;
                    }
                    booom = 1;
                }
                break;
            }
        }
        else{
            pile_card_counted[0] += 1; 
            pile_card[0][pile_card_counted[0]-1]=played_card;
            break;
        }
    }
    if(booom == 1){
        int w=0;
        hd_card_counted[active_player*2-1] += explosion_cards;
        for(int i=hd_card_counted[active_player*2-1]-explosion_cards; i<hd_card_counted[active_player*2-1]; i++){
            players_card[active_player*2-1][i]=back_to_deck[w];
            w++;
        }
    }

    for(int i=0; i<players_number*2; i++){
        if(i%2==0){
            cout << i/2+1 << " player hand cards: ";
            for(int j=0; j<hd_card_counted[i]; j++){
               cout << players_card[i][j].value << " " << color[players_card[i][j].color] << " ";
            }
            cout << endl;
        }
        else{
            cout << i/2+1 << " player deck cards: ";
            for(int j=0; j<hd_card_counted[i]; j++){
                cout << players_card[i][j].value << " " << color[players_card[i][j].color] << " ";
            }
            cout << endl;
        }
    }

    for(int i=0; i<pile_number; i++){
        cout << i+1 << " pile cards: ";
        for(int j=0; j<pile_card_counted[i]; j++){
            if(pile_card[i][j].value!=0) cout << pile_card[i][j].value << " " << color[pile_card[i][j].color] << " ";
        }
        cout << endl;
    }
}

bool is_immunity(int player, int immunity[][6], int given_color){
    for(int i=1; i<7; i++){
        if((immunity[player][i] == 1) && (given_color == i)){
                return true;
        }
    }
    return false;
}

void end_of_round(card players_card[][100], int players_number, int pile_number, int hd_card_counted[], const char* color[]){
	
    int immunity[10][6];
    int number_of_color[10][6];
    for(int i=0; i<players_number;i++){
        for(int j=0; j<pile_number+1; j++){
            number_of_color[i][j] = 0;
            immunity[i][j] = 0;
        }
    }
    int temp, w=0;
	for (int i = 1; i < players_number*2; i=i+2) { 
		for (int j = 0; j < hd_card_counted[i]; j++) {
			if((players_card[i][j].color != 0) && (players_card[i][j].value != 0)){
                temp = players_card[i][j].color;
                number_of_color[w][temp]++;
            }
		}
        w++;
	}
	for (int i = 1; i < pile_number+1; i++) { 
		int max = 0, max_player = -1;
		for (int j = 0; j < players_number; j++) {
			if (number_of_color[j][i] > max) {
				max = number_of_color[j][i];
				max_player = j;
			}
			else if (number_of_color[j][i] == max && max > 0) { 
				max_player = -1;
			}
		}
		if (max_player != -1) immunity[max_player][i] = 1;
	}
    for(int i=1; i<7; i++){
        for(int j=0; j<players_number; j++){
            if(immunity[j][i] == 1){
                cout << "Na kolor " << color[i] << " odporny jest gracz " << j+1 << endl;
            }
        }
    }
    
    int score[10];
    for(int i=0; i<10; i++){
        score[i]=0;
    }
    for(int i=1; i<players_number*2; i=i+2){
        for(int j=0; j<hd_card_counted[i]; j++){
            if((players_card[i][j].color!=0) && (is_immunity(((i+1)/2-1), immunity, players_card[i][j].color)==false)){
                score[((i+1)/2)-1]++;
            }
            else if((players_card[i][j].color==0) && (is_immunity(((i+1)/2-1), immunity, players_card[i][j].color)==false)){ 
                score[((i+1)/2)-1]+=2;
            }
        }
        cout << "Wynik gracza " << (i+1)/2 << " = " << score[((i+1)/2)-1] << endl;
    }

}