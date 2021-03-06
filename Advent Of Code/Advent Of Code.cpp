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
#include <map>

using namespace std;

void day1() {
	ifstream f("day1input.txt");
	string numbers;
	//Don't need a negative, it's either this or the other.
	string positive("+");
	int result = 0;
	int result2 = 0;
	list<int> resultList;

	int iterations = 0;

	if (f.is_open()) {
		while (result2 == 0) {
			++iterations;
			f.clear();
			f.seekg(0);
			while (getline(f, numbers)) {
				size_t found = numbers.find(positive);
				//Positive
				if (found != string::npos) {
					numbers.erase(0, 1);
					int convertedString = stoi(numbers);

					result += convertedString;

					if (result2 == 0) {
						if (find(resultList.begin(), resultList.end(), result) != end(resultList)) {
							result2 = result;
							cout << "Got a result for 2";
						}

						resultList.push_back(result);
					}
				}
				//Negative
				else {
					numbers.erase(0, 1);
					int convertedString = stoi(numbers);

					result -= convertedString;

					if (result2 == 0) {
						if (find(resultList.begin(), resultList.end(), result) != end(resultList)) {
							result2 = result;
							cout << "Got a result for 2";
						}

						resultList.push_back(result);
					}
				}
				//cout << numbers;
			}

			cout << "\nPart 1's answer is: ";
			cout << result;

			cout << "\nPart 2's answer is: ";
			cout << result2;

			cout << "\nThis took " << iterations << " iterations";
		}
	}

	else cout << "File not found";
}

