#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<ctime>
#include<Windows.h>
#include<algorithm>
#include<sapi.h>

using namespace std;

// Converts string to wide string.
wstring StringToWString(const string& s)
{
	wstring temp(s.length(), L' ');
	copy(s.begin(), s.end(), temp.begin());
	return temp;
}

// Speaks the contents of the string.
void Speak(ISpVoice *pVoice, const wstring& linew)
{
	if (pVoice == NULL)
		return;
	pVoice->Speak(linew.c_str(), 0, NULL);
}

int main()
{
	int n, i;
	srand((unsigned int)time(NULL));
	vector<string> questions;
	vector<int> answers;

	// Read the questions and corresponding answers from the file.
	bool isQuestion = true;
	string line;
	ifstream myfile("questions.txt");
	i = 0;
	if (myfile.is_open())
	{
		string str;
		while (getline(myfile, line))
		{
			if (isQuestion)
			{
				str += line + "\n\t";
				if (i == 4)
				{
					questions.push_back(str);
					isQuestion = false;
					i = 0;
					str = "";
				}
				else
					i++;
			}
			else
			{
				answers.push_back((int)(line[0] - '0'));
				isQuestion = true;
			}
		}
		myfile.close();
	}
	else
	{
		wcout << L"Could not open \"file.txt\"\n";
		return 0;
	}

	// Create the voice.
	ISpVoice *pVoice = NULL;
	if (FAILED(CoInitialize(NULL)))
		return EXIT_FAILURE;
	// We ignore the check for pVoice being NULL below because if TTS functionality doesn't work, we still want to continue displaying the questions.
	CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);

	// Get the number of questions for quiz.
	wstring linew;
	linew = L"Welcome to the quiz. Please enter the number of questions for a quiz (1 to " + to_wstring(questions.size()) + L"): ";
	wcout << L"\t" << linew;
	Speak(pVoice, linew);
	while (true)
	{
		cin >> n;
		if (n > (int)questions.size())
		{
			linew = L"Sorry, there can be maximum " + to_wstring(questions.size()) + L" questions per quiz. Please enter the number again: ";
			wcout << L"\t" << linew;
			Speak(pVoice, linew);
		}
		else
			break;
	}

	// Randomly select n questions.
	vector<int> quizQuestions(n);
	vector<bool> selectedQuestions(questions.size(), false);
	int random, ans, score = 0;
	for (int j = 0; j < n; j++)
	{
		do
		{
			random = rand() % (questions.size());
			if (selectedQuestions[random] == false)
				quizQuestions[j] = random;
		} while (selectedQuestions[random] == true);
		selectedQuestions[random] = true;
	}

	// Start the quiz.
	for (int index = 0; index < n; index++)
	{
		system("cls");
		wcout << L"\n\n\tQuiz\t\t\t\t\tScore: " << score << L"\n\n";
		if (index == 0)
			linew = L"First Question";
		else
			linew = L"Next Question";
		Speak(pVoice, linew);
		linew = StringToWString(questions[quizQuestions[index]]);
		wcout << L"\t" << linew << L"\n";
		Speak(pVoice, linew);
		linew = L"Enter answer: 1, 2, 3 or 4";
		wcout << L"\t" << linew << L"\n\t";
		Speak(pVoice, linew);
		cin >> ans;
		if (ans == answers[quizQuestions[index]])
		{
			linew = L"Right Answer";
			wcout << L"\t" << linew << L"\n";
			Speak(pVoice, linew);
			score += 10;
		}
		else
		{
			linew = L"Wrong Answer";
			wcout << L"\t" << linew << L"\n";
			Speak(pVoice, linew);
			linew = L"The correct answer is " + to_wstring(answers[quizQuestions[index]]);
			wcout << L"\t" << linew << L".\n";
			Speak(pVoice, linew);
		}
		Sleep(1000);
	}

	// Display the final score.
	system("cls");
	linew = L"Test Completed";
	Speak(pVoice, linew);
	wcout << L"\n\n\tYour final score is " << score << L"/" << n * 10 << L"!!!\n";
	linew = L"Your final score is " + to_wstring(score) + L" out of " + to_wstring(n * 10);
	Speak(pVoice, linew);

	// Release the memory.
	if (pVoice != NULL)
	{
		pVoice->Release();
		pVoice = NULL;
	}
	return 0;
}