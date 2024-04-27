#include <iostream>
#include <io.h>
#include <fcntl.h>
#include "ConsoleFunctions.h"
using namespace std;


class PlayingCard {
	int rank;
	int suit;
	char color;
	bool faceup;
	bool top;
public:
	static const int diamond;
	static const int heart;
	static const int spade;
	static const int club;
	PlayingCard(int rnk = 0, int st = 0) {
		rank = 0;
		suit = 0;
		color = 'r';
		faceup = true;
		if (rnk > 0 && rnk <= 13 && st >= 0 && st < 4) {
			rank = rnk;
			suit = st;
			if (st == 2 || st == 3) {
				color = 'b';
			}
			else if (st == 0 || st == 1) {
				color = 'r';
			}
			top = true;
			faceup = true;
		}
	}
	void display(int x, int y);
	bool isFaceUp();
	void setFaceUp(bool);
	bool isTop();
	void setTop(bool);
	int getSuit();
	int getRank();
	char getColor();
};


class PileofCards {
	PlayingCard* pile;
	int top;
	int size;
	point startPt;
	point endPt;
public:
	PileofCards() {
		size = 0;
		pile = NULL;
		top = -1;
		startPt.x = 0;
		startPt.y = 0;
		endPt.x = 0;
		endPt.x = 0;
	}
	PileofCards(int s, int a = 0, int b = 0, int c = 6, int d = 8) {
		size = s;
		pile = new PlayingCard[size];
		top = -1;
		startPt.x = a;
		startPt.y = b;
		endPt.x = c;
		endPt.x = d;
	}
	PileofCards(PileofCards& poc) {
		delete pile;
		size = poc.size;
		endPt = poc.endPt;
		startPt = poc.startPt;
		top = poc.top;
		pile = new PlayingCard[size];
		for (int i = 0; i < size; i++) {
			pile[i] = poc.pile[i];
		}
	}
	~PileofCards() {
		delete pile;
	}
	void AddPlayingCardToThePile(PlayingCard card);
	PlayingCard RemovePlayingCardFromThePile();
	PlayingCard PeekingTopofthePile();
	bool IsPileEmpty();
	bool IsPileFull();
	int getTop();
	void setStartPt(int x, int y);
	point getStartPt();
	void setEndPt(int x, int y);
	point getEndPt();
	PileofCards& operator=(const PileofCards& poc);
	PlayingCard viewCard(int i);
	void SimpleDisplay();
	void CascadingDisplay();
};


class Deck {
private:
	PlayingCard* deck[52];
	int size;
public:
	Deck() {
		size = 52;
		int j = 0;
		for (int suit = 0; suit < 4; suit++) {
			for (int i = 1; i <= 13; i++) {
				deck[j] = new PlayingCard(i, suit);
				j++;
			}
		}
	}
	int getSize() {
		return size;
	}
	bool IsEmpty() {
		if (size <= 0) {
			return true;
		}
		else
			return false;
	}
	PlayingCard Remove(int i);
	~Deck() {
		for (int i = 0; i < size; i++) {
			delete[] deck[i];
		}
	}
	PlayingCard* getdeck(int x) {
		return deck[x];
	}
};


class Solitaire {
	Deck deckofCards;
	PileofCards stock;
	PileofCards waste;
	PileofCards home[4];
	PileofCards PlayingPile[7];
	ConsoleFunctions cf;
public:
	Solitaire();
	void Shuffle();
	void dealToPlayingPiles();
	void DisplayGame();
	~Solitaire() = default;
};


