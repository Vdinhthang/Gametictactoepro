#include <iostream>
#include <SDL.h>
#include <vector>
#include <SDL_image.h>
#include "defs.h"
#include "Globals.h"
#include "clickcontrol.h"
#include "soundandmusic.h"
#include "screenplay.h"
#include "ttfont.h"

using namespace std;
sound Sound1;
screen Screen1;
Clickcontrol clickcontrol1;

bool checkCells[GRID_SIZE][GRID_SIZE] = { 0 };
bool checkCells2[GRID_SIZEMORE][GRID_SIZEMORE] = { 0 };
bool Checkwin = 0;
bool Checkwinmore = 0;
// 2players 3*3
void Clickcontrol::create() {
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			cells[i][j] = { j * CELL_SIZE ,(i + 1) * CELL_SIZE,CELL_SIZE,CELL_SIZE };
		}
	}
	backgame = { 0, 170 , 90, 30 };
}
bool Clickcontrol::handleClick(int mouseX, int mouseY, int& count) {
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			SDL_Rect cell = cells[i][j];
			if (mouseX >= cell.x && mouseX < cell.x + cell.w &&
				mouseY >= cell.y && mouseY < cell.y + cell.h && checkCells[i][j] == 0) {
				count += 1;
				checkCells[i][j] = 1;
				Cells[i][j] = temptimage;
				SDL_RenderCopy(renderer, temptimage, NULL, &cells[i][j]);
				Sound1.clicksound();
				temptimage = (temptimage == X_CELL) ? O_CELL : X_CELL;
				return true;
			}
		}
	}
	if (mouseX >= backgame.x && mouseX < backgame.x + backgame.w && mouseY >= backgame.y && mouseY < backgame.y + backgame.h) {
		clickcontrol1.resetClicks(count);
		Screen1.screenclosetempt();
		Screen1.screenwelcome();
		Screen1.screenplaymore();
	}
	return false;
}
void Clickcontrol::AIClick(int& count) {
	vector<pair<int, int>> emptyCells;
	for (int i = 0; i < GRID_SIZE; i++)
		for (int j = 0; j < GRID_SIZE; j++)
			if (checkCells[i][j] == 0)
				emptyCells.push_back({ i, j });

	if (!emptyCells.empty()) {
		srand(time(0));
		int choice = rand() % emptyCells.size();
		int row = emptyCells[choice].first;
		int col = emptyCells[choice].second;
		count++;
		checkCells[row][col] = 1;
		Cells[row][col] = temptimage;
		SDL_RenderCopy(renderer, temptimage, NULL, &cells[row][col]);
		temptimage = (temptimage == X_CELL) ? O_CELL : X_CELL;
	}
}

void Clickcontrol::AIsmartclick(int& count) {
	int scoreBoard[GRID_SIZE][GRID_SIZE] = { 0 };
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			if (checkCells[i][j] == 0) {
				if (i == 1 && j == 1) scoreBoard[i][j] = 3;
				else if ((i == 0 && j == 0) || (i == 0 && j == 2) ||
					(i == 2 && j == 0) || (i == 2 && j == 2)) {
					scoreBoard[i][j] = 2;
				}
				else scoreBoard[i][j] = 1;

				checkCells[i][j] = 1;
				Cells[i][j] = O_CELL;
				if (Checkwin == 1) {
					scoreBoard[i][j] += 100;
				}

				Cells[i][j] = X_CELL;
				if (Checkwin == -1) {
					scoreBoard[i][j] += 50;
				}

				checkCells[i][j] = 0;
				Cells[i][j] = NULL;
			}
		}
	}
	int maxScore = -1;
	vector<pair<int, int>> bestMoves;

	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			if (checkCells[i][j] == 0 && scoreBoard[i][j] > maxScore) {
				maxScore = scoreBoard[i][j];
				bestMoves.clear();
				bestMoves.push_back({ i, j });
			}
			else if (checkCells[i][j] == 0 && scoreBoard[i][j] == maxScore) {
				bestMoves.push_back({ i, j });
			}
		}
	}
	if (!bestMoves.empty()) {
		int randIdx = rand() % bestMoves.size();
		int row = bestMoves[randIdx].first;
		int col = bestMoves[randIdx].second;
		checkCells[row][col] = 1;
		Cells[row][col] = O_CELL;
		count++;
		SDL_RenderCopy(renderer, O_CELL, NULL, &cells[row][col]);
		temptimage = X_CELL;
	}
}

