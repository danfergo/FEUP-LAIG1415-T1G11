#include "Board.h"
#include "BoardPiece.h"
#include "../../scenegraph/animations/LinearAnimation.h"
#include "../../scenegraph/animations/CircularAnimation.h"
#include "../../scenegraph/primitives/Retangle.h"

BoardHouse::BoardHouse(Board * board, int i, int j): board(board), i(i), j(j) {
	setEnabled(false);

}


void BoardHouse::setEnabled(bool val){
	this->setVisible(val);
	this->setTouchable(val);
}


bool BoardHouse::clickHandler(){
	this->board->getController()->selectBoardCoords(i,j);
	return true;
}


Board::Board(){
	
	outPadding = 0.01f;
	cellSize  = .05f;
	innerPadding = cellSize/(float)6;
	float x, z;
	Point2d points[2] = {{-cellSize/2,-cellSize/2},{cellSize/2,cellSize/2}};
	Retangle * r = new Retangle(points);
	for(int i = 0 ; i < 6; i++){
		for(int j = -2; j < 8; j++){
			piece(i,j) = NULL;
			if(!(( j < 0 || j >= 6) && i > 4)){  
				house(i,j) = new BoardHouse(this,i,j);
				house(i,j)->addPrimitive(r);
				coordsConvert(i,j,x,z);
				house(i,j)->addTranslation(x,0,z);
				house(i,j)->addRotationX(-90);
				this->addDescendants(house(i,j));
			}else{
				house(i,j) = NULL;
			}
		}
	} 
	
	Point2d vertexes[2] = {{-0.5,-0.5},{0.5,0.5}};
	Node * ground = new Node(new Retangle(vertexes));

	angleChooser = new AngleChooser(this);
	this->addDescendants(angleChooser);
	this->addTranslation(-2.5*cellSize,0,-2.5*cellSize);



	ground->addTranslation(2.5*cellSize,0,2.5*cellSize); 
	ground->addScaling(54*cellSize/5,0, 30*cellSize/5); 
	ground->addRotationX(-90);

	this->addDescendants(ground);
	

}


void Board::coordsConvert(int i, int j, float &  xx, float & zz){

	if(i >= 0 &&  i < 6 && j >= 0 && j < 6){
		xx = cellSize*j;
		zz = cellSize*i;

	}else{

		if(j < 0) {
			xx = -1*outPadding +  cellSize*j + innerPadding*(j-1);
		}else{
			xx = 6*cellSize + outPadding +  (cellSize)*(j-6) + innerPadding*(j-5);
		}
		zz = cellSize*i + innerPadding*(i+1);
	}

}

BoardPiece * & Board::piece(int i, int j){
	return boardPieces[i][j+2];
}

BoardHouse * & Board::house(int i, int j){
	return boardHouses[i][j+2];
}

BoardPiece* Board::addPiece(int i, int j){
	float x, z;
	coordsConvert(i,j,x,z);
	BoardPiece * boardPiece = new BoardPiece(this);
	boardPiece->addTranslation(x,0,z);
	piece(i,j) = boardPiece;
	this->addDescendants(boardPiece);
	return boardPiece;
}


MatchController * Board::getController(){
	return this->controller;
}

void Board::setController(MatchController * controller){
	this->controller = controller;
}
void Board::update(unsigned time){
	Node::update(time);
	/**controller->update();**/
}


void Board::setSelectable(std::vector<IJ> pieces){
	for(std::vector<IJ>::iterator it = pieces.begin(); it != pieces.end(); it++){
		this->piece(it->i, it->j)->setTouchable(true);
	}
}

void Board::unsetSelectableAll(){
	for(int i = 0 ; i < 6; i++){
		for(int j = -2; j < 8; j++){
			if(piece(i,j) != NULL){
				this->piece(i,j)->setTouchable(false);
			}
		}
	} 
}

void Board::unsetSelectableAllHouses(){
	for(int i = 0 ; i < 6; i++){
		for(int j = -2; j < 8; j++){
			if(house(i,j) != NULL){
				house(i,j)->setEnabled(false);
			}
		}
	} 
}

void Board::setSelectableHouses(std::vector<IJ> houses){
	for(std::vector<IJ>::iterator it = houses.begin(); it != houses.end(); it++){
		this->house(it->i, it->j)->setEnabled(true);
	} 
}


std::vector<IJ> Board::getOutsidePieces(int player){
	std::vector<IJ> coords;
	IJ temp(0,0);
	for(int i = 0 ; i < 6; i++){
		for(int j = -2+player*8; j < 0+player*8; j++){
			if(piece(i,j)){
				temp.i = i; temp.j = j;
				coords.push_back(temp);
			}
		}
	}
	return coords;
}

std::vector<IJ> Board::getOutsideFreeHouses(int player){
	std::vector<IJ> coords;
	IJ temp(0,0);
	for(int i = 0 ; i < 6; i++){
		for(int j = -2+player*6; j < 0+player*8; j++){
			if(piece(i,j) == NULL){
				temp.i = i; temp.j = j;
				coords.push_back(temp);
			}
		}
	}
	return coords;
}

AngleChooser * Board::getAngleChooser(){
	return this->angleChooser;
}

int Board::pushUpPiece(int delay, int i,int j){
	Point3d points[2] = {{0,0,0},{0,cellSize,0}}; 
	LinearAnimation * animation = new LinearAnimation(delay,1);
	animation->addControlPoint(points[0]);
	animation->addControlPoint(points[1]);
	piece(i,j)->addAnimation(animation);
	return 1;
}


int Board::pullDownPiece(int delay, int i,int j){
	Point3d points[2] = {{0,0,0},{0,-cellSize,0}}; 
	LinearAnimation * animation = new LinearAnimation(delay,1);
	animation->addControlPoint(points[0]);
	animation->addControlPoint(points[1]);
	piece(i,j)->addAnimation(animation);
	return 1;

}

int Board::slidePiece(int delay, int fromI,int fromJ, int toI, int toJ){
	float fromX,fromZ,toX,toZ, deltaX, deltaZ;
	coordsConvert(fromI,fromJ,fromX,fromZ);
	coordsConvert(toI,toJ,toX,toZ);

	deltaX = toX - fromX;
	deltaZ = toZ - fromZ;
	
	Point3d points[2] = {{0,0,0},{deltaX,0,deltaZ}}; 
	LinearAnimation * animation = new LinearAnimation(delay,1,false);
	animation->addControlPoint(points[0]);
	animation->addControlPoint(points[1]);
	piece(fromI,fromJ)->addAnimation(animation);
	piece(toI,toJ) = piece(fromI,fromJ);
	piece(fromI,fromJ) = NULL;  
	return 1;
}

int Board::rotatePiece(int delay, int i,int j, int rot){
	Point3d center = {0,0,0};
	CircularAnimation * animation = new CircularAnimation(delay,1,center,0, -45*piece(i,j)->getAngle(),-45*rot);
	piece(i,j)->addAnimation(animation); 
	piece(i,j)->setAngle(rot);
	return 1;
}


void  Board::moveAngleChooserTo(int i, int j){
	float x,z;
	coordsConvert(i,j,x,z);
	this->angleChooser->resetTransformations();
	this->angleChooser->addTranslation(x,0,z);
}


void Board::getCoords(BoardPiece * piece, int & ii, int & jj){
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 10; j++){
			if(piece == this->boardPieces[i][j]){
				ii = i;
				jj = j-2;
				return;
			}
		}
	}
}

