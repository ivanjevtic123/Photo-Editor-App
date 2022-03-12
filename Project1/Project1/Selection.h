#pragma once

#include <stdio.h>

#include "Image.h"
#include "Operation.h"
#include "Rectangle.h"

using namespace std;

class Rectangle;
//class Operation;

class Selection {
private:
	friend class Image;
	string name;

	vector<Rectangle *> rectangles;
public:

	Selection(string nn/*, vector<Rectangle *> rr*/) {//nakon svakog puta: updateSelecton();
		name = nn;
		//rectangles = rr; //deep cpy of pointers, shallow cpy of objects, taking control of pointed objects
		//updateSelection();//prodji kroz sliku po formuli
	}

	~Selection() { //destructor
		rectangles.clear();
	}

	string getName() const {
		return name;
	}

	//setujem RGB
	void fillWithColour(Layer *layer, int r, int g, int b) {
		for (int i = 0; i < (layer->getHeight()); i++) {
			for (int j = 0; j < (layer->getWidth()); j++) {//umesto j sam pisao i, bravo 
				if (layer->pixels[i][j]->checkActive()) {
					layer->pixels[i][j]->setRed(r);
					layer->pixels[i][j]->setGreen(g);
					layer->pixels[i][j]->setBlue(b);
				}
			}
		}
	}

	//============================================================================================
	//!!!SVE RADI OKO DODAVANJA!!!
	void createAndAddRectangle(int x, int y, int w, int h, Layer *layer, Operation *opBasic, CompositeOperation *opComposite) {
		Rectangle *r = new Rectangle(x, y, w, h);
		addRectangle(r);
		//sad update:
		updateSelection(layer, r, opBasic, opComposite);
	}
	void addRectangle(Rectangle *r) {//nakon svakog puta: updateSelecton();
		rectangles.push_back(r);
		//updateSelection();//prodji kroz sliku po formuli
	}
	//mzd u Image.h pa posle svakog poziva ovih da ga zovem
	//mainLayer->pixels; uvek argument
	void updateSelection(Layer *layer, Rectangle *r, Operation *opBasic, CompositeOperation *opComposite) { 
		
		
		int pomX = 0, pomY = 0, pomHeight = 0, pomWidth = 0;
		bool flagBadSelection = false;


		if (r->getX() < 0) pomX = 0;
		else if (r->getX() > layer->getHeight()) flagBadSelection = true; //pomX = layer->getHeight();//lose
		else pomX = r->getX();

		if (r->getY() < 0) pomY = 0;
		else if (r->getY() > layer->getWidth()) flagBadSelection = true;//pomY = layer->getWidth();
		else pomY = r->getY();
		
		if (r->getHeight() < 0) pomHeight = 0;
		else if (r->getHeight() + pomX > layer->getHeight()) pomHeight = layer->getHeight() - pomX;//pomHeight = layer->getHeight();
		else pomHeight = r->getHeight();

		if (r->getWidth() < 0) pomWidth = 0;
		else if (r->getWidth() + pomY > layer->getWidth()) pomWidth = layer->getWidth()  - pomY;//pomWidth = layer->getWidth();
		else pomWidth = r->getWidth();

		if (flagBadSelection == true) {
			cout << "Lose dimenzije rectanglea!" << endl;
			return;
		}

		for (int i = pomX; i < pomX + pomHeight; i++) {
			for (int j = pomY; j < pomY + pomWidth; j++) {
				if(layer->pixels[i][j] != nullptr)layer->pixels[i][j]->setActive(r->getStatus());//BUG!!!!!
			}
		}
		if(opBasic != nullptr) opBasic->setSelectionExists(true);//ispod stavi
		if (opComposite != nullptr) opComposite->setSelectionExists(true);//ispod for stavi
	}
	/*void updateSelection(Layer *layer, Rectangle *r, Operation *opBasic, CompositeOperation *opComposite) {
		for (int i = 0; i < layer->getHeight(); i++) {
			for (int j = 0; j < layer->getWidth(); j++) {

			}
		}

	}*/

	//============================================================================================
	

	//SVE DELOVE SELEKCIJE UPDATEUJE
	//pri brisanju rectangla jednog, tad zovi
	void updateWithAllRectangles(Layer *layer, Operation *opBasic, CompositeOperation *opComposite) {
		for (int i = 0; i < rectangles.size(); i++) {
			updateSelection(layer, rectangles[i], opBasic, opComposite);//BUG!!!
		}
	}

	

	//obavezno updateSelection(...) nakon ove fje:
	void deleteRectangle(int index) {//od 0 do n
		// erase the 6th element
		rectangles.erase(rectangles.begin() + index);
		/*for (int i = 0; i < rectangles.size() - 1; i++) {
			rectangles[i]->
		}*/
	}

	void destroySelection(Layer *layer, Operation *opBasic, CompositeOperation *opComposite) {//samo da se poziva na mainSelection; ako izaberem drugi selection za
		rectangles.clear();  //main, onda opet postaviti SelectionExists na true!!!
		if (opBasic != nullptr) opBasic->setSelectionExists(false);
		if (opComposite != nullptr) opComposite->setSelectionExists(false);
		//prodji kroz ceo matrix
		for (int i = 0; i < layer->getHeight(); i++) {
			for (int j = 0; j < layer->getWidth(); j++) {
				layer->pixels[i][j]->setActive(false);
			}
		}
	}

	

};