void day2() {
	ifstream f("day2input.txt");
	string line;
	int twoMatch = 0;
	int threeMatch = 0;

	if (f.is_open()) {
		while (getline(f, line)) {
			char chars[26];
			line.copy(chars, 26);
			bool twoMatched = false;
			bool threeMatched = false;
			string matchedChars;
			for (int i = 0; i < 26; ++i) {
				int matches = 0;
				if (twoMatched  && threeMatched)continue;
				if (matchedChars.find(chars[i]) == string::npos) {
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
		cout << "Two Match: " << twoMatch << " Three Match:" << threeMatch << " equals " << twoMatch * threeMatch;
	}
}

void day2part2() {
	ifstream f("day2input.txt");
	string line;
	string allLines[250];
	string answer;

	if (f.is_open()) {
		int i = 0;
		while (getline(f, line)) {
			allLines[i] = line;
			i++;
		}
	}

	for (int i = 0; i < 250; i++) {
		for (int j = 0; j < 250; j++) {
			if (i == j)continue;
			int differentLetters = 0;
			string fullAnswer = "";
			for (int k = 0; k < 26; k++) {
				if (allLines[i][k] != allLines[j][k])differentLetters++;
				else fullAnswer += allLines[i][k];
			}
			if (differentLetters == 1) {
				answer = fullAnswer;
			}
		}
	}

	cout << answer;
}

void day3() {
	ifstream f("day3input.txt");
	vector< vector<int> > fabric(1000, vector<int>(1000));
	vector<string> lines;
	int alreadyClaimed = 0;
	int claimedAll = 0;
	if (f.is_open()) {
		string line;
		while (getline(f, line)) {
			lines.push_back(line);
		}
	}

	//Answer 1 - Pass 1
	for (int lineNumber = 0; lineNumber < 1365; lineNumber++) {
		int claim, posX, posY, width, height;

		//Filling up all of our information from the line
		int claimEnd = lines[lineNumber].find(" ");
		claim = stoi(lines[lineNumber].substr(1, claimEnd - 1));
		int posXEnd = lines[lineNumber].find(",");
		posX = stoi(lines[lineNumber].substr(claimEnd + 3, posXEnd - 1));
		int posYEnd = lines[lineNumber].find(":");
		posY = stoi(lines[lineNumber].substr(posXEnd + 1, posYEnd - 1));
		int widthEnd = lines[lineNumber].find("x");
		width = stoi(lines[lineNumber].substr(posYEnd + 2, widthEnd - 1));
		height = stoi(lines[lineNumber].substr(widthEnd + 1));

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
		claim = stoi(lines[lineNumber].substr(1, claimEnd - 1));
		int posXEnd = lines[lineNumber].find(",");
		posX = stoi(lines[lineNumber].substr(claimEnd + 3, posXEnd - 1));
		int posYEnd = lines[lineNumber].find(":");
		posY = stoi(lines[lineNumber].substr(posXEnd + 1, posYEnd - 1));
		int widthEnd = lines[lineNumber].find("x");
		width = stoi(lines[lineNumber].substr(posYEnd + 2, widthEnd - 1));
		height = stoi(lines[lineNumber].substr(widthEnd + 1));

		//Verifying our claim
		bool intact = true;
		for (int x = posX; x < posX + width; x++) {
			for (int y = posY; y < posY + height; y++) {
				if (fabric[x][y] != claim) intact = false;
			}
		}
		if (intact)claimedAll = claim;
	}

	cout << "Answer 1: " << alreadyClaimed << " / Answer 2: " << claimedAll;
}

void day4() {
	ifstream f("day4input.txt");
	vector<string> lines;
	map<int, vector<int>> sleepTimes;

	//Getting the files data
	if (f.is_open()) {
		string line;
		while (getline(f, line)) {
			lines.push_back(line);
		}
	}

	//Making the info useable
	sort(lines.begin(), lines.end());

	int prevId;
	int prevTime;
	bool sleeping = false;
	int currentLine = 0;
	for (int i = 0; i < lines.size(); i++) {
		cout << lines[i] << "\n";
		int idStart = lines[i].find("#");
		if (idStart != -1) {
			currentLine++;
			string cutString = lines[i].substr(idStart + 1, 5);
			int idEnd = cutString.find(" ");
			string id = cutString.substr(0, idEnd);
			prevId = stoi(id);

			//Just started shift so obviously awake
			sleeping = false;

			//Create new ID map if it doesn't exist
			if (sleepTimes.find(prevId) == sleepTimes.end()) {
				sleepTimes[prevId].resize(60);
			}
		}

		if (lines[i][19] == 'w') {
			int currentTime = stoi(lines[i].substr(15, 2));

			for (int i = prevTime; i < currentTime; i++) {
				sleepTimes[prevId][i]++;
			}
			sleeping = false;
		}
		else if (lines[i][19] == 'f') {
			prevTime = stoi(lines[i].substr(15, 2));
			sleeping = true;
		}
	}

	int laziestGuard = 0;
	int totalTimeSlept = 0;

	//Lets find the guard who slept the most!
	for (map<int, vector<int>>::const_iterator it = sleepTimes.begin(); it != sleepTimes.end(); ++it) {
		int guardSleepTime = 0;
		for (int minute = 0; minute < 60; minute++) {
			guardSleepTime += sleepTimes[it->first][minute];
			if (guardSleepTime > totalTimeSlept) {
				laziestGuard = it->first;
				totalTimeSlept = guardSleepTime;
			}
		}
	}

	int minuteMostAsleepAt = 0;
	int greatestTimeSleepingAtMinute = 0;
	//Now let's narrow it down to the most slept minute
	for (int i = 0; i < 60; i++) {
		if (sleepTimes[laziestGuard][i] > greatestTimeSleepingAtMinute) {
			minuteMostAsleepAt = i;
			greatestTimeSleepingAtMinute = sleepTimes[laziestGuard][i];
		}
	}

	cout << "Answer 1 is " << laziestGuard * minuteMostAsleepAt << "\n";

	int routineSleepyGuard = 0;
	int mostPopularMinute = 0;
	int highestTme = 0;
	for (map<int, vector<int>>::const_iterator it = sleepTimes.begin(); it != sleepTimes.end(); ++it) {
		for (int minute = 0; minute < 60; minute++) {
			if (sleepTimes[it->first][minute] > highestTme) {
				routineSleepyGuard = it->first;
				mostPopularMinute = minute;
				highestTme = sleepTimes[it->first][minute];
			}
		}
	}
	cout << "Answer 2 is " << routineSleepyGuard * mostPopularMinute;
}

bool removeSimilar(string &data) {
	bool removed = false;

	for (string::size_type i = 0; i < data.size(); i++) {
		if (isupper(data[i]) != 0 && (char)tolower(data[i]) == data[i + 1]) {
			data.erase(i, 2);
			removed = true;
			break;
		}
		if (islower(data[i]) != 0 && (char)toupper(data[i]) == data[i + 1]) {
			data.erase(i, 2);
			removed = true;
			break;
		}
	}
	return removed;
}

void day5() {
	ifstream f("day5input.txt");
	string input;

	//Getting the files data
	if (f.is_open()) {
		getline(f, input);
	}

	bool removing = true;
	int iterations = 0;
	while (removing) {
		iterations++;
		removing = removeSimilar(input);
	}
	cout << "Iterations " << iterations << "\nUnits " << input.size();
}

int main()
{
	day5();
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