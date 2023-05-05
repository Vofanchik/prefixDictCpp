#include "TrieDictionary.h"
#include <string>
#include <fstream>



int main()
{
	TrieNode* trieWord = new TrieNode();

	std::string data;
	std::fstream dictionary;

	dictionary.open("dictionary.txt", std::fstream::in); 
	if (dictionary.is_open())
	{
		while (dictionary)
		{
			
			dictionary >> data;
			insert(trieWord, data);
		}
	}
	else
	{
		std::cout << "error:  file not open." << std::endl;
		return -1;
	}
	dictionary.close();



	std::string inputWord;    
	std::string fullText;     
	std::string currentWord;     
	std::vector<std::string> predict;




	while (true)
	{
		getline(std::cin, inputWord);
		for (int i = 0; i < inputWord.length(); ++i)
		{

			fullText += inputWord[i];
			currentWord += inputWord[i];

			if (inputWord[i] == ' ')  
			{
				currentWord.clear();    
			}

		}
		substitution(trieWord, predict, currentWord);


		if (predict[0].length() == 0) //???????
		{
			currentWord.clear();
			std::cout << fullText;
			continue;
		}

		for (int i = 0; i < predict.size(); i++)
		{
			if (i > 8)
			{
				break;
			}
			std::cout << i << ' ' << predict[i]<< ' ';

		}
		int choice = 1;

		while (choice!=9)
		{
			std::cout << "\nSelect suggest number, or input 9 to continue\n";
			std::cin >> choice;
			std::cin.ignore(32767, '\n');
			if (choice >= 0 && choice < predict.size())				
			{
				for (size_t i = 0; i < currentWord.length(); i++)
				{
					fullText.pop_back();
				}
				fullText+=predict[choice];
				break;
			}

		}
		std::cout << fullText;

	}
	
}

