#include<vector>
#include<iostream>
#include <algorithm>
#include<string>

using namespace std;


//owner 0 = water
struct ship{
	int owner;
};

struct coordinate{
	bool shot;
	vector <ship> ships;
};

struct player{
	int ships_counter;
};



bool GameEnded(player players[]){
 bool result = false;
 if(players[0].ships_counter == 0 || players[1].ships_counter ==0) result = true;
 return result;
}

int ChangeTurn2(int current_turn){
	int result = 0;
	if(current_turn ==1) result=2;
	if(current_turn ==2 ) result =1;

	return result;
}

//output =0 :end game, 1: player 1 turn, 2 :player 2 turn
int ChangeTurn(int _currentTurn, player players[], bool _hit){
 int _turn = 0;
 if(GameEnded(players)){
	   if(_hit){
		   if(_currentTurn ==1 ){
			   	   if(players[1].ships_counter==0)  return(2);}}

	   else if (!_hit){
	   		   if(_currentTurn ==1) return(2);
	 }
 }

	 if(!GameEnded(players)){
	   if(_hit){
		   if(_currentTurn == 1){
			   if(players[1].ships_counter!=0) return(1);
			   else if (players[1].ships_counter==0) return(2);}
		   else if (_currentTurn ==2){
				 if(players[0].ships_counter!=0) return (2);
				 //else if (players[0].ships_counter==0) return(1);
			 }
		 }
		 else if(!_hit){

			 return(ChangeTurn2(_currentTurn));}}

	 return _turn;
}









int main()
{
	int game_rounds = 0;
	string result;
	cin >> game_rounds;
	while(game_rounds >0){

	int w = 0;
	int h = 0;
	int n = 0;
	cin >> w >> h >> n;

	player players[2];
	players[0].ships_counter =0;
	players[1].ships_counter =0;

	coordinate map[w][h];
	//initialize the map
	 for(int j=0 ; j<h ; j++){
		 for(int i=0; i<w; i++ ){
			 map[i][j].shot =false;
			 map[i][j].ships.push_back(ship{0});}}

	char input_p1[w][h];
	char input_p2[w][h];

		for(int j = 0; j<h; j++ ){
			for(int i =0 ; i <w; i++)
							cin >> input_p1[i][j];}
		for(int j = 0; j<h; j++ ){
			for(int i =0 ; i <w; i++)
							cin >> input_p2[i][j];}


 //set map
 //player1
 for(int j = 0; j<h; j++ ){
	 for(int i=0 ; i < w; i++){
		 if(input_p1[i][j] == '#'){
		 ship new_ship;
		 new_ship.owner = 1;
		 players[0].ships_counter++;
		 map[i][j].ships.push_back(new_ship);
	 }}}
 //player2
 for(int j = 0; j<h; j++ ){
	 for(int i=0 ; i < w; i++){
		 if(input_p2[i][j] == '#'){
		 ship new_ship;
		 new_ship.owner = 2;
		 players[1].ships_counter++;
		 map[i][j].ships.push_back(new_ship);
	 }}}

//get the shoots
// 0 :x, 1: y
 int shots [n][2] ;

 for(int i = 0; i<n; i++ ) //0=x , 1=y
 {
 cin>>shots[i][0] >> shots[i][1];
 shots[i][1] = (h-1)-shots[i][1];

 }




 int player_turn = 1;
 int x=-1;
 int y=-1;
 bool HIT = false;
 int shot_index= 0;
 bool GameEnd = false;
 for( shot_index = 0; shot_index<n && player_turn != 0; shot_index++ ){
	 x = shots[shot_index][0];
	 y = shots[shot_index][1];
                    if(map[x][y].shot == false){  // coordinate is not shot
                        map[x][y].shot=true;
                        if(map[x][y].ships.size() > 1){ // there are other ships here!(ship with owner 0 is water)
                            for (ship shipOnCoordinate : map[x][y].ships ){ //reduce counters
                                if(shipOnCoordinate.owner !=0 && shipOnCoordinate.owner != player_turn)
                                {
                                HIT = true;
                                if(shipOnCoordinate.owner == 1) players[0].ships_counter--;
                                if(shipOnCoordinate.owner == 2) players[1].ships_counter--;}}
                        }
                        else if(map[x][y].ships.size() < 1) //miss
                        {
                        	HIT = false;
                        }

                    }
                    else if (map[x][y].shot == true) //miss
                    {
                    	HIT = false;
                    }

    player_turn = ChangeTurn(player_turn, players,HIT);
    HIT = false;
    GameEnd = GameEnded(players);
}

 //player_turn =0 means game ended
 if(GameEnd==true) //game ended
 {
     if(players[0].ships_counter==0 && players[1].ships_counter==0)
         result.append("draw\n");
     else if(players[0].ships_counter==0 && players[1].ships_counter!=0)
    	 result.append("player two wins\n");
     else if(players[0].ships_counter!=0 && players[1].ships_counter==0)
         result.append("player one wins\n");
     else if(players[0].ships_counter>0 && players[1].ships_counter > 0) //shoudnt happen
         result.append("draw\n");}

 else if(GameEnd==false) //game not ended
{
      if (players[0].ships_counter==0 && players[1].ships_counter==0) result.append("draw\n");

       if(players[0].ships_counter > 0 || players[1].ships_counter > 0) result.append("draw\n");
       else if(players[0].ships_counter==0 && players[1].ships_counter!=0)
      	 result.append("player two wins\n");
       else if(players[0].ships_counter!=0 && players[1].ships_counter==0)
           result.append("player one wins\n");

       else if(shot_index >= n) result.append("draw\n");
 }
game_rounds--;
	}
	cout << result;
 return 0;
}
