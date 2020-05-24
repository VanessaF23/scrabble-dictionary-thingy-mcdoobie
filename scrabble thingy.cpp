#include <iostream>									
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>


using namespace std;

class Word											//word class to be used for the word objects that make up the dictionary vector.
{
private:
	string word;
	string definition;
	string type;
public:
	Word(string, string, string);
	void printDefinition();
	string getWord();
	string getDefinition();
	string getType();
	int calculateScrabbleScore();
	//string writeWord(string);

};
Word::Word(string wordLine, string definitionLine, string typeLine)    //constructor for word class variables
{
	Word::word = wordLine;
	Word::definition = definitionLine;
	Word::type = typeLine;
}

class Dictionary										//dictionary class that contains a vector made up of word objects from the word class.
{
private:
	vector<Word>dictionaryFile;
public:
	void loadDictionary(string);
	void findLongest();
	void logySearch();
	void findWord(string);
	void rhymeSearch(string);
	string formatSearchWord();
	void anagramFinder(string);
	void highestScoringWord(string);
	void writeWord();

};

class Html
{
private:

public:
	void writeToHtml();

};

void Dictionary::writeWord()
{
	cout << "Please wait while the HTML files are created" << endl;
	string letterArray[] = { "A.html","B.html","C.html","D.html","E.html","F.html","G.html","H.html","I.html","J.html","K.html","L.html","M.html","N.html","O.html","P.html","Q.html","R.html","S.html","T.html","U.html","V.html","W.html","X.html","Y.html","Z.html" };
	//string letters[] = { "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z" };
	string letters = "abcdefghijklmnopqrstuvwxyz";
	int j = 0;
	const int K = 0;
	const int M = 1;
	const char HYPHEN = '-';
	string currentWord;
	string fileName;
	for (int i = 0; i < 27; i++)
	{
		cout << "first for loop" << endl;
		fileName = letterArray[j];
		//cout << fileName << endl;
		ofstream myfile;
		myfile.open(fileName);
		for (Word word : dictionaryFile)
		{
			cout << "dictionary for loop" << endl;
			//if (fileOpen == false)
			//{
			if (myfile.is_open())
			{
				cout << "if file open loop" << endl;
				//cout << "file is open for" << fileName << endl;
				currentWord = word.getWord();
				if (currentWord[K] == letters[j] || ((currentWord[K] == HYPHEN) && (currentWord[M] == letters[j])))
				{
					cout << "body of html loop" << endl;
					//cout << currentWord;
					string sectionWord = currentWord;
					string sectionType = word.getType();
					string sectionDefinition = word.getDefinition();
					myfile << "<p>" << sectionWord << "</p>";
					myfile << "<p>" << "(" << sectionType << "). " << sectionDefinition << "</p><br>";
					//myfile << "<html><body><h1><i><hr align=center>testing</i></h1></body></html>";
				}
				
			}
		}
		myfile.close();
		j += 1;
	}
}


void Html::writeToHtml()
{
	Dictionary dictionary;
	string fileName;
	//string sectionDictionary;
	string letterArray[] = { "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z" };
	for (int j = 0; j < size(letterArray); j++)
	{
		fileName = letterArray[j] + ".html";
		ofstream myfile;
		myfile.open(fileName);
		if (myfile.is_open())
		{
			myfile << "<html><body><h1><i><hr align=center>Words beggining with the letter: " << letterArray[j] << "</i></h1></body></html>";
			myfile << "<a href =index.html>Back to the index page</a><br>";
			string letter = letterArray[j];
			myfile.close();
		}
		else
		{
			cout << "Error. unable to open " << fileName << "file" << endl;
		}
	}
	ofstream myfile;
	myfile.open("index.html");
	if (myfile.is_open())
	{
		myfile << "<html><body><h1><i><hr align=center>Welcome to the dictionary index page.</i></h1></body></html>";
		myfile << "<title>Dictionary</title>";
		for (int j = 0; j < size(letterArray); j++)
		{
			fileName = letterArray[j] + ".html";
			myfile << "<a href =" << fileName << ">" << letterArray[j] << " word's page" << "</a>" << "<br>";
		}

		cout << "Success. dictionary2020.txt file has been written to HTML" << endl << endl;
		myfile.close();
	}
	else
	{
		cout << "Error. Unable to open index.html file." << endl;
	}

}


