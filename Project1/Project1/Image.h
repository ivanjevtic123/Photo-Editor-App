#pragma once

#include <vector>
#include <string>
#include <stdint.h>//za tipove


#include "Layer.h"
//#include "Formatter.h"
//#include "FormatterBMP.h"
//#include "FormatterPAM.h"
#include "BMPLayer.h"
#include "PAMLayer.h"
#include "CompositeOperation.h"

using namespace std;

#define MAX 500

class Formatter; //to avoid circular dependency
class Operation; 
class Selection;

class Image {
private:

	string projectName;

	vector<Layer *> layers; //1..N, N na vrhu
	Layer* mainLayer; //konacni produkt svih layera
	void updateMainLayer();

	Formatter *myFormatter;

	Operation *operation = nullptr; //Ili da stavim BasicOperations *bacicOp = nllptr;
	CompositeOperation *compositeOp = nullptr;
	
	Selection *mainSelection = nullptr;
	vector<Selection *> selections;
	
	bool selectionIsActive = false;
	
	void exportToCustomFormat(string path);
	void importFromCustomFormat(string path);
public:

	Image(string name = "Untitled");

	void addLayer(string path, ImageType type);

	void loadProject(/*string path*/); //ZA LICNI FORMAT
	void saveProject();//na istu lokaciju odozgo prepisem?//mogu da dodam string globalni za load save

	//Paket za Selections:
	void addSelection(string name);
	void addSelection(Selection *s);
	void choseMainSelection(string id);
	void addRectangleInSelection(int x, int y, int w, int h);//na main Selection se odnosi//uvek izaberi za main pa onda operisi sa njim
	void fillMainSelectionWithColour(int r, int g, int b);//na mainLayer se odnosi
	void deleteRectangle(int index);//brise rectangle, i updateuje celu selekciju
	void deleteSelection();


	//Paket za BasicOperation:
	void addBasicOperation();
	void executeBasicOperation();
	void destroyBasicOperation();

	//Paket za CompositeOperation:
	void addCompositeOperation();
	void executeCompositeOperation();
	void destroyCompositeOperation();

	//dodatni Paket za Layere:


	//Paket za .fun
	void exportToFun(string path);
	void importFromFun(string path);


	//u destruktoru sve delete, i sve destroy fje zovi
};
