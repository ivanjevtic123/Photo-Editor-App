#include "image.h"

int main2() {
	try {
		Image project("Novi projekat");

		project.addLayer("primer.bmp", ImageType::BMP);

		project.saveProject();
	}
	catch (ErrorInPixelValue e) {
		cout << e;
	}
	system("pause");
	return 0;
}


int mainCetvrtiMaj() {
	Image project("Novi projekat");

	project.addLayer("primer.bmp", ImageType::BMP);


	project.addSelection("sel1");
	project.choseMainSelection("sel1");
	project.addRectangleInSelection(12, 12, 2, 2);
	project.addRectangleInSelection(10, 10, 1, 5);
	//project.fillMainSelectionWithColour(0, 0, 0);

	//project.addBasicOperation();

	//project.executeBasicOperation();

	//project.destroyBasicOperation();

	project.addCompositeOperation();
	project.executeCompositeOperation();
	
	project.saveProject();

	//project.destroyCompositeOperation();

	//project.deleteSelection();

	//project.saveProject();

	system("pause");
	return 0;
}


int mainFunImport() {

	Image project("Novi projekat");

	project.addLayer("primer.bmp", ImageType::BMP);


	project.importFromFun("probaProba.fun");
	project.executeCompositeOperation();

	project.saveProject();

	//project.exportToFun("probaProba.fun");

	project.destroyCompositeOperation();


	project.saveProject();

	system("pause");
	return 0;
}

int mainLicniFormat() {

	Image project("Novi projekat");
	project.loadProject();

	project.saveProject();

	system("pause");
	return 0;
}

int mainKKKK() {
	Image project("Novi projekat");
	project.addLayer("primer.bmp", ImageType::BMP);

	project.addSelection("sel1");
	project.choseMainSelection("sel1");
	project.addRectangleInSelection(12, 12, 2, 2);
	project.addRectangleInSelection(10, 10, 1, 5);

	project.addCompositeOperation();
	project.executeCompositeOperation();


	project.saveProject();



	project.destroyCompositeOperation();
	project.deleteSelection();

	system("pause");
	return 0;
}

int mainBMPsveOsimLayera() { //test operacija i selekcija
	try {
		Image project("Novi projekat");

		project.addLayer("primer.bmp", ImageType::BMP);

		project.addSelection("sel1");
		project.choseMainSelection("sel1");
		project.addRectangleInSelection(12, 12, 2, 2);
		project.addRectangleInSelection(10, 10, 1, 5);
		//project.fillMainSelectionWithColour(0, 0, 0);

		project.addBasicOperation();

		project.executeBasicOperation();

		project.destroyBasicOperation();

		project.addCompositeOperation();
		project.executeCompositeOperation();
		project.destroyCompositeOperation();

		project.deleteSelection();
		project.saveProject();
	}
	catch (ErrorInPixelValue e) {
		cout << e;
	}
	system("pause");
	return 0;
}

//FORMULA ZA LAYER:
// A = A0 + (1 - A0) * A1;
// R = R0 * A0 / A + R1 * (1 - A0) * A1 / A;
//prozirnostPixela * prozirnostLayera / 100 = alpha


