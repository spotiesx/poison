#include <iostream>
#include <string>
using namespace std;

struct card {
    int value;
    int color;
};

void create_deck(int values[], card all_cards[], int kettles_number, int green_number, int green_value, int other_number){
    int p=0;
    for(int i=0; i < green_number; i++){
        all_cards[i].value = green_value;
        all_cards[i].color = p;
    }
    int t=0;
    p++;
    for(int i=0; i < kettles_number; i++){
        for(int j=green_number+(other_number*i); j<(green_number + other_number + (other_number * i)); j++){
            all_cards[j].value = values[t];
            all_cards[j].color = p;
            t++;
        }
        t=0;
        p++;
    }
};

int main(){
    int players_number, kettles_number, green_number, green_value, other_number;
    cin >> players_number >> kettles_number >> green_number >> green_value >> other_number;

    int deck_size = (green_number + (other_number * kettles_number));

    int* values;
    values = (int*)malloc(other_number * sizeof(int));
    for(int i=0; i<other_number; i++){
        cin >> values[i];
    }
    card* all_cards;
    all_cards = (card*)malloc(deck_size * sizeof(card));
    create_deck(values, all_cards, kettles_number, green_number, green_value, other_number);
    
    card** players_cards;
    players_cards = (card**)malloc(players_number * sizeof(card*));
    for (int i = 0; i < players_number; i++){
        players_cards[i] = (card*)malloc(deck_size * sizeof(card));
    }
    for(int i=0; i<players_number; i++){
        for (int j = 0; j < deck_size; j++) {
            players_cards[i][j].value = 0;
            players_cards[i][j].color = 0;
        }
    }
	int k;
    for (int i = 0; i < players_number; i++) {
        k=0;
		for (int j = i; j < deck_size; j += players_number) {
			if(all_cards[j].value != 0){
                players_cards[i][k] = all_cards[j];
                k++;
            }
        }		
	}
    
    cout << "active player = 1" << endl;
    cout << "players number = " << players_number << endl;
    const char* color[] = {"green","blue", "red", "violet", "yellow", "white", "black"};
    for(int i=0; i<players_number; i++){
        cout << i+1 << " player hand cards: ";
        for(int j=0; j < deck_size; j++){
            if(players_cards[i][j].value != 0){
                cout << players_cards[i][j].value << " " << color[players_cards[i][j].color] << " ";
            }
        }
        cout << endl;
        cout << i+1 << " player deck cards:" << endl;
    }
    for (int i = 0; i < kettles_number; i++){
        cout << i+1 << " pile cards:" << endl; 
    }

    free(players_cards);
    free(values);
	free(all_cards);

    return 0;
}