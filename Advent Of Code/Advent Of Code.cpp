// Advent Of Code.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
#include <string>
#include <vector>

void day1() {
	std::ifstream f("day1input.txt");
	std::string numbers;
	//Don't need a negative, it's either this or the other.
	std::string positive("+");
	int result = 0;
	int result2 = 0;
	std::list<int> resultList;

	int iterations = 0;

	if (f.is_open()) {
		while (result2 == 0) {
			++iterations;
			f.clear();
			f.seekg(0);
			while (std::getline(f, numbers)) {
				std::size_t found = numbers.find(positive);
				//Positive
				if (found != std::string::npos) {
					numbers.erase(0, 1);
					int convertedString = std::stoi(numbers);

					result += convertedString;

					if (result2 == 0) {
						if (std::find(resultList.begin(), resultList.end(), result) != std::end(resultList)) {
							result2 = result;
							std::cout << "Got a result for 2";
						}

						resultList.push_back(result);
					}
				}
				//Negative
				else {
					numbers.erase(0, 1);
					int convertedString = std::stoi(numbers);

					result -= convertedString;

					if (result2 == 0) {
						if (std::find(resultList.begin(), resultList.end(), result) != std::end(resultList)) {
							result2 = result;
							std::cout << "Got a result for 2";
						}

						resultList.push_back(result);
					}
				}
				//std::cout << numbers;
			}

			std::cout << "\nPart 1's answer is: ";
			std::cout << result;

			std::cout << "\nPart 2's answer is: ";
			std::cout << result2;

			std::cout << "\nThis took " << iterations << " iterations";
		}
	}

	else std::cout << "File not found";
}

void day2() {
	std::ifstream f("day2input.txt");
	std::string line;
	int twoMatch = 0;
	int threeMatch = 0;

	if (f.is_open()) {
		while (std::getline(f, line)) {
			char chars[26];
			line.copy(chars, 26);
			bool twoMatched = false;
			bool threeMatched = false;
			std::string matchedChars;
			for (int i = 0; i < 26; ++i) {
				int matches = 0;
				if (twoMatched  && threeMatched)continue;
				if (matchedChars.find(chars[i]) == std::string::npos) {
					for (int j = i; j < 26; ++j) {
						if (chars[i] == chars[j]) {
							matches++;
						}
					}
				}
				matchedChars += chars[i];
				if (matches == 2)twoMatched = true;
				if (matches == 3)threeMatched = true;
			}

			if (twoMatched)twoMatch++;
			if (threeMatched)threeMatch++;
		}
		std::cout << "Two Match: " << twoMatch << " Three Match:" << threeMatch << " equals " << twoMatch * threeMatch;
	}
}

void day2part2() {
	std::ifstream f("day2input.txt");
	std::string line;
	std::string allLines[250];
	std::string answer;

	if (f.is_open()) {
		int i = 0;
		while (std::getline(f, line)) {
			allLines[i] = line;
			i++;
		}
	}

	for (int i = 0; i < 250; i++) {
		for (int j = 0; j < 250; j++) {
			if (i == j)continue;
			int differentLetters = 0;
			std::string fullAnswer = "";
			for (int k = 0; k < 26; k++) {
				if (allLines[i][k] != allLines[j][k])differentLetters++;
				else fullAnswer += allLines[i][k];
			}
			if (differentLetters == 1) {
				answer = fullAnswer;
			}
		}
	}

	std::cout << answer;
}

void day3() {
	std::ifstream f("day3input.txt");
	std::vector< std::vector<int> > fabric(1000, std::vector<int>(1000));
	std::vector<std::string> lines;
	int alreadyClaimed = 0;
	int claimedAll = 0;
	if (f.is_open()) {
		std::string line;
		while (std::getline(f, line)) {
			lines.push_back(line);
		}
	}

	//Answer 1 - Pass 1
	for (int lineNumber = 0; lineNumber < 1365; lineNumber++) {
		int claim, posX, posY, width, height;

		//Filling up all of our information from the line
		int claimEnd = lines[lineNumber].find(" ");
		claim = std::stoi(lines[lineNumber].substr(1, claimEnd - 1));
		int posXEnd = lines[lineNumber].find(",");
		posX = std::stoi(lines[lineNumber].substr(claimEnd + 3, posXEnd - 1));
		int posYEnd = lines[lineNumber].find(":");
		posY = std::stoi(lines[lineNumber].substr(posXEnd + 1, posYEnd - 1));
		int widthEnd = lines[lineNumber].find("x");
		width = std::stoi(lines[lineNumber].substr(posYEnd + 2, widthEnd - 1));
		height = std::stoi(lines[lineNumber].substr(widthEnd + 1));

		//Cutting out in our 2D array
		int amountCouldntClaim = 0;
		for (int x = posX; x < posX + width; x++) {
			for (int y = posY; y < posY + height; y++) {
				if (fabric[x][y] > 0) {
					fabric[x][y] = -1;
					amountCouldntClaim++;
				}
				else if (fabric[x][y] == 0) fabric[x][y] = claim;
			}
		}
		if (amountCouldntClaim == 0)claimedAll = claim;
	}

	//Final tally - Answer 1
	for (int x = 0; x < 1000; x++) {
		for (int y = 0; y < 1000; y++) {
			if (fabric[x][y] == -1)alreadyClaimed++;
		}
	}

	//Answer 2 - Second Pass to verify integrity of claim
	for (int lineNumber = 0; lineNumber < 1365; lineNumber++) {
		int claim, posX, posY, width, height;

		//Filling up all of our information from the line
		int claimEnd = lines[lineNumber].find(" ");
		claim = std::stoi(lines[lineNumber].substr(1, claimEnd - 1));
		int posXEnd = lines[lineNumber].find(",");
		posX = std::stoi(lines[lineNumber].substr(claimEnd + 3, posXEnd - 1));
		int posYEnd = lines[lineNumber].find(":");
		posY = std::stoi(lines[lineNumber].substr(posXEnd + 1, posYEnd - 1));
		int widthEnd = lines[lineNumber].find("x");
		width = std::stoi(lines[lineNumber].substr(posYEnd + 2, widthEnd - 1));
		height = std::stoi(lines[lineNumber].substr(widthEnd + 1));

		//Verifying our claim
		bool intact = true;
		for (int x = posX; x < posX + width; x++) {
			for (int y = posY; y < posY + height; y++) {
				if (fabric[x][y] != claim) intact = false;
			}
		}
		if (intact)claimedAll = claim;
	}

	std::cout << "Answer 1: " << alreadyClaimed << " / Answer 2: " << claimedAll;
}

int main()
{
	day3();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file