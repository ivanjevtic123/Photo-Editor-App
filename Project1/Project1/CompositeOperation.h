#pragma once

#include "Operation.h"
#include "BasicOperations.h"
#include "BasicOperations.h"

class CompositeOperation : public Operation {
private:

	string name;

	vector<Operation *> operations;

	bool flagSelection = false;
	friend class Image;
public:

	CompositeOperation(string nn, bool sel) : name(nn), Operation(sel) {}

	CompositeOperation() {
		operations.clear();
	}

	void execution(Pixel &curr) override { //IZVRSAVANJE SVIH OPERACIJA U KOMPOZITNOJ!!!
		for (int i = 0; i < operations.size(); i++) {
			operations[i]->execution(curr);
		}
		//Check&Set(curr);
	}

	OperationType getOperationType() override { return COMP; }

	void addOperation() { //sve sam trebao u while da strpam!!!//U main da ubacim!!!
		bool kraj = false;
		while (!kraj) {
			cout << "Unesite redni broj operacije koju zelite da dodate:" << endl;
			int option;
			int number;
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
			cout << "16. Ne zelim vise da dodajem" << endl;

			cin >> option;

			switch (option) {
			case 1: {
				cout << "Unesite const int:" << endl;
				cin >> number;
				cout << endl;
				if (operations.size() != 0) operations[operations.size() - 1]->setLastFlag(false);
				//dodajem operaciju koju tu i kreiram
				Saberi *opp = new Saberi(number, getSelectionExists(), true, true);
				operations.push_back(opp);
			} break;

			case 2: {
				cout << "Unesite const int:" << endl;
				cin >> number;
				cout << endl;
				if (operations.size() != 0) operations[operations.size() - 1]->setLastFlag(false);
				//dodajem operaciju koju tu i kreiram
				Oduzmi *opp = new Oduzmi(number, getSelectionExists(), true, true);
				operations.push_back(opp);
			} break;

			case 3: {
				cout << "Unesite const int:" << endl;
				cin >> number;
				cout << endl;
				if (operations.size() != 0) operations[operations.size() - 1]->setLastFlag(false);
				//dodajem operaciju koju tu i kreiram
				InverznoOduzmi *opp = new InverznoOduzmi(number, getSelectionExists(), true, true);
				operations.push_back(opp);
			} break;

			case 4: {
				cout << "Unesite const int:" << endl;
				cin >> number;
				cout << endl;
				if (operations.size() != 0) operations[operations.size() - 1]->setLastFlag(false);
				//dodajem operaciju koju tu i kreiram
				Pomnozi *opp = new Pomnozi(number, getSelectionExists(), true, true);
				operations.push_back(opp);
			} break;

			case 5: {
				cout << "Unesite const int:" << endl;
				cin >> number;
				cout << endl;
				if (operations.size() != 0) operations[operations.size() - 1]->setLastFlag(false);
				//dodajem operaciju koju tu i kreiram
				Podeli *opp = new Podeli(number, getSelectionExists(), true, true);
				operations.push_back(opp);
			} break;
			case 6: {
				cout << "Unesite const int:" << endl;
				cin >> number;
				cout << endl;
				if (operations.size() != 0) operations[operations.size() - 1]->setLastFlag(false);
				//dodajem operaciju koju tu i kreiram
				InverznoPodeli *opp = new InverznoPodeli(number, getSelectionExists(), true, true);
				operations.push_back(opp);
			} break;

			case 7: {
				cout << "Unesite const int:" << endl;
				cin >> number;
				cout << endl;
				if (operations.size() != 0) operations[operations.size() - 1]->setLastFlag(false);
				//dodajem operaciju koju tu i kreiram
				Power *opp = new Power(number, getSelectionExists(), true, true);
				operations.push_back(opp);
			} break;

			case 8: {
				//cout << "Unesite const int:" << endl;
				//cin >> number;
				cout << endl;
				if (operations.size() != 0) operations[operations.size() - 1]->setLastFlag(false);
				//dodajem operaciju koju tu i kreiram
				Log *opp = new Log(getSelectionExists(), true, true);
				operations.push_back(opp);
			} break;

			case 9: {
				//cout << "Unesite const int:" << endl;
				//cin >> number;
				cout << endl;
				if (operations.size() != 0) operations[operations.size() - 1]->setLastFlag(false);
				//dodajem operaciju koju tu i kreiram
				Abs *opp = new Abs(getSelectionExists(), true, true);
				operations.push_back(opp);
			} break;

			case 10: {
				cout << "Unesite const int:" << endl;
				cin >> number;
				cout << endl;
				if (operations.size() != 0) operations[operations.size() - 1]->setLastFlag(false);
				//dodajem operaciju koju tu i kreiram
				Min *opp = new Min(number, getSelectionExists(), true, true);
				operations.push_back(opp);
			} break;

			case 11: {
				cout << "Unesite const int:" << endl;
				cin >> number;
				cout << endl;
				if (operations.size() != 0) operations[operations.size() - 1]->setLastFlag(false);
				//dodajem operaciju koju tu i kreiram
				Max *opp = new Max(number, getSelectionExists(), true, true);
				operations.push_back(opp);
			} break;

			case 12: {
				//cout << "Unesite const int:" << endl;
				//cin >> number;
				cout << endl;
				if (operations.size() != 0) operations[operations.size() - 1]->setLastFlag(false);
				//dodajem operaciju koju tu i kreiram
				Inverzija *opp = new Inverzija(getSelectionExists(), true, true);
				operations.push_back(opp);
			} break;

			case 13: {
				//cout << "Unesite const int:" << endl;
				//cin >> number;
				cout << endl;
				if (operations.size() != 0) operations[operations.size() - 1]->setLastFlag(false);
				//dodajem operaciju koju tu i kreiram
				PretvoriUSivo *opp = new PretvoriUSivo(getSelectionExists(), true, true);
				operations.push_back(opp);
			} break;

			case 14: {
				//cout << "Unesite const int:" << endl;
				//cin >> number;
				cout << endl;
				if (operations.size() != 0) operations[operations.size() - 1]->setLastFlag(false);
				//dodajem operaciju koju tu i kreiram
				PretvoriUCrnoBelo *opp = new PretvoriUCrnoBelo(getSelectionExists(), true, true);
				operations.push_back(opp);
			} break;

			case 15: { //Medijana

			} break;
			case 16: {
				kraj = true;
				break;
			} break;
			}
		}
	}

	void importCompositeOperation(string path); //iz .fun 

	void exportCompositeOperation(string path); // u .fun

	void setLastFlag(bool flag) override {} //ne koristim ovde, ali overridujem da ne budem apstraktan


	int getNum() const override {
		return -1;
	}
};