void Dictionary::highestScoringWord(string searchWord)
{
	char letter;
	string matchingWord;
	int currentHighestScore = 0;
	for (Word word : dictionaryFile)
	{
		string searchLetters = searchWord;
		int letterMatches = 0;
		string currentWord = word.getWord();
		string originalWord = currentWord;
		sort(currentWord.begin(), currentWord.end());
		for (int k = 0; k < currentWord.length(); k++)
		{
			letter = currentWord[k];
			size_t found = searchLetters.find(letter);
			if (found != string::npos)
			{
				letterMatches += 1;
				for (int l = 0; l < searchLetters.length(); l++)
				{
					if (searchLetters[l] == letter)
					{
						searchLetters[l] = '%';
						l = searchLetters.length();
					}
				}
			}
			else
			{
				k = currentWord.length();
			}
			if (letterMatches == currentWord.length())
			{
				int currentScore = word.calculateScrabbleScore();
				if (currentScore > currentHighestScore)
				{
					currentHighestScore = currentScore;
					matchingWord = originalWord;
					cout << matchingWord << endl;
				}
			}
		}

	}
	if (currentHighestScore == 0)
	{
		matchingWord = "No words found";
	}
	cout << "the word found with the highest scrabble score is: " << matchingWord << "(" << currentHighestScore << ")" << endl << endl;
	
}

void Dictionary::anagramFinder(string searchWord)
{
	string matchingWords = "";
	string unsortedSearch = searchWord;
	sort(searchWord.begin(), searchWord.end());
	for (Word word : dictionaryFile)
	{
		string currentWord = word.getWord();
		string sortedWord = currentWord;
		if (searchWord.length() == currentWord.length())
		{
			if (unsortedSearch == currentWord)
			{
				continue;
			}
			else
			{
				sort(sortedWord.begin(), sortedWord.end());
				if (searchWord == sortedWord)
				{
					matchingWords += currentWord + "\n";
				}
			}
		}
	}
	if (matchingWords == "")
	{
		matchingWords = "No anagrams found.";
	}
	cout << "The anagrams of the search word are:" << endl << matchingWords << endl << endl;
}

void Dictionary::rhymeSearch(string searchWord)
{
	string searchTerm = searchWord;
	reverse(searchTerm.begin(), searchTerm.end());
	string endLetters;
	string foundWords;
	string comparisonTerm;
	for (int j = 0; j < 3; j++)
	{
		endLetters += searchTerm[j];
	}
	for (Word word : dictionaryFile)
	{
		string currentWord = word.getWord();
		comparisonTerm = currentWord;
		reverse(comparisonTerm.begin(), comparisonTerm.end());
		int k = 0;
		if (comparisonTerm[k] == endLetters[k])
		{
			k++;
			if (comparisonTerm[k] == endLetters[k])
			{
				k++;
				if (comparisonTerm[k] == endLetters[k])
				{
					if (comparisonTerm == searchTerm)
					{
						continue;
					}
					else
						foundWords += currentWord + "\n";
				}
			}
		}
	}
	if (foundWords == "")
	{
		foundWords = "No words found.";
	}
	cout << "The words that rhyme are:" << endl << foundWords << endl << endl;
}

void Dictionary::findWord(string searchTerm)			//dictionary function that takes the users input "searchTerm" and finds it within the dictionary vector. If there is a match, functions: getType, GetDefinition and printDefinition will be called.
{
	bool found = false;
	string searchWord = searchTerm;
	for (Word word : dictionaryFile)
	{
		string currentWord = word.getWord();
		if (currentWord == searchWord)
		{
			string type = word.getType();
			string def = word.getDefinition();
			found = true;
			word.printDefinition();
		}
		else
			continue;
	}
	if (found == false)
	{
		cout << "word not found" << endl << endl;
	}
}