const int PlayingCard::diamond = 0;
const int PlayingCard::heart = 1;
const int PlayingCard::spade = 2;
const int PlayingCard::club = 3;
void PlayingCard::display(int x, int y) {
	ConsoleFunctions c;
	ConsoleColor ortxt = white;
	ConsoleColor orbg = black;
	ConsoleColor txt = dark_red;
	ConsoleColor undsc = black;
	if (faceup == true && top == true) {
		if (color == 'r') {
			c.SetColor(txt, ortxt);
		}
		if (color == 'b') {
			c.SetColor(orbg, ortxt);
		}
		if (rank > 9) {
			for (int i = 0; i < 7; i++) {
				c.SetCursorAt(x, y + i);
				for (int j = 0; j < 6; j++) {
					if (i == 0 && j == 0 || i == 6 && j == 4) {
						cout << rank;
						j++;
					}
					else if (i == 0 && j == 2 || i == 6 && j == 3) {
						int d = _setmode(_fileno(stdout), _O_U8TEXT);
						if (suit == 0) {
							wcout << L'\u2666';
						}
						else if (suit == 1) {
							wcout << L'\u2665';
						}
						else if (suit == 2) {
							wcout << L'\u2660';
						}
						else if (suit == 3) {
							wcout << L'\u2663';
						}
						d = _setmode(_fileno(stdout), _O_TEXT);
					}
					else {
						cout << " ";
					}
				}
			}
		}
		else {
			for (int i = 0; i < 7; i++) {
				c.SetCursorAt(x, y + i);
				for (int j = 0; j < 6; j++) {
					if (i == 0 && j == 0 || i == 6 && j == 5) {
						cout << rank;
					}
					else if (i == 0 && j == 1 || i == 6 && j == 4) {
						int d = _setmode(_fileno(stdout), _O_U8TEXT);
						if (suit == 0) {
							wcout << L'\u2666';
						}
						else if (suit == 1) {
							wcout << L'\u2665';
						}
						else if (suit == 2) {
							wcout << L'\u2660';
						}
						else if (suit == 3) {
							wcout << L'\u2663';
						}
						d = _setmode(_fileno(stdout), _O_TEXT);
					}
					else {
						cout << " ";
					}
				}
			}
		}
	}
	else if (faceup == false && top == true) {
		c.SetColor(txt, txt);
		for (int i = 0; i < 7; i++) {
			c.SetCursorAt(x, y + i);
			for (int j = 0; j < 6; j++) {
				cout << " ";
			}
		}
	}
	else if (faceup == true && top == false) {
		if (color == 'r') {
			c.SetColor(txt, ortxt);
		}
		if (color == 'b') {
			c.SetColor(orbg, ortxt);
		}
		if (rank > 9) {
			for (int i = 0; i < 2; i++) {
				c.SetCursorAt(x, y + i);
				for (int j = 0; j < 6; j++) {
					if (i == 0 && j == 0) {
						cout << rank;
						j++;
					}
					else if (i == 0 && j == 2) {
						int d = _setmode(_fileno(stdout), _O_U8TEXT);
						if (suit == 0) {
							wcout << L'\u2666';
						}
						else if (suit == 1) {
							wcout << L'\u2665';
						}
						else if (suit == 2) {
							wcout << L'\u2660';
						}
						else if (suit == 3) {
							wcout << L'\u2663';
						}
						d = _setmode(_fileno(stdout), _O_TEXT);
					}
					else {
						if (i == 0) {
							cout << " ";
						}
						else if (i == 1) {
							c.SetColor(undsc, ortxt);
							cout << "_";
						}
					}
				}
			}
		}
		else {
			for (int i = 0; i < 2; i++) {
				c.SetCursorAt(x, y + i);
				for (int j = 0; j < 6; j++) {
					if (i == 0 && j == 0) {
						cout << rank;
					}
					else if (i == 0 && j == 1) {
						int d = _setmode(_fileno(stdout), _O_U8TEXT);
						if (suit == 0) {
							wcout << L'\u2666';
						}
						else if (suit == 1) {
							wcout << L'\u2665';
						}
						else if (suit == 2) {
							wcout << L'\u2660';
						}
						else if (suit == 3) {
							wcout << L'\u2663';
						}
						d = _setmode(_fileno(stdout), _O_TEXT);
					}
					else {
						if (i == 0) {
							cout << " ";
						}
						else if (i == 1) {
							c.SetColor(undsc, ortxt);
							cout << "_";
						}
					}
				}
			}
		}
	}
	else if (faceup == false && top == false) {
		c.SetColor(txt, txt);
		for (int i = 0; i < 2; i++) {
			c.SetCursorAt(x, y + i);
			for (int j = 0; j < 6; j++) {
				if (i == 0) {
					cout << " ";
				}
				if (i == 1) {
					c.SetColor(undsc, txt);
					cout << "_";
				}
			}
		}
	}
	c.SetColor(ortxt, orbg);
}
bool PlayingCard::isFaceUp() {
	return faceup;
}
void PlayingCard::setFaceUp(bool x) {
	faceup = x;
}
bool PlayingCard::isTop() {
	return top;
}
void PlayingCard::setTop(bool x) {
	top = x;
}
int PlayingCard::getSuit() {
	return suit;
}
int PlayingCard::getRank() {
	return rank;
}
char PlayingCard::getColor() {
	return color;
}


