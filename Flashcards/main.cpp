#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <time.h>
#include <sys/stat.h>
#include <csignal>
#include <algorithm>
#include <filesystem>

bool save = false;

bool dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}

std::vector<std::string> questions, answers;

//Convert a character to an int
int cti(char ch) {
	if (ch == '0') {
		return 0;
	}
	if (ch == '1') {
		return 1;
	}
	if (ch == '2') {
		return 2;
	}
	if (ch == '3') {
		return 3;
	}
	if (ch == '4') {
		return 4;
	}
	if (ch == '5') {
		return 5;
	}
	if (ch == '6') {
		return 6;
	}
	if (ch == '7') {
		return 7;
	}
	if (ch == '8') {
		return 8;
	}
	if (ch == '9') {
		return 9;
	}
	if (tolower(ch) == 'a') {
		return 11;
	}
	if (tolower(ch) == 'b') {
		return 12;
	}
	if (tolower(ch) == 'c') {
		return 13;
	}
	if (tolower(ch) == 'd') {
		return 14;
	}
	if (tolower(ch) == 'e') {
		return 15;
	}
	if (tolower(ch) == 'f') {
		return 16;
	}
	if (tolower(ch) == 'g') {
		return 17;
	}
	if (tolower(ch) == 'h') {
		return 18;
	}
	if (tolower(ch) == 'i') {
		return 19;
	}
	if (tolower(ch) == 'j') {
		return 20;
	}
	if (tolower(ch) == 'k') {
		return 21;
	}
	if (tolower(ch) == 'l') {
		return 22;
	}
	if (tolower(ch) == 'm') {
		return 23;
	}
	if (tolower(ch) == 'n') {
		return 24;
	}
	if (tolower(ch) == 'o') {
		return 25;
	}
	if (tolower(ch) == 'p') {
		return 26;
	}
	if (tolower(ch) == 'q') {
		return 27;
	}
	if (tolower(ch) == 'r') {
		return 28;
	}
	if (tolower(ch) == 's') {
		return 29;
	}
	if (tolower(ch) == 't') {
		return 30;
	}
	if (tolower(ch) == 'u') {
		return 31;
	}
	if (tolower(ch) == 'v') {
		return 32;
	}
	if (tolower(ch) == 'w') {
		return 33;
	}
	if (tolower(ch) == 'x') {
		return 34;
	}
	if (tolower(ch) == 'y') {
		return 35;
	}
	if (tolower(ch) == 'z') {
		return 36;
	}
	return 9999;
}

//Handle an input of ctrl+c
void none(int signum) {
	if (signum == 2) {
		if (save) {
			std::fstream autos;
			autos.open("sets/save.txt", std::fstream::app);
			if (questions.size() > answers.size()) {
				for (size_t x = 0; x < answers.size(); x++) {
					autos.write(questions[x].c_str(), questions[x].size());
					autos.write("|", 1);
					autos.write(answers[x].c_str(), answers[x].size());
					autos.write("\n", 1);
				}
			}
			else {
				for (size_t x = 0; x < questions.size(); x++) {
					autos.write(questions[x].c_str(), questions[x].size());
					autos.write("|", 1);
					autos.write(answers[x].c_str(), answers[x].size());
					autos.write("\n", 1);
				}
			}
			autos.flush();
			std::cout << "\nCtrl+c was pressed, so now you must hit it again to close the program (don't worry, you'll have a chance to save your stuff)";
		}
		else {
			std::cout << "\nCtrl+c was pressed, so now you must hit it again to close the program";
		}
	}
}

//Test if a given file exists
bool fileExists(const std::string& filename)
{
	struct stat buf;
	return stat(filename.c_str(), &buf) != -1;
}

//Generate a random number (with exclusions) and retrn the result
int randNum(int min, int max, std::vector<int> exclusions) {
	int result = (rand() % (max + 1) - min) + min;
	bool pseudo = true;
	bool found = false;
	while (pseudo) {
		found = false;
		for (unsigned int x = 0; x < exclusions.size(); x++) {
			if (result == exclusions[x]) {
				result = (rand() % (max + 1) - min) + min;
				found = true;
				break;
			}
		}
		if (!found) {
			pseudo = false;
		}
	}

	return result;
}

