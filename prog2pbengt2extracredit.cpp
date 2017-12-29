/*
**Prog2: Trinity
**Peter Bengtson
**Tuesday 11am: Itika Gupta
**January 30, 2016
**Notepad++, Windows 7
**
**Description: Plays the board game Trinity, in which players alternate taking turns placing pieces
**in attempt to make a one of the winning configurations before their opponent.
*/

#include <stdio.h>

//global variable only added for extra credit portion
bool cpu_turn = false;

//prints basic project information
void printInfo(){ 
	printf("\nProgram #2: Trinity \n"
			"Author: Peter Bengtson\n"
			"Lab: Tues 11am\n"
			"Date: January 30, 2016\n"
			"System: Notepad++ on Windows 7\n\n");
	return;
}

//prints the game instructions
void printInstructions(){ 
	printf("\nWelcome to Trinity, the game where there's three ways\n"
			"to get three in a row, in one of three rows or columns,\n"
			"or diagonals. Play alternates between the two players.\n"
			"On each move select any available piece and an open\n"
			"board destination location. A winning configuration\n"
			"is three of the same set in a row (e.g. b a c, A B C\n"
			"or 3 2 1), all 3 from the same set position (e.g. A 1 a,\n"
			"B 2 b or c 3 C), or three in a row where each is a\n"
			"different set member (1st, 2nd, 3rd) such as 2 A c,\n"
			"a B 3 or C 1 b.\n"
			"------------------------------------\n");
	return;
	
}

//prints the current board
void printBoard(char b[]){ 
	printf("------------------------------------\n");
	printf(" -----------   Positions:\n");
	printf("| %c | %c | %c |    1  2  3\n", b[0], b[1], b[2]); 
	printf("|-----------|\n");
	printf("| %c | %c | %c |    4  5  6\n", b[3], b[4], b[5]); 
	printf("|-----------|\n");
	printf("| %c | %c | %c |    7  8  9\n", b[6], b[7], b[8]); 
	printf(" -----------\n");
	return;
}

//checks if piece is valid
char checkPiece(char c, char p[]){ 
	int i;
	for (i=0; i<10; i++){
		if (p[i]==c)
			return ' ';
	}
	return c;
}

//removes piece from array
void removePiece(char c, char p[]){ 
	int i;
	for (i=0; i<10; i++){
		if (p[i]==c)
			p[i]=' ';
	}
	return;
}

//checks what row the character is in
int checkRow(char c){ 
	if (c=='A' || c =='B' || c=='C')
		return 1;
	if (c=='1' || c =='2' || c=='3')
		return 2;
	if (c=='a' || c =='b' || c=='c')
		return 3;	
	
	return -1;
}

//checks what col the character is in
int checkCol(char c){ 
	if (c=='A' || c =='1' || c=='a')
		return 1;
	if (c=='B' || c =='2' || c=='b')
		return 2;
	if (c=='C' || c =='3' || c=='c')
		return 3;	
	
	return -1;	
}

//checks all winning conditions for specific characters
bool checkCond(char c1, char c2, char c3){ 
	if (c1==' ' || c2==' ' || c3==' ')
		return false;
	
	//assigns rows and col for each character
	int c1r, c2r, c3r, c1c, c2c, c3c;
	c1r = checkRow(c1);
	c2r = checkRow(c2);
	c3r = checkRow(c3);
	c1c = checkCol(c1);
	c2c = checkCol(c2);
	c3c = checkCol(c3);
	
	//checks if all are in same row
	if (c1r == c2r && c2r == c3r){
		if (cpu_turn==false)
			printf("\nCongratulations, you win with %c %c %c\n", c1, c2, c3);		
		return true;
	}
	
	//checks if all are in same col
	if (c1c == c2c && c2c == c3c){
		if (cpu_turn==false)
			printf("\nCongratulations, you win with %c %c %c\n", c1, c2, c3);		
		return true;
	}
	
	//checks if all are in different rows and cols
	if (c1r != c2r && c2r != c3r && c1r != c3r){
		if (c1c != c2c && c2c!=c3c && c1c!=c3c){
			if (cpu_turn==false)
				printf("\nCongratulations, you win with %c %c %c\n", c1, c2, c3);
			return true;
		}
	}
	return false;
}

