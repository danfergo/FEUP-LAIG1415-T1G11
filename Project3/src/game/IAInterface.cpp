#include "IAInterface.h"

#include <stdlib.h>    
#include <sstream>



IAInterface::IAInterface(void): conn(BUFFER_MAX_SIZE) {
	
}

GameState * IAInterface::initialize(enum Mode mode){
	std::stringstream cmd;
	cmd << "initialize(" << (int)mode << ").\n";

	conn.send(cmd.str().c_str());
	conn.receive(temporaryBuffer);
	
	return new GameState(temporaryBuffer);
}

std::vector<IJ> IAInterface::availablePiecesToMove(GameState * gamestate){
	std::vector<IJ> coords;

	conn.send(std::string("available_pieces(" + gamestate->toString() + ").\n").c_str());
	conn.receive(temporaryBuffer);

	parseListIJ(temporaryBuffer,coords);
	return coords;
}

std::vector<IJ> IAInterface::availableMoves(GameState * gamestate, IJ coord){
	std::vector<IJ> coords;
	std::cout << coord.toString()<< std::endl;
	conn.send(std::string("available_moves("+ coord.toString()+"," + gamestate->toString() + ").\n").c_str());

	conn.receive(temporaryBuffer);

	parseListIJ(temporaryBuffer,coords); 
	return coords;
}

std::vector<int> IAInterface::availableAngles(GameState * gamestate, IJ from, IJ to){
	std::vector<int> angles;

	conn.send(std::string("available_angles("+ from.toString()+","+to.toString()+"," + gamestate->toString() + ").\n").c_str());

	conn.receive(temporaryBuffer);	

	parseListAngles(temporaryBuffer,angles);
	return angles;
}	


bool IAInterface::isHumanPlaying(GameState * gamestate){
	conn.send(std::string("player_type(" + gamestate->toString() + ").\n").c_str());
	conn.receive(temporaryBuffer);
	std::string player(temporaryBuffer);
	
	return player == "human";
}
/**
int IAInterface::currentPlayer(GameState * gamestate){
	conn.send(std::string("current_player(" + gamestate->toString() + ").\n").c_str());
	conn.receive(temporaryBuffer);
	return atoi(temporaryBuffer);
}
**/
GameState * IAInterface::chooseMove(GameState * gamestate, Move * move){

	//parseListStrings(temporaryBuffer,subdata);

	return NULL;
}


GameState * IAInterface::makeMove(GameState * gamestate, Move * move ){
	std::vector<std::string> subdata;
	std::stringstream a;
	

	if(!move->from.isOutOfBoard()) subdata.push_back(move->from.toString());
	if(!move->to.isOutOfBoard()) subdata.push_back(move->to.toString());
	if(move->toA >=0){
		a << move->toA;
		subdata.push_back(a.str());
	}

	std::string mv;
	mv  = "[";
	for(int i = 0 ; i < subdata.size(); i++){
		if(i != 0) mv += ",";
		mv += subdata[i];
	}
	mv += "]";

	conn.send(std::string("play_move("+ mv + "," + gamestate->toString() + ").\n").c_str());

	conn.receive(temporaryBuffer);	
	
	return new GameState(temporaryBuffer);
}




void IAInterface::parseListIJ(const char * buff, std::vector<IJ> & list){
	if(buff[1] == ']') return;
	while(*buff != ']'){
		list.push_back(IJ(buff[1] - '0',buff[3] - '0'));
		buff += 4;
	}
}

void IAInterface::parseListAngles(const char * buff, std::vector<int> & list){
	if(buff[1] == ']') return;
	while(*buff != ']'){
		list.push_back(buff[1] - '0');
		buff += 2;
	}
}


void IAInterface::parseListStrings(const char * buff, std::vector<std::string> & list){
	int i0 = 1, i = 0, depth = 0;
	while(i == 0 || buff[i-1] != ']' || depth != 0){
		if(buff[i] == '[') depth++;
		if(buff[i] == ']') depth--;
		if(buff[i] == ',' && depth == 1) {
			if(i0!=i)list.push_back(std::string(&buff[i0],(i-i0)));
			i0 = i+1;
		} 

		i++;
	}
	if(i-1 > i0)list.push_back(std::string(&buff[i0],(i-1-i0)));
}