void Clickcontrol::draw() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	for (int i = 1; i <= GRID_SIZE; i++) {
		SDL_RenderDrawLine(renderer, 0, i * CELL_SIZE, SCREEN_WIDTH, i * CELL_SIZE);
	}
	for (int j = 1; j <= GRID_SIZE; j++) {
		SDL_RenderDrawLine(renderer, j * CELL_SIZE, CELL_SIZE, j * CELL_SIZE, SCREEN_HEIGHT);
	}
	SDL_RenderDrawLine(renderer, 0, 170, 90, 170);
	SDL_RenderDrawLine(renderer, 90, 170, 90, 200);
}
void Clickcontrol::checkwin(int count) {
	bool checkwin = 0;
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for (int i = 0; i <= GRID_SIZE - 1; i++) {
		if (Cells[i][0] == Cells[i][1] && Cells[i][1] == Cells[i][2] && Cells[i][0] != NULL) {
			SDL_RenderDrawLine(renderer, 0, ((i + 1) * 1.0 + 0.5) * CELL_SIZE, SCREEN_WIDTH, ((i + 1) * 1.0 + 0.5) * CELL_SIZE);
			checkwin = 1;
		}
	}
	for (int i = 0; i <= GRID_SIZE - 1; i++) {
		if (Cells[0][i] == Cells[1][i] && Cells[2][i] == Cells[1][i] && Cells[0][i] != NULL) {
			SDL_RenderDrawLine(renderer, (i * 1.0 + 0.5) * CELL_SIZE, CELL_SIZE, (i * 1.0 + 0.5) * CELL_SIZE, SCREEN_HEIGHT);
			checkwin = 1;
		}
	}
	if (Cells[0][0] == Cells[1][1] && Cells[1][1] == Cells[2][2] && Cells[0][0] != NULL) {
		SDL_RenderDrawLine(renderer, 0, CELL_SIZE, SCREEN_WIDTH, SCREEN_HEIGHT);
		checkwin = 1;
	}
	if (Cells[0][2] == Cells[1][1] && Cells[2][0] == Cells[1][1] && Cells[0][2] != NULL) {
		SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT, SCREEN_WIDTH, CELL_SIZE);
		checkwin = 1;
	}
	if (checkwin == 1 || (count == 9 && checkwin == 0)) {
		if (checkwin == 1) {
			if (count % 2 != 0) {
				Checkwin = -1;
				temptimage = IMG_LoadTexture(renderer, "D:\\2024-2025\\ky2\\LTNC\\codeproject\\codeproject\\image\\X_win.png");
			}
			else {
				Checkwin = 1;
				temptimage = IMG_LoadTexture(renderer, "D:\\2024-2025\\ky2\\LTNC\\codeproject\\codeproject\\image\\O_win.png");
			}
			Sound1.playwin();
		}
		else if (count == 9 && checkwin == 0) {
			temptimage = IMG_LoadTexture(renderer, "D:\\2024-2025\\ky2\\LTNC\\codeproject\\codeproject\\image\\tie.png");
			Sound1.tiesound();
		}
		SDL_Rect rect;
		rect.x = CELL_SIZE * 1.2;
		rect.y = CELL_SIZE * 1.2 + CELL_SIZE;
		rect.w = CELL_SIZE * 0.6;
		rect.h = CELL_SIZE * 0.6;
		SDL_RenderCopy(renderer, temptimage, NULL, &rect);
		for (int i = 0; i < GRID_SIZE; i++) {
			for (int j = 0; j < GRID_SIZE; j++) {
				checkCells[i][j] = 1;
			}
		}
	}
}
void Clickcontrol::resetClicks(int& count) {
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			temptimage = Empty_CELL;
			checkCells[i][j] = 0;
			SDL_RenderCopy(renderer, temptimage, NULL, &cells[i][j]);
			Cells[i][j] = NULL;
		}
	}
	draw();
	SDL_RenderPresent(renderer);
	temptimage = X_CELL;
	count = 0;
}
//10*10
void Clickcontrol::handleClickmore(int mouseX, int mouseY, int& count) {
	for (int i = 0; i < GRID_SIZEMORE; i++) {
		for (int j = 0; j < GRID_SIZEMORE; j++) {
			SDL_Rect cell = cellsmore[i][j];
			if ((mouseX >= cell.x && mouseX < cell.x + cell.w &&
				mouseY >= cell.y && mouseY < cell.y + cell.h) && (checkCells2[i][j] == 0)) {
				count += 1;
				Cellsmore[i][j] = temptimage;
				checkCells2[i][j] = 1;
				SDL_RenderCopy(renderer, temptimage, NULL, &cellsmore[i][j]);
				Sound1.clicksound();
				temptimage = (temptimage == X_CELL) ? O_CELL : X_CELL;
			}
		}
	}
	if (mouseX >= backgame.x && mouseX < backgame.x + backgame.w && mouseY >= backgame.y && mouseY < backgame.y + backgame.h) {
		clickcontrol1.resetClicksmore(count);
		Screen1.screenclosetempt();
		Screen1.screenwelcome();
		Screen1.screenplay2();
	}
}
void Clickcontrol::resetClicksmore(int& count) {
	for (int i = 0; i < GRID_SIZEMORE; i++) {
		for (int j = 0; j < GRID_SIZEMORE; j++) {
			temptimage = Empty_CELL;
			checkCells2[i][j] = 0;
			SDL_RenderCopy(renderer, temptimage, NULL, &cellsmore[i][j]);
			Cellsmore[i][j] = NULL;
		}
	}
	drawmore();
	SDL_RenderPresent(renderer);
	Checkwinmore = 0;
	temptimage = X_CELL;
	count = 0;
}
void Clickcontrol::createmore() {
	for (int i = 0; i < GRID_SIZEMORE; i++) {
		for (int j = 0; j < GRID_SIZEMORE; j++) {
			cellsmore[i][j] = { j * CELL_SIZEMORE ,(i)*CELL_SIZEMORE + CELL_SIZE,CELL_SIZEMORE,CELL_SIZEMORE };
		}
	}
}
void Clickcontrol::drawmore() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	for (int i = 0; i <= GRID_SIZEMORE; i++) {
		SDL_RenderDrawLine(renderer, 0, i * CELL_SIZEMORE + CELL_SIZE, SCREEN_WIDTH, i * CELL_SIZEMORE + CELL_SIZE);
	}
	for (int j = 1; j <= GRID_SIZEMORE; j++) {
		SDL_RenderDrawLine(renderer, j * CELL_SIZEMORE, CELL_SIZE, j * CELL_SIZEMORE, SCREEN_HEIGHT);
	}
	SDL_RenderDrawLine(renderer, 0, 170, 90, 170);
	SDL_RenderDrawLine(renderer, 90, 170, 90, 200);
}
void Clickcontrol::checkwinmore(int count) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for (int i = 0; i < GRID_SIZEMORE; i++) {
		for (int j = 0; j <= GRID_SIZEMORE - TOTALNEED; j++) {
			bool checkdiagonaldown = 1;
			bool checkdiagonalup = 1;
			bool checkdiagonalrevdown = 1;
			bool checkdiagonalrevup = 1;
			bool checkrow = 1;
			bool checkcol = 1;
			for (int k = 0; k < TOTALNEED - 1; k++) {
				if ((Cellsmore[i][j + k] != Cellsmore[i][j + k + 1]) || Cellsmore[i][j + k] == NULL) {
					checkrow = 0;
				}
				if ((Cellsmore[j + k][i] != Cellsmore[j + k + 1][i]) || Cellsmore[j + k][i] == NULL) {
					checkcol = 0;
				}
				if (j + k + i < GRID_SIZEMORE && GRID_SIZEMORE - 1 - j - k - i > 0) {
					if (Cellsmore[j + k + i][j + k] != Cellsmore[j + k + i + 1][j + k + 1] || Cellsmore[j + k + i][j + k] == NULL) {
						checkdiagonaldown = 0;
					}
					if (Cellsmore[j + k][j + k + i] != Cellsmore[j + k + 1][j + k + i + 1] || Cellsmore[j + k][j + k + i] == NULL) {
						checkdiagonalup = 0;
					}
					if (Cellsmore[GRID_SIZEMORE - 1 - (j + k)][j + k + i] != Cellsmore[GRID_SIZEMORE - 1 - (j + k + 1)][j + k + i + 1] || Cellsmore[GRID_SIZEMORE - 1 - (j + k)][j + k + i] == NULL) {
						checkdiagonalrevdown = 0;
					}
					if (Cellsmore[GRID_SIZEMORE - 1 - (j + k) - i][j + k] != Cellsmore[GRID_SIZEMORE - 1 - (j + k + 1) - i][j + k + 1] || Cellsmore[GRID_SIZEMORE - 1 - i - (j + k)][j + k] == NULL) {
						checkdiagonalrevup = 0;
					}
				}
				else {
					checkdiagonaldown = 0;
					checkdiagonalup = 0;
					checkdiagonalrevdown = 0;
					checkdiagonalrevup = 0;
				}
			}
			if (checkdiagonalrevdown == 1) {
				Checkwinmore = 1;
				SDL_RenderDrawLine(renderer, (j + i) * CELL_SIZEMORE, CELL_SIZE + (GRID_SIZEMORE - j) * CELL_SIZEMORE, (j + i + TOTALNEED) * CELL_SIZEMORE, CELL_SIZE + (GRID_SIZEMORE - j - TOTALNEED) * CELL_SIZEMORE);
			}
			if (checkdiagonalrevup == 1) {
				Checkwinmore = 1;
				SDL_RenderDrawLine(renderer, (j)*CELL_SIZEMORE, CELL_SIZE + (GRID_SIZEMORE - j - i) * CELL_SIZEMORE, (j + TOTALNEED) * CELL_SIZEMORE, CELL_SIZE + (GRID_SIZEMORE - j - i - TOTALNEED) * CELL_SIZEMORE);
			}
			if (checkdiagonaldown == 1) {
				Checkwinmore = 1;
				SDL_RenderDrawLine(renderer, (j)*CELL_SIZEMORE, CELL_SIZE + (j + i) * CELL_SIZEMORE, (j + TOTALNEED) * CELL_SIZEMORE, (j + TOTALNEED + i) * CELL_SIZEMORE + CELL_SIZE);
			}
			if (checkdiagonalup == 1) {
				Checkwinmore = 1;
				SDL_RenderDrawLine(renderer, (j + i) * CELL_SIZEMORE, CELL_SIZE + (j)*CELL_SIZEMORE, (j + TOTALNEED + i) * CELL_SIZEMORE, (j + TOTALNEED) * CELL_SIZEMORE + CELL_SIZE);
			}
			if (checkrow == 1 || checkcol == 1) {
				Checkwinmore = 1;
				if (checkrow == 1) {
					SDL_RenderDrawLine(renderer, j * (CELL_SIZEMORE), CELL_SIZE + (i * 1.0 + 0.5) * CELL_SIZEMORE, (j + TOTALNEED) * CELL_SIZEMORE, CELL_SIZE + (i * 1.0 + 0.5) * CELL_SIZEMORE);
				}
				if (checkcol == 1) {
					SDL_RenderDrawLine(renderer, (i * 1.0 + 0.5) * CELL_SIZEMORE, CELL_SIZE + j * CELL_SIZEMORE, (i * 1.0 + 0.5) * CELL_SIZEMORE, CELL_SIZE + CELL_SIZEMORE * (j + TOTALNEED));
				}
			}
		}
	}

	if (Checkwinmore == 1 || (count == GRID_SIZEMORE * GRID_SIZEMORE && Checkwinmore == 0)) {
		for (int i = 0; i < GRID_SIZEMORE; i++) {
			for (int j = 0; j < GRID_SIZEMORE; j++) {
				checkCells2[i][j] = 1;
			}
		}
		if (Checkwinmore == 1) {
			if (count % 2 != 0) {
				temptimage = IMG_LoadTexture(renderer, "D:\\2024-2025\\ky2\\LTNC\\codeproject\\codeproject\\image\\X_win.png");
			}
			else {
				temptimage = IMG_LoadTexture(renderer, "D:\\2024-2025\\ky2\\LTNC\\codeproject\\codeproject\\image\\O_win.png");
			}
			Sound1.playwin();
		}
		else if (count == GRID_SIZEMORE * GRID_SIZEMORE && Checkwinmore == 0) {
			temptimage = IMG_LoadTexture(renderer, "D:\\2024-2025\\ky2\\LTNC\\codeproject\\codeproject\\image\\tie.png");
			Sound1.tiesound();
		}
		SDL_Rect rect;
		rect.x = CELL_SIZE * 1.2;
		rect.y = CELL_SIZE * 1.2 + CELL_SIZE;
		rect.w = CELL_SIZE * 0.6;
		rect.h = CELL_SIZE * 0.6;
		SDL_RenderCopy(renderer, temptimage, NULL, &rect);
	}
}