void PileofCards::AddPlayingCardToThePile(PlayingCard card) {
	if (this->IsPileFull() == false) {
		if (top != -1) {
			pile[top].setTop(false);
		}
		pile[top + 1] = card;
		pile[top + 1].setTop(true);
		top++;
	}
	else if (this->IsPileFull() == true) {
		cout << "Pile is full!" << endl;
	}
}
PlayingCard PileofCards::RemovePlayingCardFromThePile() {
	PlayingCard temp;
	if (this->IsPileEmpty() == false) {
		temp = pile[top];
		top--;
		if (top != -1) {
			pile[top].setTop(true);
		}
	}
	else if (this->IsPileEmpty() == true) {
		cout << endl << "Pile is empty!" << endl;
		cout << "Printing previous card: " << endl;
		temp.setFaceUp(true);
		temp.setTop(true);
	}
	return temp;
}
PlayingCard PileofCards::PeekingTopofthePile() {
	return pile[top];
}
bool PileofCards::IsPileEmpty() {
	if (top <= -1) {
		return true;
	}
	else
		return false;
}
bool PileofCards::IsPileFull() {
	if (top >= size - 1) {
		return true;
	}
	else
		return false;
}
int PileofCards::getTop() {
	return top;
}
void PileofCards::setStartPt(int X, int Y) {
	startPt.x = X;
	startPt.y = Y;
}
point PileofCards::getStartPt() {
	return startPt;
}
void PileofCards::setEndPt(int X, int Y) {
	endPt.x = X;
	endPt.y = Y;
}
point PileofCards::getEndPt() {
	return endPt;
}
PileofCards& PileofCards::operator=(const PileofCards& poc) {
	if (this != &poc) {
		delete pile;
		size = poc.size;
		endPt = poc.endPt;
		startPt = poc.startPt;
		top = poc.top;
		pile = new PlayingCard[size];
		for (int i = 0; i < size; i++) {
			pile[i] = poc.pile[i];
		}
	}
	return *this;
}
PlayingCard PileofCards::viewCard(int i) {
	return pile[i];
}
void PileofCards::SimpleDisplay() {
	if (top == -1) {
		ConsoleColor ortxt = white;
		ConsoleColor orbg = black;
		ConsoleColor g = dark_green;
		ConsoleFunctions c;
		c.SetColor(g, g);
		for (int i = 0; i < 7; i++) {
			c.SetCursorAt(startPt.x, startPt.y + i);
			for (int j = 0; j < 6; j++) {
				cout << " ";
			}
		}
		c.SetColor(ortxt, orbg);
	}
	else if (top > -1) {
		pile[top].display(startPt.x, startPt.y);
	}
}
void PileofCards::CascadingDisplay() {
	if (top == -1) {
		ConsoleColor ortxt = white;
		ConsoleColor orbg = black;
		ConsoleColor g = dark_green;
		ConsoleFunctions c;
		c.SetColor(g, g);
		for (int i = 0; i < 7; i++) {
			c.SetCursorAt(startPt.x, startPt.y + i);
			for (int j = 0; j < 6; j++) {
				cout << " ";
			}
		}
		c.SetColor(ortxt, orbg);
	}
	else if (top > -1) {
		int b = startPt.y;
		for (int a = 0; a < size; a++) {
			pile[a].display(startPt.x, b);
			if (pile[a].isTop() == false) {
				b+=2;
			}
		}
	}
}


PlayingCard Deck::Remove(int i) {
	PlayingCard temp(0, 0);
	if (this->IsEmpty() == false) {
		temp = *deck[i];
		delete[] deck[i];
		for (int k = i; k < size; k++) {
			deck[k] = deck[k + 1];
		}
		size--;
	}
	else
		cout << "Deck is empty" << endl;
	return temp;
}


