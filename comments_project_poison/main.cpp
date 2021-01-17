// Zadanie 3 na STOS
    /*int n=1;
    for(int i=0; i<players_number*2; i++){
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
    }*/
// Zadanie 4a na STOS
    /*int green=0, green_value=0, if_different_green = 0
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
        cout << "Found " << green << " green cards, all with " << green_value << " value";
    }
    else if(if_different_green > 1){
        cout << "Different green cards values occurred";
    }
    else if(green==0){
        cout << "Green cards does not exist";
    }*/

    // Zadanie 4b na STOS
    /*int different=0;
    for(int i=2; i<7; i++){
        if(color_counter[i]!=0){
            if(color_counter[i]!=color_counter[i-1]){
                different++;
            }
        }
    }*/
    /*if(different==0){
        cout << "The number cards of all colors is equal: " << color_counter[1];
    }
    else{
        cout << "At least two colors with a different number of cards were found:" << endl;
        for(int i=1; i<7; i++){
            if(color_counter[i]!=0){
                cout << color[i] << " cards are " << color_counter[i] << endl; 
            }
        }
    }*/

    // Zadanie 5 na STOS
    /*int t=0;
    if(different==0){
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
    }*/

    // Zadanie 6 na STOS
    /*int is_ok=0;
    int player_number_card[10];
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
        cout << "Current state of the game is ok";
    }*/
    
    //Zadanie 7 na STOS
    /*card played_card;
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
    }*/