//Clear the console
void clearScreen(char fill = ' ') {
	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}

int main() {
	signal(SIGINT, none);
	srand(static_cast<unsigned int>(time(NULL)));
	std::string input = "", path = "sets/";
	std::fstream savedFiles("saved.txt");
	std::vector<std::string> list;
	char cur;
	std::string comp;

	/*std::vector<std::string> orgList;
	std::vector<int> poses;
	int curren;*/

	/*for (size_t x = 0; x < list.size(); x++) {
		curren = list.size();
		for (size_t y = 0; y < list.size(); y++) {
			if (x != y) {
				if (list[x].size() > list[y].size()) {
					for (unsigned int z = 0; z < list[x].size(); z++) {
						if (z < list[y].size()) {
							if (cti(list[x].at(z)) > cti(list[y].at(z))) {
								if (cti(list[x].at(z)) != 9999 && cti(list[y].at(z)) != 9999) {
									curren++;
									break;
								}
							}
							else {
								if (cti(list[x].at(z)) < cti(list[y].at(z))) {
									if (cti(list[x].at(z)) != 9999 && cti(list[y].at(z)) != 9999) {
										//if (curren > 0) {
											curren--;
										//}
										break;
									}
								}
							}
						}
						else {
							break;
						}
					}
				}
				else {
					for (unsigned int z = 0; z < list[y].size(); z++) {
						if (z < list[x].size()) {
							if (cti(list[x].at(z)) > cti(list[y].at(z))) {
								if (cti(list[x].at(z)) != 9999 && cti(list[y].at(z)) != 9999) {
									curren++;
									break;
								}
							}
							else {
								if (cti(list[x].at(z)) < cti(list[y].at(z))) {
									if (cti(list[x].at(z)) != 9999 && cti(list[y].at(z)) != 9999) {
										//if (curren > 0) {
											curren--;
										//}
										break;
									}
								}
							}
						}
						else {
							break;
						}
					}
				}
			}
		}
		poses.emplace_back(curren);
	}

	orgList = std::vector<std::string>(list.size());
	for (size_t x = 0; x < poses.size(); x++) {
		orgList[x] = list[poses[x]];
	}*/

	/*std::sort(list.begin(), list.end(), [&](const std::string &t1, const std::string &t2) {
		if (t1.size() > t2.size()) {
			for (size_t x = 0; x < t2.size(); x++) {
				if (cti(t1[x]) != cti(t2[x]) && cti(t1[x]) != 9999 && cti(t2[x]) != 9999) {
					return cti(t1[x]) > cti(t2[x]);
				}
			}
		}
		else {
			for (size_t x = 0; x < t1.size(); x++) {
				if (cti(t1[x]) != cti(t2[x]) && cti(t1[x]) != 9999 && cti(t2[x]) != 9999) {
					return cti(t1[x]) > cti(t2[x]);
				}
			}
		}
	});*/

	if (fileExists("sets/save.txt")) {
		std::cout << "The last file you were writing was automatically saved. Would you like to recover it? (Keep in mind to fully recover it, you must select \"y,\" select the file you were previously writing in, and then save your changes there) (y/n): ";
		input = std::string();
		while (input == "") {
			std::getline(std::cin, input);
		}
		if (tolower(input.at(0)) == 'y') {
			save = true;
			std::fstream autos("sets/save.txt");
			char charR = ' ';
			autos.get(charR);
			std::string compiledAns;
			while (!autos.eof()) {
				if (charR == '\n') {
					answers.emplace_back(compiledAns);
					compiledAns = std::string();
				}
				else {
					if (charR == '|') {
						questions.emplace_back(compiledAns);
						compiledAns = std::string();
					}
					else {
						compiledAns += charR;
					}
				}
				autos.get(charR);
			}
		}
		else {
			std::cout << "\nWould you like to delete the autosave? (y/n): ";
			input = std::string();
			while (input == "") {
				std::getline(std::cin, input);
			}
			if (tolower(input.at(0) == 'y')) {
				std::remove("sets/save.txt");
			}
		}
	}
	while (true) {
		savedFiles.get(cur);
		while (!savedFiles.eof()) {
			if (cur != '\n') {
				comp += cur;
			}
			else {
				list.emplace_back(comp);
				comp = std::string();
			}
			savedFiles.get(cur);
		}

		std::sort(list.begin(), list.end(), [](std::string first, std::string second) {
			return first.compare(second) < 0;
		});

		std::string oldIn;
		bool stop;
		while (true) {
			stop = false;
			std::cout << "Input the name of the file you want to read (like spanish1.txt) or type \"/l\" without the quotes to list all currently existing files (you can type a directory or key letters to look in as well like /l 10th, /l 10th/spanish, or /l ab (this will get you any files/folders whose first directories begin with ab)) or you can use /lc <text> to list all files with any part that matches <text> (like /lc foo would get you foo.txt, hi/foo/this.txt, and this/foo.txt, for example) (if making new directories/entering existing ones, use / NOT \\): ";
			input = std::string();
			while (input == "") {
				std::getline(std::cin, input);
			}
			if (input.substr(0, 2) == "/l") {
				std::cout << "\n";
				if (input.size() == 2) {
					for (size_t x = 0; x < list.size(); x++) {
						std::cout << list[x] << "\n";
					}
				}
				else {
					if (input[2] == 'c') {
						if (input.size() == 3) {
							for (size_t x = 0; x < list.size(); x++) {
								std::cout << list[x] << "\n";
							}
						}
						else {
							for (size_t x = 0; x < list.size(); x++) {
								if (list[x].find(input.substr(4, input.size())) != std::string::npos) {
									std::cout << list[x] << "\n";
								}
							}
						}
					}
					else {
						for (size_t x = 0; x < list.size(); x++) {
							if (list[x].substr(0, input.size() - 3) == input.substr(3, input.size() - 3)) {
								std::cout << list[x] << "\n";
							}
						}
					}
				}
				std::cout << "\n";
			}
			else {

				oldIn = input;
				if (input.find("/") != std::string::npos) {
					std::string fullPath;
					std::string ynIn;
					size_t prevSize = 0;
					for (unsigned int x = 0; x < input.size(); x++) {
						if (input[x] != '/') {
							fullPath += input[x];
						}
						else {
							fullPath += input[x];
							if (!dirExists(path + fullPath)) {
								ynIn = std::string();
								std::string newFolder = fullPath.substr(prevSize, (fullPath.size() - 1) - prevSize);
								while (newFolder.find("/") != std::string::npos) {
									newFolder = newFolder.substr(newFolder.find("/") + 1, (newFolder.size() - 1) - newFolder.find("/"));
								}
								std::cout << "The folder " << newFolder << " does not exist. Do you want to create it? (y/n): ";
								
								while (ynIn == "") {
									std::getline(std::cin, ynIn);
								}
								
								std::string comp = path;
								comp.append(fullPath);
								LPCSTR d = comp.c_str();

								if (ynIn[0] == 'y') {
									if (!CreateDirectory(d, NULL)) {
										std::cout << "Failed to create directory (" << GetLastError() << ")\n";
										//Restart
										stop = true;
										break;
									}
									//Otherwise, update size
									prevSize = fullPath.size();
								}
								else {
									//Restart, because otherwise, big problems occur
									stop = true;
									std::cout << "\n";
									break;
								}
							}
						}
					}
				}

				if (!fileExists((path + input)) && !stop) {
					std::cout << "\nThis file does not yet exist. Would you like to create it? (y/n): ";
					input = std::string();
					while (input == "") {
						std::getline(std::cin, input);
					}

					if (tolower(input.at(0)) == 'y') {
						break;
					}
					else {
						std::cout << "\n";
					}
				}
				else {
					if (!stop) {
						break;
					}
				}
			}
		}

		path.append(oldIn);

		std::fstream file;
		file.open(path, std::fstream::app);
		if (file.is_open()) {
			if (tolower(input.at(0)) == 'y') {
				savedFiles.close();
				savedFiles.open("saved.txt", std::fstream::app);
				savedFiles.write(oldIn.c_str(), oldIn.size());
				savedFiles.write("\n", 1);
				savedFiles.flush();
			}
			savedFiles.close();

			std::cout << "\nWould you like to add to this file? (y/n): ";
			input = std::string();
			while (input == "") {
				std::getline(std::cin, input);
			}

			if (tolower(input.at(0)) == 'y') {
				HWND hwnd = GetConsoleWindow();
				HMENU hmenu = GetSystemMenu(hwnd, FALSE);
				EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);
				while (true) {
					input = std::string();
					std::cout << "\nInput the question you want (or $ to save your changes and stop, or /z to undo the last answer input) (type /ncs at the end of your question to make it not disappear when the answer is shown): ";
					while (input == "") {
						std::getline(std::cin, input);
					}
					if (input.at(0) != '$') {
						if (input != "/z") {
							save = true;
							questions.emplace_back(input);
							while (true) {
								input = std::string();
								std::cout << "\nNow input the answer (or /z to undo the question input) (type /ncs at the end of your answer to make it not disappear when the question is shown [reverse mode]): ";
								while (input == "") {
									std::getline(std::cin, input);
								}

								if (input == "/z") {
									if (questions.size() != 0) {
										std::cout << "\nUndone: " << questions[questions.size() - 1] << "\n";
										questions.pop_back();
										questions.shrink_to_fit();
										break;
									}
									else {
										std::cout << "\nAll questions have already been undone\n";
									}
								}
								else {
									answers.emplace_back(input);
									break;
								}
							}
						}
						else {
							if (answers.size() != 0) {
								std::cout << "\nUndone: " << answers[answers.size() - 1] << "\n";
								answers.pop_back();
								answers.shrink_to_fit();

								while (true) {
									input = std::string();
									std::cout << "\nNow input the answer (or /z to undo the question input): ";
									while (input == "") {
										std::getline(std::cin, input);
									}

									if (input == "/z") {
										std::cout << "\nUndone: " << questions[questions.size() - 1] << "\n";
										questions.pop_back();
										questions.shrink_to_fit();
										break;
									}
									else {
										answers.emplace_back(input);
										break;
									}
								}
							}
							else {
								std::cout << "\nThere is no last answer, so you cannot undo\n";
							}
						}
					}
					else {
						std::cout << "\nWriting, do not exit...";
						for (size_t x = 0; x < questions.size(); x++) {
							file.write(questions[x].c_str(), questions[x].size());
							file.write("|", 1);
							file.write(answers[x].c_str(), answers[x].size());
							file.write("\n", 1);
						}
						file.flush();
						std::cout << "\nFinished writing";
						break;
					}
				}
				save = false;
				EnableMenuItem(hmenu, SC_CLOSE, MF_ENABLED);
			}

			std::cout << "\nWould you like to show the cards in reverse order? (answer and then question) (y/n): ";
			input = std::string();
			while (input == "") {
				std::getline(std::cin, input);
			}
			bool reverse = (tolower(input.at(0)) == 'y' ? true : false);

			std::cout << "\nPress enter to begin the flashcards and continue throughout";

			while (!_kbhit()) {}
			_getche();

			clearScreen();

			std::string compiledAns;
			char charR;
			file.close();
			file.open(path);
			file.get(charR);
			std::vector<int> order;
			questions.clear();
			questions.shrink_to_fit();
			answers.clear();
			answers.shrink_to_fit();
			while (!file.eof()) {
				if (charR == '\n') {
					answers.emplace_back(compiledAns);
					compiledAns = std::string();
				}
				else {
					if (charR == '|') {
						questions.emplace_back(compiledAns);
						compiledAns = std::string();
					}
					else {
						compiledAns += charR;
					}
				}
				file.get(charR);
			}
			file.close();

			std::vector<int> res;
			std::vector<std::string> compiledQuestions = std::vector<std::string>(questions.size()), compiledAnswers = std::vector<std::string>(questions.size());
			for (unsigned int x = 0; x < questions.size(); x++) {
				res.emplace_back(randNum(0, questions.size() - 1, res));
				compiledQuestions[res[x]] = questions[x];
				compiledAnswers[res[x]] = answers[x];
			}

			bool dontCS = false;
			std::cout << "\n(Press any key to flip the card and continue once the card has been flipped, or hit backspace to go back to a previous question or answer)";
			clearScreen();
			while (true) {
				for (size_t x = 0; x < compiledQuestions.size(); x++) {
					if (reverse) {
						if (compiledAnswers[x].size() >= 4) {
							if (compiledAnswers[x].substr(compiledAnswers[x].size() - 4, 4) == "/ncs") {
								dontCS = true;
								std::cout << "(" << x + 1 << "/" << compiledAnswers.size() << "): " << compiledAnswers[x].substr(0, compiledAnswers[x].size() - 4);
							}
							else {
								std::cout << "(" << x + 1 << "/" << compiledAnswers.size() << "): " << compiledAnswers[x];
							}
						}
						else {
							std::cout << "(" << x + 1 << "/" << compiledAnswers.size() << "): " << compiledAnswers[x];
						}
					}
					else {
						if (compiledQuestions[x].size() >= 4) {
							if (compiledQuestions[x].substr(compiledQuestions[x].size() - 4, 4) == "/ncs") {
								dontCS = true;
								std::cout << "(" << x + 1 << "/" << compiledQuestions.size() << "): " << compiledQuestions[x].substr(0, compiledQuestions[x].size() - 4);
							}
							else {
								std::cout << "(" << x + 1 << "/" << compiledQuestions.size() << "): " << compiledQuestions[x];
							}
						}
						else {
							std::cout << "(" << x + 1 << "/" << compiledQuestions.size() << "): " << compiledQuestions[x];
						}
					}

					while (!_kbhit()) {}
					if (_getch() == 8) {
						dontCS = false;
						clearScreen();
						if (x != 0) {
							x -= 2;
						}
						else {
							x--;
						}
					}
					else {
						if (dontCS) {
							std::cout << "\n\n";
							dontCS = false;
						}
						else {
							clearScreen();
						}

						if (reverse) {
							if (compiledQuestions[x].size() >= 4) {
								if (compiledQuestions[x].substr(compiledQuestions[x].size() - 4, 4) == "/ncs") {
									std::cout << "(" << x + 1 << "/" << compiledQuestions.size() << "): " << compiledQuestions[x].substr(0, compiledQuestions[x].size() - 4);
								}
								else {
									std::cout << "(" << x + 1 << "/" << compiledQuestions.size() << "): " << compiledQuestions[x];
								}
							}
							else {
								std::cout << "(" << x + 1 << "/" << compiledQuestions.size() << "): " << compiledQuestions[x];
							}
						}
						else {
							if (compiledAnswers[x].size() >= 4) {
								if (compiledAnswers[x].substr(compiledAnswers[x].size() - 4, 4) == "/ncs") {
									std::cout << "(" << x + 1 << "/" << compiledAnswers.size() << "): " << compiledAnswers[x].substr(0, compiledAnswers[x].size() - 4);
								}
								else {
									std::cout << "(" << x + 1 << "/" << compiledAnswers.size() << "): " << compiledAnswers[x];
								}
							}
							else {
								std::cout << "(" << x + 1 << "/" << compiledAnswers.size() << "): " << compiledAnswers[x];
							}
						}
						while (!_kbhit()) {}
						if (_getch() == 8) {
							x--;
						}
						clearScreen();
					}
				}
				res.clear();
				res.shrink_to_fit();
				for (unsigned int x = 0; x < questions.size(); x++) {
					res.emplace_back(randNum(0, questions.size() - 1, res));
					compiledQuestions[res[x]] = questions[x];
					compiledAnswers[res[x]] = answers[x];
				}

				std::cout << "Switch the card order? (y/n) (or type /b to go back to the main menu): ";
				input = std::string();
				while (input == "") {
					std::getline(std::cin, input);
				}

				if (input == "/b") {
					questions.clear();
					answers.clear();
					compiledQuestions.clear();
					compiledAnswers.clear();
					clearScreen();
					path = "sets/";
					savedFiles.flush();
					savedFiles.close();
					savedFiles.open("saved.txt");
					list.clear();
					break;
				}

				if (tolower(input.at(0)) == 'y') {
					reverse = !reverse;
				}
				clearScreen();
			}
		}
		else {
			std::cout << "\nCould not find file named " << input << " make sure it is in the \"sets\" folder. Press any key to continue";
			while (!_kbhit()) {}
		}
	}
}