string Dictionary::formatSearchWord()
{
	string requestedWord;
	string formattedWord;
	string lowerWord;
	string c;
	formattedWord.clear();
	lowerWord.clear();
	cout << "please enter a word you would like to search:" << endl;
	getline(cin, requestedWord);
	for (unsigned int j = 0; j < requestedWord.length(); j++)
	{
		if (requestedWord[j] == ' ')
		{
			continue;
		}
		else
			formattedWord += requestedWord[j];
	}
	for (unsigned int i = 0; i < formattedWord.length(); i++)
	{
		c = tolower(formattedWord[i]);
		lowerWord += c;
	}
	return lowerWord;
}

void Word::printDefinition()							// outputs the corresponding type and definition that matches the word searched by the user
{
	int scrabbleScore = calculateScrabbleScore();
	cout << "(" << type << ".) " << definition << endl << "Scrabble score: " << scrabbleScore << endl << endl;
	if (scrabbleScore == 0)
	{
		cout << "Please note: any word containing a hyphen, a word of type 'miscellaneous'" << endl << "or 'proper noun' is not allowed in Scrabble and will return a score of 0" << endl << endl;
	}
}

string Word::getWord()									//returns the word object from the dictionary vector
{
	return word;
}

string Word::getDefinition()							//returns the definition object from the dictionary vector									
{
	
	return definition;
}

string Word::getType()									//returns the type object from the dictionary vector
{
	return type;
}

int Word::calculateScrabbleScore()
{
	int scrabbleScore = 0;
	string currentWord;
	for (int j = 0; j < word.length(); j++)
	{
		if (type == "misc" || type == "pn")
		{
			scrabbleScore = 0;
			j = word.length();
		}
		else if (word[j] == '-')
		{
			scrabbleScore = 0;
			j = word.length();
		}
		else if (word[j] == 'a' || word[j] == 'e' || word[j] == 'i' || word[j] == 'l' || word[j] == 'n' || word[j] == 'o' || word[j] == 'r' || word[j] == 's' || word[j] == 't' || word[j] == 'u')
		{
			scrabbleScore += 1;
		}
		else if (word[j] == 'd' || word[j] == 'g')
		{
			scrabbleScore += 2;
		}
		else if (word[j] == 'b' || word[j] == 'c' || word[j] == 'm' || word[j] == 'p')
		{
			scrabbleScore += 3;
		}
		else if (word[j] == 'f' || word[j] == 'h' || word[j] == 'v' || word[j] == 'w' || word[j] == 'y')
		{
			scrabbleScore += 4;
		}
		else if (word[j] == 'k')
		{
			scrabbleScore += 5;
		}
		else if (word[j] == 'j' || word[j] == 'x')
		{
			scrabbleScore += 8;
		}
		else if (word[j] == 'q' || word[j] == 'z')
		{
			scrabbleScore += 10;
		}
		else
		{
			continue;
		}
	}
	return scrabbleScore;
}

void Dictionary::loadDictionary(string fileName)		//function to load a text file into a vector of type "word". file name is passed in as a parameter. Each line is read in as an object of class "word" before being input to the vector.
{
	ifstream inputFile;																	
	inputFile.open(fileName);
	string line;																		
	string currentWord;
	string currentDefinition;
	string currentType;																		
	if (inputFile.is_open())														
	{
		while (!inputFile.eof())															
		{
			getline(inputFile, line);
			currentWord = line;
			getline(inputFile, line);
			currentDefinition = line;
			getline(inputFile, line);
			currentType = line;
			getline(inputFile, line);
			Word dictionaryWords(currentWord, currentDefinition, currentType);																
			dictionaryFile.push_back(dictionaryWords);
		}
		inputFile.close();
	}
	
	else
	{
		cout << "Error. Unable to open 'dictionary2020.txt file" << endl;
	}
}


