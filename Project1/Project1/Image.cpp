#include <algorithm>

#include "Image.h"

#include "Formatter.h"
#include "FormatterBMP.h"
#include "FormatterPAM.h"
#include "BMPLayer.h"
#include "PAMLayer.h"
#include "Layer.h"
#include "Operation.h"
#include "Selection.h"
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;


Image::Image(string name) : projectName(name) { 
	myFormatter = nullptr; 
}

void Image::updateMainLayer(){ 
	if (layers.size() == 1) {
		mainLayer = layers.front();
	}
	else {
	//



	}

}

void Image::addLayer(string path, ImageType type) {
	if (myFormatter != nullptr) delete myFormatter;

	switch (type) {
	case BMP: {
		myFormatter = new FormatterBMP();
		//operaciju dodaj iz maina
		//operation = new Operation();//dodao//kasnije moram delete u DTR
		BMPLayer *newLayer = new BMPLayer(path);
		myFormatter->readLayer(path, *newLayer);
		layers.push_back(newLayer);
		updateMainLayer();
		mainLayer->importInMatrix();
	} break;
	case PAM: {
		myFormatter = new FormatterPAM();
		PAMLayer *newLayer = new PAMLayer(path);
		myFormatter->readLayer(path, *newLayer);
		layers.push_back(newLayer);
		updateMainLayer();
		mainLayer->importInMatrix();
	} break;
	}

}

void Image::loadProject(/*string path*/) {
	string path;
	cout << "Unesite ima projekta u licnom formatu" << endl;
	cin >> path;

	importFromCustomFormat(path);
}

void Image::saveProject() { //zapravo nije morao switch-mogao sam:(1-kao uneti format; 2-kao licni projekat)
	cout << endl;

	int selection;
	while (1) {
		cout << "Izaberite u kom obliku zelite da sacuvate fajl(uneti redni broj):" << endl
			<< "1. BMP format" << endl
			<< "2. PAM format" << endl
			<< "3. Licni format(projekat)" << endl;
		cin >> selection;
		if (selection == 1 || selection == 2 || selection == 3) break;
		else cout << "Niste uneli broj u opsegu 1..3!!!" << endl;
	}
	string path = "";
	//void FormatterBMP::writeLayer(string path, const Layer &image)
	switch (selection) {
	case 1: {
		cout << "Unesite putanju fajla:" << endl;
		cin >> path; cout << endl; //std::vector<uint8_t> data

		mainLayer->exportToDataFromMatrix();
		myFormatter->writeLayer(path, *mainLayer);
	} break;
	case 2: {
		cout << "Unesite putanju fajla:" << endl;
		cin >> path; cout << endl;

		mainLayer->exportToDataFromMatrix();
		myFormatter->writeLayer(path, *mainLayer);
	} break;
	case 3:
		cout << "Unesite putanju fajla:" << endl;
		cin >> path; 
		cout << endl;

		exportToCustomFormat(path);
		break;
	}

}