Solitaire::Solitaire() {
	PileofCards temp(52, 1, 1, 7, 9);
	stock = temp;
	PileofCards temp1(52, 8, 1, 14, 9);
	waste = temp1 ;
	int sx = 22, ex = 26;
	for (int i = 0; i < 4; i++) {
		PileofCards temp2(13, sx, 1, ex, 9);
		home[i] = temp2;
		sx += 7;
		ex += 7;
	}
	sx = 1;
	ex = 7;
	int ey = 25;
	int size = 1;
	for (int i = 0; i < 7; i++) {
		PileofCards temp3(size + 13, sx, 10, ex, ey);
		PlayingPile[i] = temp3;
		sx += 7;
		ex += 7;
		ey += 2;
		size++;
	}
}
void Solitaire::Shuffle() {
	int i;
	while (!deckofCards.IsEmpty()) {
		i = rand() % deckofCards.getSize();
		PlayingCard c = deckofCards.Remove(i);
		c.setFaceUp(false);
		c.setTop(true);
		stock.AddPlayingCardToThePile(c);
	}
}
void Solitaire::dealToPlayingPiles() {
	int x = 51;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j <= i; j++) {
			if (x >= 0) {
				PlayingCard temp = stock.RemovePlayingCardFromThePile();
				x--;
				temp.setFaceUp(false);
				temp.setTop(false);
				if (j == i) {
					temp.setFaceUp(true);
					temp.setTop(true);
				}
				PlayingPile[i].AddPlayingCardToThePile(temp);
			}
		}
	}
}
void Solitaire::DisplayGame() {
	stock.SimpleDisplay();
	waste.SimpleDisplay();
	for (int i = 0; i < 4; i++) {
		home[i].SimpleDisplay();
	}
	for (int i = 0; i < 7; i++) {
		PlayingPile[i].CascadingDisplay();
	}
}


int main() {
	//		TEST 1

	//PlayingCard A(3, PlayingCard::spade);
	//PlayingCard B(2, PlayingCard::spade);
	//PlayingCard C(4, PlayingCard::heart);
	//PlayingCard D(5, PlayingCard::club);
	//PlayingCard E(3, PlayingCard::diamond);
	//PlayingCard temp(3, PlayingCard::heart);
	//PileofCards pile1(5);
	///****** Adding cards in pile ********/
	//pile1.AddPlayingCardToThePile(A);
	//pile1.AddPlayingCardToThePile(B);
	//pile1.AddPlayingCardToThePile(C);
	//pile1.AddPlayingCardToThePile(D);
	//pile1.AddPlayingCardToThePile(E);
	//
	//pile1.AddPlayingCardToThePile(temp);
	///****** Removing Cards from pile *****/
	//temp = pile1.RemovePlayingCardFromThePile();

	//temp.display(20, 0);

	//temp = pile1.RemovePlayingCardFromThePile(); //5 of Club should be removed
	//temp.display(0, 10);
	//temp = pile1.RemovePlayingCardFromThePile(); //4 of Heart should be removed
	//temp.display(10, 10);
	//temp = pile1.RemovePlayingCardFromThePile(); //2 of Spade should be removed
	//temp.display(20, 10);
	//temp = pile1.RemovePlayingCardFromThePile(); //3 of Spade should be removed
	//temp.display(30, 10);
	//temp = pile1.RemovePlayingCardFromThePile(); //Now the pile is empty
	//temp.display(40, 20);

	//		TEST 2
	
	//Deck D1;
	//PlayingCard A(0, 0);
	//int y = 0;
	//A = D1.Remove(0);
	//A.display(0, y);
	//y = y + 10;

	//A = D1.Remove(0);
	//A.display(0, 10);
	//y = y + 10;
	//A = D1.Remove(0);
	//A.display(0, 20); // three cards removed
	//y = y + 10;
	//while (!D1.IsEmpty())
	//{
	//	A = D1.Remove(0);
	//	A.display(0, y);
	//	y = y + 10;
	//}
	
	//		SELF TEST
	
	//Deck D1;
	//PlayingCard A(0, 0);
	//int y = 0;
	//A = D1.Remove(0);
	//A.display(0, y);
	////y = y + 10;
	//system("pause");
	//system("cls");	//	clear screen added for convenience

	//A = D1.Remove(0);
	//A.display(0, y);
	////y = y + 10;
	//system("pause");
	//system("cls");	//	clear screen added for convenience

	//A = D1.Remove(0);
	//A.display(0, y); // three cards removed
	////y = y + 10;
	//system("pause");
	//system("cls");	//	clear screen added for convenience
	//while (!D1.IsEmpty())
	//{
	//	A = D1.Remove(0);
	//	A.display(0, y);
	//	//y = y + 10;
	//	system("pause");
	//	system("cls");	//	clear screen added for convenience
	//}

	//		BONUS PART

	Solitaire S;
	S.Shuffle();
	S.dealToPlayingPiles();
	S.DisplayGame();

	return 0;
}