//FINAL MAIN:
int main() {

	bool uneta;

	//bool first = false;

	bool saved = false;

	bool kraj = false;

	cout << "Unesite naziv slike: " << endl;
	string naziv;
	cin >> naziv;
	Image project(naziv);
	cout << endl;


	while (!kraj) {
		cout << "Unesite redni broj operacije:" << endl;
		int option;
		int number;
		cout << "1. Dodavanje sloja" << endl;
		cout << "2. Dodavanje selekcije" << endl;
		cout << "3. Izaberi glavnu selekciju" << endl;
		cout << "4. Obrisati glavnu selekciju" << endl;
		cout << "5. Dodati Rectangle u selekciju" << endl;
		cout << "6. Izvrsiti BasicOperation" << endl;
		cout << "7. Dodati kompozitnu operaciju" << endl;
		cout << "8. Izvrsiti kompozitnu operaciju" << endl;
		cout << "9. Obrisati kompozitnu operaciju" << endl;
		cout << "10. Popuniti glavnu selekciju datom bojom" << endl;
		cout << "11. Sacuvati projekat" << endl;
		cout << "12. Exportujte .fun fajl" << endl;
		cout << "13. Importujte iz .fun fajla" << endl;
		cout << "14. Kraj rada" << endl;

		cin >> option;

		switch (option) {
		case 1: {

			cout << "Izaberite koji tip vam odgovara:" << endl;
			int num;
			while (1) {
				cout << "1. BMP format" << endl;
				cout << "2. PAM format" << endl;
				cin >> num;
				if (num == 1 || num == 2) break;
				cout << endl;
			}
			string putanja;
			cout << "Unesite putanju fajla:" << endl;
			cin >> putanja;
			cout << endl;
			if (num == 1) project.addLayer(putanja, ImageType::BMP);
			else project.addLayer(putanja, ImageType::PAM);

		} break;

		case 2: {
			
			cout << "Unesite naziv selekcije:" << endl;
			string nazivSelekcije;
			cin >> nazivSelekcije;
			cout << endl;
			project.addSelection(nazivSelekcije);

		} break;

		case 3: {
			
			cout << "Unesite naziv glavne selekcije:" << endl;
			string nazivGlavneSelekcije;
			cin >> nazivGlavneSelekcije;
			cout << endl;
			project.addSelection(nazivGlavneSelekcije);

			project.choseMainSelection(nazivGlavneSelekcije);
		} break;

		case 4: {

			project.deleteSelection();
			cout << endl;

		} break;

		case 5: {
			int x, y, w, h;
			cout << "Uneti x:" << endl;//xywh
			cin >> x;
			cout << endl << "Uneti y:" << endl;
			cin >> y;
			cout << endl << "Uneti sirinu:" << endl;
			cin >> w;
			cout << endl << "Uneti visinu:" << endl;
			cin >> h;
			cout << endl;


			project.addRectangleInSelection(x, y, w, h);
		} break;

		case 6: {
			
			project.addBasicOperation();
			project.executeBasicOperation();
			project.destroyBasicOperation();

		} break;

		case 7: {

			project.addCompositeOperation();
			cout << endl;

		} break;

		case 8: {
			
			project.executeCompositeOperation();
			cout << endl;

		} break;

		case 9: {
			
			project.destroyCompositeOperation();
			cout << endl;

		} break;

		case 10: {
			
			cout << "Uneti komponentu RED:" << endl;
			int r;
			cin >> r;
			cout << endl;

			cout << "Uneti komponentu GREEN:" << endl;
			int g;
			cin >> g;
			cout << endl;

			cout << "Uneti komponentu BLUE:" << endl;
			int b;
			cin >> b;
			cout << endl;

			project.fillMainSelectionWithColour(r, g, b);

		} break;

		case 11: {
			
			project.saveProject(); //za sva 3 formata
			saved = true;

		} break;

		case 12: {
			
			cout << "Unesite putanju sa ekstenzijom .fun u koju exportujete CompositeOp:" << endl;
			string funPutanja;
			cin >> funPutanja;
			cout << endl;
			project.exportToFun(funPutanja);

		} break;

		case 13: {
			
			cout << "Unesite putanju sa ekstenzijom .fun iz koje importujete CompositeOp:" << endl;
			string funPutanjaImport;
			cin >> funPutanjaImport;
			cout << endl;
			project.importFromFun(funPutanjaImport);

		} break;

		case 14: {

			int finishNum;

			if (saved == false) {
				cout << "Niste sacuvali projekat!!!" << endl;
				cout << "1. Izadjite" << endl;
				cout << "2. Povratak na meni" << endl;
				cin >> finishNum;
				if (finishNum == 1) kraj = true; //kraj
			}
			else {
				kraj = true;//kraj
			}

			//break;
		} break;
		}
	}




	system("pause");
	return 0;
}