void Image::importFromCustomFormat(string path) {
	ifstream inp;
	inp.open(path.c_str());

	if (inp) {
		//layers.clear();
		//selections.clear();
		//compositeOp->operations.clear();

		char red[MAX];
		inp.getline(red, MAX);
		projectName = string(red);

		inp.getline(red, MAX);
		int numLayers = atoi(red);
		if (numLayers > 0) { //citamo i dodajemo layere
			for (int i = 0; i < numLayers; i++) {
				inp.getline(red, MAX);
				string path(red);
				
				inp.getline(red, MAX);
				ImageType type = (ImageType)atoi(red);

				inp.getline(red, MAX);
				bool active = (bool)atoi(red);

				inp.getline(red, MAX);
				bool visible = (bool)atoi(red);

				addLayer(path, type);
			}
		}

		inp.getline(red, MAX);
		int numSelections = atoi(red);

		if (numSelections > 0) { 
			for (int i = 0; i < numSelections; i++) {
				inp.getline(red, MAX);
				string name(red);

				Selection *s = new Selection(name);

				inp.getline(red, MAX);
				int numRect = atoi(red);

				if (numRect > 0) {
					for (int j = 0; j < numRect; j++) {
						inp.getline(red, MAX);
						int x, y, h, w;
						sscanf(red, "%d %d %d %d", &x, &y, &h, &w);
						s->addRectangle(new Rectangle(x, y, w, h));
					}
				}

				addSelection(s);
			}
		}

		inp.getline(red, MAX);
		int numOperations = atoi(red);

		//DODAO:
		inp.getline(red, MAX);
		string name(red);
		inp.getline(red, MAX);
		bool selectionFlag(red);
		compositeOp = new CompositeOperation(name, selectionFlag);


		if (numOperations > 0) {

			//for (za broj operacija):
			//citam tip operacije
			//switch(tip) { case ADD: kreiram op i dodajem u compostite
			for (int i = 0; i < numOperations; i++) {
				inp.getline(red, MAX);
				int num;
				OperationType type = (OperationType)atoi(red);
				
				switch (type) {
				case ADD: {
					inp.getline(red, MAX);
					int num;
					sscanf(red, "%d", &num);
					
					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					Saberi *opp = new Saberi(num, compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case SUB: {
					inp.getline(red, MAX);
					int num;
					sscanf(red, "%d", &num);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					Oduzmi *opp = new Oduzmi(num, compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case INVSUB: {
					inp.getline(red, MAX);
					int num;
					sscanf(red, "%d", &num);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					InverznoOduzmi *opp = new InverznoOduzmi(num, compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case MUL: {
					inp.getline(red, MAX);
					int num;
					sscanf(red, "%d", &num);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					Pomnozi *opp = new Pomnozi(num, compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case DIV: {
					inp.getline(red, MAX);
					int num;
					sscanf(red, "%d", &num);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					Podeli *opp = new Podeli(num, compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case INVDIV: {
					inp.getline(red, MAX);
					int num;
					sscanf(red, "%d", &num);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					InverznoPodeli *opp = new InverznoPodeli(num, compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case POW: {
					inp.getline(red, MAX);
					int num;
					sscanf(red, "%d", &num);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					Power *opp = new Power(num, compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case LOG: {
					inp.getline(red, MAX);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					Log *opp = new Log(compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case ABS: {
					inp.getline(red, MAX);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					Abs *opp = new Abs(compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case MIN: {
					inp.getline(red, MAX);
					int num;
					sscanf(red, "%d", &num);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					Min *opp = new Min(num, compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case MAXIM: {
					inp.getline(red, MAX);
					int num;
					sscanf(red, "%d", &num);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					Max *opp = new Max(num, compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case INV: {
					inp.getline(red, MAX);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					Inverzija *opp = new Inverzija(compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case GRAY: {
					inp.getline(red, MAX);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					PretvoriUSivo *opp = new PretvoriUSivo(compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case BNW: {
					inp.getline(red, MAX);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					PretvoriUCrnoBelo *opp = new PretvoriUCrnoBelo(compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case MED: {
					
				} break;


				}

				

			}

		}
	}
	else {
		cout << "Greska pri kreiranju ulaznog fajla!" << endl;
	}

	inp.close();
}

void Image::exportToCustomFormat(string path) {
	ofstream outp;
	outp.open(path.c_str());

	if (outp) {
		outp << projectName << endl; //ima projekta

		outp << layers.size() << endl; //broj layera
		//opciono: layeri
		for (Layer *l : layers) {
			outp << l->imagePath << endl;
			outp << l->getImageType() << endl;
			outp << l->active << endl;
			outp << l->visible << endl;
		}

		outp << selections.size() << endl; //broj selekcija
		//opciono: selekcije
		for (Selection *s : selections) {
			outp << s->name << endl;
			outp << s->rectangles.size() << endl;
			for (Rectangle *r : s->rectangles) {
				outp << r->posX << " " << r->posY << " " << r->height << " " << r->width << endl;
			}
		}
		/*
		cout << "Unesite ime CompositeOperation-a:" << endl;
	string name;
	cin >> name;
	compositeOp = new CompositeOperation(name, selectionIsActive);
	compositeOp->addOperation();//dodaje operacije
		*/


		//ovaj deo koda je za .FUN fajl
		outp << compositeOp->operations.size() << endl; //broj operacija
		//dodao:
		outp << compositeOp->name << endl;
		outp << compositeOp->getSelectionExists() << endl;
		for (int i = 0; i < compositeOp->operations.size(); i++) {
			outp << compositeOp->operations[i]->getOperationType() << " " << endl;//<< endl;
			//u zavisnosti od tipa, ispisi podatke (u jednom redu) potrebne za konstruktor te operacije
			switch (compositeOp->operations[i]->getOperationType()) {
			case ADD: {
				outp << compositeOp->operations[i]->getNum() << endl;
			} break;

			case SUB: {
				outp << compositeOp->operations[i]->getNum() << endl;
			} break;

			case INVSUB: {
				outp << compositeOp->operations[i]->getNum() << endl;
			} break;

			case MUL: {
				outp << compositeOp->operations[i]->getNum() << endl;
			} break;

			case DIV: {
				outp << compositeOp->operations[i]->getNum() << endl;
			} break;

			case INVDIV: {
				outp << compositeOp->operations[i]->getNum() << endl;
			} break;

			case POW: {
				outp << compositeOp->operations[i]->getNum() << endl;
			} break;

			case LOG: {
				outp << endl;
			} break;

			case ABS: {
				outp << endl;
			} break;

			case MIN: {
				outp << compositeOp->operations[i]->getNum() << endl;
			} break;

			case MAXIM: {
				outp << compositeOp->operations[i]->getNum() << endl;
			} break;

			case INV: {
				outp << endl;
			} break;

			case GRAY: {
				outp << endl;
			} break;

			case BNW: {
				outp << endl;
			} break;

			case MED: {
				
			} break;


			}
		}

		outp.close();
	}
	else {
		cout << "Greska pri kreiranju izlaznog fajla!" << endl;
	}
}

//..........................................................................................
void Image::addSelection(string name) {
	Selection *s = new Selection(name);
	selections.push_back(s);
	if (selections.size() == 1) mainSelection = selections[0];
}

void Image::addSelection(Selection *s) {
	selections.push_back(s);
	if (selections.size() == 1) mainSelection = selections[0];
}

void Image::choseMainSelection(string id) {//dodati 2 parametra Operacija//kao WRAPPER FJU NAPRAVITI
	for (int i = 0; i < selections.size(); i++) { //ili fju koja ce updateovati to da selekcija postoji
		if (id == selections[i]->getName()) {
			mainSelection = selections[i];
			mainSelection->updateWithAllRectangles(mainLayer, operation, compositeOp);
			break;
		}
	}
}

void Image::addRectangleInSelection(int x, int y, int w, int h) {
	mainSelection->createAndAddRectangle(x, y, w, h, mainLayer, operation, compositeOp);
	selectionIsActive = true;
}

void Image::fillMainSelectionWithColour(int r, int g, int b) {
	mainSelection->fillWithColour(mainLayer, r, g, b);
}

void Image::deleteRectangle(int index) {
	mainSelection->deleteRectangle(index);
	mainSelection->updateWithAllRectangles(mainLayer, operation, compositeOp);
}

void Image::deleteSelection() {
	mainSelection->destroySelection(mainLayer ,operation, compositeOp);
	//proci kroz celu sliku i setovati sve da su neaktivni mozda???
	//ne moram, jer pri choseovanju mainSelectiona updateujem celu matricu
	//ali, da li prodjem zapravo kroz celu??? provericu...
	selectionIsActive = false;
}

//...........................................................................
void Image::addBasicOperation(){
	int number;
	int option;

	cout << "Izaberite koju operaciju zelite da dodate: " << endl;
	cout << "1. saberi" << endl;
	cout << "2. oduzmi" << endl;
	cout << "3. inverzno oduzmi" << endl;
	cout << "4. pomnozi" << endl;
	cout << "5. podeli" << endl;
	cout << "6. inverzno podeli" << endl;
	cout << "7.	power" << endl;
	cout << "8. log" << endl;
	cout << "9. abs" << endl;
	cout << "10. min" << endl;
	cout << "11. max" << endl;
	cout << "12. inverzija" << endl;
	cout << "13. pretvori u sivo" << endl;
	cout << "14. pretvori u crno belo" << endl;
	cout << "15. medijana" << endl;

	cin >> option;

	switch (option) {
	case 1: {
		cout << "Unesite const int:" << endl;
		cin >> number;
		cout << endl;
		operation = new Saberi(number, selectionIsActive, false, true);
	} break;

	case 2: {
		cout << "Unesite const int:" << endl;
		cin >> number;
		cout << endl;
		operation = new Oduzmi(number, selectionIsActive, false, true);
	} break;

	case 3: {
		cout << "Unesite const int:" << endl;
		cin >> number;
		cout << endl;
		operation = new InverznoOduzmi(number, selectionIsActive, false, true);
	} break;

	case 4: {
		cout << "Unesite const int:" << endl;
		cin >> number;
		cout << endl;
		operation = new Pomnozi(number, selectionIsActive, false, true);
		
	} break;

	case 5: {
		cout << "Unesite const int:" << endl;
		cin >> number;
		cout << endl;
		operation = new Podeli(number, selectionIsActive, false, true);
	} break;
	case 6: {
		cout << "Unesite const int:" << endl;
		cin >> number;
		cout << endl;
		operation = new InverznoPodeli(number, selectionIsActive, false, true);
	} break;

	case 7: {
		cout << "Unesite const int:" << endl;
		cin >> number;
		cout << endl;
		operation = new Power(number, selectionIsActive, false, true);
	} break;

	case 8: {
		cout << endl;
		operation = new Log(selectionIsActive, false, true);
	} break;

	case 9: {
		cout << endl;
		operation = new Abs(selectionIsActive, false, true);
	} break;

	case 10: {
		cout << "Unesite const int:" << endl;
		cin >> number;
		cout << endl;
		operation = new Min(number, selectionIsActive, false, true);
	} break;

	case 11: {
		cout << "Unesite const int:" << endl;
		cin >> number;
		cout << endl;
		operation = new Max(number, selectionIsActive, false, true);
	} break;

	case 12: {
		cout << endl;
		operation = new Inverzija(selectionIsActive, false, true);
	} break;

	case 13: {
		cout << endl;
		operation = new PretvoriUSivo(selectionIsActive, false, true);
	} break;

	case 14: {
		cout << endl;
		operation = new PretvoriUCrnoBelo(selectionIsActive, false, true);//sel exists kao globalini flag pravi
	} break;

	case 15: { //Medijana

	} break;
	}
}

void Image::executeBasicOperation(){
	if (operation != nullptr) {
		for (int i = 0; i < mainLayer->getHeight(); i++) {
			for (int j = 0; j < mainLayer->getWidth(); j++) {
				operation->execution(*mainLayer->pixels[i][j]);
			}
		}
	}
	else {
		cout << "Niste uneli BasicOperation!!!" << endl;
	}
}

void Image::destroyBasicOperation(){
	delete operation;
	operation = nullptr;
}

void Image::addCompositeOperation() {
	cout << "Unesite ime CompositeOperation-a:" << endl;
	string name;
	cin >> name;
	compositeOp = new CompositeOperation(name, selectionIsActive);
	compositeOp->addOperation();//dodaje operacije
}

void Image::executeCompositeOperation(){
	if (compositeOp != nullptr) {
		for (int i = 0; i < mainLayer->getHeight(); i++) {
			for (int j = 0; j < mainLayer->getWidth(); j++) {
				compositeOp->execution(*mainLayer->pixels[i][j]);
			}
		}
	}
	else {
		cout << "Niste uneli CompositeOperation!!!" << endl;
	}
}

void Image::destroyCompositeOperation() {
	delete compositeOp;
	compositeOp = nullptr;
}
//.............................................................................

void Image::exportToFun(string path) {

	ofstream outp;
	outp.open(path.c_str());

	if (outp) {
	
		//ovaj deo koda je za .FUN fajl
		outp << compositeOp->operations.size() << endl; //broj operacija
		//dodao:
		outp << compositeOp->name << endl;
		outp << compositeOp->getSelectionExists() << endl;
		for (int i = 0; i < compositeOp->operations.size(); i++) {
			outp << compositeOp->operations[i]->getOperationType() << " " << endl;//<< endl;
			//u zavisnosti od tipa, ispisem podatke (u jednom redu) potrebne za konstruktor te operacije
			switch (compositeOp->operations[i]->getOperationType()) {
			case ADD: {
				outp << compositeOp->operations[i]->getNum() << endl;
			} break;

			case SUB: {
				outp << compositeOp->operations[i]->getNum() << endl;
			} break;

			case INVSUB: {
				outp << compositeOp->operations[i]->getNum() << endl;
			} break;

			case MUL: {
				outp << compositeOp->operations[i]->getNum() << endl;
			} break;

			case DIV: {
				outp << compositeOp->operations[i]->getNum() << endl;
			} break;

			case INVDIV: {
				outp << compositeOp->operations[i]->getNum() << endl;
			} break;

			case POW: {
				outp << compositeOp->operations[i]->getNum() << endl;
			} break;

			case LOG: {
				outp << endl;
			} break;

			case ABS: {
				outp << endl;
			} break;

			case MIN: {
				outp << compositeOp->operations[i]->getNum() << endl;
			} break;

			case MAXIM: {
				outp << compositeOp->operations[i]->getNum() << endl;
			} break;

			case INV: {
				outp << endl;
			} break;

			case GRAY: {
				outp << endl;
			} break;

			case BNW: {
				outp << endl;
			} break;

			case MED: {

			} break;


			}
		}

		outp.close();
	}
	else {
		cout << "Greska pri kreiranju izlaznog FUN fajla!" << endl;
	}

}

void Image::importFromFun(string path) {

	ifstream inp;
	inp.open(path.c_str());

	char red[MAX];

	if (inp) {

		inp.getline(red, MAX);
		int numOperations = atoi(red);

		//DODAO:
		inp.getline(red, MAX);
		string name(red);
		inp.getline(red, MAX);
		bool selectionFlag(red);
		compositeOp = new CompositeOperation(name, selectionFlag);


		if (numOperations > 0) {

			//for (za broj operacija):
			//citam tip operacije
			//switch(tip) { case ADD: kreiram op i dodajem u compostite
			for (int i = 0; i < numOperations; i++) {
				inp.getline(red, MAX);
				int num;
				OperationType type = (OperationType)atoi(red);

				switch (type) {
				case ADD: {
					inp.getline(red, MAX);
					int num;
					sscanf(red, "%d", &num);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					Saberi *opp = new Saberi(num, compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case SUB: {
					inp.getline(red, MAX);
					int num;
					sscanf(red, "%d", &num);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					Oduzmi *opp = new Oduzmi(num, compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case INVSUB: {
					inp.getline(red, MAX);
					int num;
					sscanf(red, "%d", &num);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					InverznoOduzmi *opp = new InverznoOduzmi(num, compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case MUL: {
					inp.getline(red, MAX);
					int num;
					sscanf(red, "%d", &num);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					Pomnozi *opp = new Pomnozi(num, compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case DIV: {
					inp.getline(red, MAX);
					int num;
					sscanf(red, "%d", &num);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					Podeli *opp = new Podeli(num, compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case INVDIV: {
					inp.getline(red, MAX);
					int num;
					sscanf(red, "%d", &num);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					InverznoPodeli *opp = new InverznoPodeli(num, compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case POW: {
					inp.getline(red, MAX);
					int num;
					sscanf(red, "%d", &num);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					Power *opp = new Power(num, compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case LOG: {
					inp.getline(red, MAX);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					Log *opp = new Log(compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case ABS: {
					inp.getline(red, MAX);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					Abs *opp = new Abs(compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case MIN: {
					inp.getline(red, MAX);
					int num;
					sscanf(red, "%d", &num);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					Min *opp = new Min(num, compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case MAXIM: {
					inp.getline(red, MAX);
					int num;
					sscanf(red, "%d", &num);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					Max *opp = new Max(num, compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case INV: {
					inp.getline(red, MAX);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					Inverzija *opp = new Inverzija(compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case GRAY: {
					inp.getline(red, MAX);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					PretvoriUSivo *opp = new PretvoriUSivo(compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case BNW: {
					inp.getline(red, MAX);

					if (compositeOp->operations.size() != 0) compositeOp->operations[compositeOp->operations.size() - 1]->setLastFlag(false);
					//dodajem operaciju koju tu i kreiram
					PretvoriUCrnoBelo *opp = new PretvoriUCrnoBelo(compositeOp->getSelectionExists(), true, true);
					compositeOp->operations.push_back(opp);
				} break;

				case MED: {

				} break;


				}



			}

		}
	}
	else {
		cout << "Greska pri kreiranju ulaznog fajla!" << endl;
	}

	inp.close();
}