void Dictionary::findLongest()								// function to find the longest word in the vector "dictionaryFile". Outputs the longest word along with its type and definition.
{
	vector<int>lengths;																	
	int lengthsMax = 0;
	string longestWord = "";
	for (Word word : dictionaryFile)
	{
		string currentWord = word.getWord();
		if (currentWord.size() > lengthsMax)													
		{
			lengthsMax = currentWord.size();
			longestWord = currentWord;
		}
	}
	for (Word word : dictionaryFile)
	{
		if (longestWord == word.getWord())
		{
			cout << "The longest word in the dictionary is:" << endl;
			cout << longestWord << endl << endl;
			cout << "(" << word.getType() << ".) " << word.getDefinition() << endl << endl;		
			cout << endl;
		}
	}
}

void Dictionary::logySearch()								// function that searches the vector "dictionaryFile" for the word objects ending in "logy". returns all matches. Returns only words, not type and definition
{
	string searchTerm = "logy";															
	reverse(searchTerm.begin(), searchTerm.end());										
	string foundWords;																	
	string comparisonTerm;																
	for (Word word : dictionaryFile)
	{
		string currentWord = word.getWord();
		if (currentWord.size() <= 7)												
		{
			comparisonTerm = currentWord;
			reverse(comparisonTerm.begin(), comparisonTerm.end());				
			size_t found = comparisonTerm.find(searchTerm);								
			if (found != string::npos)													
			{
				foundWords += currentWord + "\n";									
			}
		}
		else
			continue;
	}
	cout << "The words ending in 'logy' are:" << endl << foundWords << endl;		
}

int main()						// main creates a loop to run the program. First calls "loadDictionary" function and then outputs menu options for the user. It calls various functions depending on the users input. 3 menu options for the user plus an option to quit the program
{
	string fileName = "dictionary2020.txt";
	Dictionary dictionary;	
	Html html;
	dictionary.loadDictionary(fileName);					
	string menuChoice = "0";															
	cout << "Welcome! " << endl;
	while (true)
	{
		cout << "Please choose what you would like to do from the menu options below:" << endl << "1. Enter a word, the corresponding definition and word type will be displayed" << endl <<
			"(note: (n.) = Noun, (v.) = Verb, (adj.) = Adjective, (adv.) = Adverb, (prep.) = Preposition, (misc.) = MiscWords," << endl << "(pn.) = Proper Nouns and (n.v.) = Noun and Verb)" << endl;
		cout << "2. Find the longest word in the dictionary" << endl;
		cout << "3. Find words that end in 'logy' and contain seven letters or less in total" << endl;
		cout << "4. Enter a word and search for all words that rhyme" << endl;
		cout << "5. Anagram search: enter a word to search and the anagrams of that word will be returned" << endl;
		cout << "6. Enter some characters to find a word with the highest scrabble score" << endl;
		cout << "7. Write the dictionary file to HTML" << endl;
		cout << endl;
		cout << "Please enter: 1, 2, 3, 4, 5, 6  or 7. If you would like to quit, enter: 99 " << endl;
		getline(cin, menuChoice);											
		if (menuChoice == "1" || menuChoice == "2" || menuChoice == "3" || menuChoice == "4" || menuChoice == "5" || menuChoice == "6" || menuChoice == "7")
		{
			if (menuChoice == "1")					
			{
				string searchWord = dictionary.formatSearchWord();
				dictionary.findWord(searchWord);
			}
			else if (menuChoice == "2")													
			{
				dictionary.findLongest();
			}
			else if (menuChoice == "3")													
			{
				dictionary.logySearch();
			}
			else if (menuChoice == "4")
			{
				string searchWord = dictionary.formatSearchWord();
				dictionary.rhymeSearch(searchWord);
			}
			else if (menuChoice == "5")
			{
				string searchWord = dictionary.formatSearchWord();
				dictionary.anagramFinder(searchWord);
			}
			else if (menuChoice == "6")
			{
				string searchWord = dictionary.formatSearchWord();
				dictionary.highestScoringWord(searchWord);
			}
			else if (menuChoice == "7")
			{
				html.writeToHtml();
				dictionary.writeWord();
			}
		}
		else if (menuChoice == "99")													
		{
			cout << "Goodbye!" << endl;
			break;
		}
		else																			
		{
			cout << "please only enter: 1, 2, 3, 4, 5, 6, 7 or 99 to quit" << endl << endl;
		}
	}
}