//checks winning conditions for the last character played
bool checkWin(int bIn, char b[]){ 
	//rows
	if (bIn==1 || bIn==2 || bIn==3)
		if (checkCond(b[0], b[1], b[2]))
			return true;
	if (bIn==4 || bIn==5 || bIn== 6)
		if (checkCond(b[3], b[4], b[5]))
			return true;
	if (bIn==7 || bIn==8 || bIn== 9)
		if (checkCond(b[6], b[7], b[8]))
			return true;	
		
	//cols
	if (bIn==1 || bIn==4 || bIn==7)
		if (checkCond(b[0], b[3], b[6]))
			return true;
	if (bIn==2 || bIn==5 || bIn== 8)
		if (checkCond(b[1], b[4], b[7]))
			return true;
	if (bIn==3 || bIn==6 || bIn== 9)
		if (checkCond(b[2], b[5], b[8]))
			return true;	
		
	//diagonal
	if (bIn==1 || bIn==5 || bIn==9)
		if (checkCond(b[0], b[4], b[8]))
			return true;
	if (bIn==3 || bIn==5 || bIn==7)
		if (checkCond(b[2], b[4], b[6]))
			return true;
	
	return false;
}

//finds move for cpu
bool cpuFindMove(char bTemp[], char b[], char p[]){ 
	int i;
	int j;
	
	//tests every input until it finds a winning move. Returns false if winning move not found.
	for (i=0; i<9; i++){
		if (bTemp[i]==' '){
			for (j=0; j<9; j++){
				if (p[j]!=' '){				
					bTemp[i]=p[j]; 
					if (checkWin(i+1, bTemp)==true){ //checks if current iteration for winning move
						b[i]=p[j]; 
						removePiece(p[j], p); 
						bTemp[i]=' ';
						return true;
					}
					bTemp[i]=' '; //resets the tested value if no winning move found.
				}
			}
		}
	}
	return false;
}

bool cpuTurn(char b[], char p[]){
	char bTemp[] = "         ";
	int i;
	
	for (i=0; i<9; i++)
		bTemp[i]=b[i];
	
	//checks if cpu can win this move
	if (cpuFindMove(bTemp, b, p)==true)
		return true;
	
	char bTemp2[] = "         ";	
	char pTemp[] = "         ";
	int j;
	int k;
	
	for (i=0; i<9; i++)
		pTemp[i]=p[i];	
	
	for (i=0; i<9; i++)
		bTemp2[i]=b[i];
	
	//checks for a move that doesn't result in a lose (within the next move)
	for (i=0; i<9; i++){
		if (bTemp2[i]==' '){
			for (j=0; j<9; j++){
				if (pTemp[j]!=' '){				
					bTemp2[i]=pTemp[j];
					removePiece(pTemp[j], pTemp);
					if (cpuFindMove(bTemp2, bTemp, pTemp)==false){
						b[i]=p[j];
						removePiece(p[j], p);	
						return false;
					}
					bTemp2[i]=' ';
					for (k=0; k<9; k++)
						pTemp[k]=p[k];				
				}
			}
		}
	}
	
	//human player has guarenteed win, plays first available move
	for (i=0; i<9; i++){
		if (b[i]==' '){
			for (j=0; j<9; j++){
				if (p[j]!=' '){
					b[i]=p[j];
					removePiece(p[j], p);
					return false;
				}
			}
		}
	}
	return false;
}

int main()
{
	printInfo();
	printInstructions();
	
	//initialize pieces and board
	char p[] = "ABC123abc";
	char b[] = "         ";
	
	printBoard(b);
	
	//initialize chars for user input
	char pIn, tempC;
	int bIn;
	bool validInput = false;
	
	//loops through the 9 moves
	int move;
	for (move = 1; move < 10; move++){ 
		printf("Pieces available to play:\n   %c %c %c\n   %c %c %c\n   %c %c %c\n\n", 
				p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);

		//get user input
		if (move%2 ==1){
			cpu_turn=false;
			printf("1. Player 1 enter piece and position: ");
			scanf("%c%d%c", &pIn, &bIn, &tempC);
			
			//check if input is valid
			validInput = false;
			while (validInput == false){	
				tempC = checkPiece(pIn, p); //holds value of ' ' if piece is valid
				if (tempC != ' '){
					printf("*** Piece %c is not available. Please retry: ", tempC);
					scanf("%c%d%c", &pIn, &bIn, &tempC);
				}
				else if (b[bIn-1]!=' '){ //checks if the board location is ' '
					printf("*** Location %d is already taken. Please retry: ", bIn);
					scanf("%c%d%c", &pIn, &bIn, &tempC);
				}
				else
					validInput = true;
			}

			//place input on board. replace piece value with ' '
			b[bIn-1]=pIn;
			removePiece(pIn, p);
		}
		else{
			cpu_turn=true;
			if (cpuTurn(b, p)==true)
				move = 20;
		}
		
		printBoard(b);
		
		if (checkWin(bIn, b)){ //breaks loop if winning move was played
			move = 20;
			if (cpu_turn==true)
				printf("\nCPU wins!\n");
		}
		
		if (move ==9) //prints draw if 9th move was played without meeting winning condition
			printf("\n Draw!");
	}
	
	return 1;
}