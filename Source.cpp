#include <iostream>
#include "FlexLexer.h"
#include <fstream>
#include <array>
#include <string>
#include <functional>
#include <sstream>
#include <map>



using namespace std;

int Input(); 
int Read();   
int Show();   

#define SIZE 4
static const std::array<string, SIZE> msgs = { "1. Input", "2. Read from file", "3. Show statistic", "4. Exit" };
static const std::array<function<bool()>, SIZE> func = { Input, Read, Show };

int getInt(int&);

int main()
{
	int c;
	const char* msg = "";
	do
	{
		system("cls");
		for (int i = 0; i < SIZE; i++)
		{
			cout << msgs[i].c_str() << endl;
		}
		cout << "Your choice:------>";
		do
		{
			cout << msg;
			getInt(c);
			msg = "Error! Repeat, please!";

		} while (c > 4);
		if (c != 4) func[c - 1]();
		msg = "";
	} while (c != 4);

	cout << "\n\n" << endl;
	cout << "--------------That's all! Bye!--------------------------";
	return 0;
}

int Input()
{
	yyFlexLexer lexer;
	cout << "Enter string:" << endl;
	string str;
	getline(cin,str);
	getline(cin,str);
	istringstream i(str + "\n");
	ostringstream o;
	istream& input(i);
	ostream& ouput(o);
	lexer.switch_streams(&input, &ouput);
	if (lexer.yylex())
	{
		cout << "Ok " << o.str() << endl;
		ofstream of = ofstream("statistics.txt", ofstream::app);
		of << o.str() << endl;
		of.close();
	}
	else
	{
		cout << "Wrong!" << endl;
	}
	system("pause");
	return 1;
}


int Read()
{
	cout << "open input.txt" << endl;
	ifstream fi = ifstream(string("input.txt")); 
	if (fi.good()) 
	{
		while (!fi.eof())
		{
			yyFlexLexer lexer;
			string str;
			getline(fi, str);
			istringstream i(str + "\n");
			ostringstream o;
			istream& input(i);
			ostream& ouput(o);
			lexer.switch_streams(&input, &ouput);
			cout << "string: " << str << " -> ";
			if (lexer.yylex())
			{
				cout << "Ok " << o.str() << endl;
				ofstream of = ofstream("statistics.txt", ofstream::app);
				of << o.str() << endl;
				of.close();
			}
			else
			{
				cout << "Wrong!" << endl;
			}
		}
	}
	else
	{
		cout << "file input.txt not found" << endl;
	}
	system("pause");
	fi.close();
	return 1;
}


int Show()
{
	map<string, int> stat;
	ifstream i = ifstream(string("statistics.txt"));
	if (i.good())
	{
		while (!i.eof())
		{
			string str;
			getline(i, str);
			if (str.empty())
				continue;
			if (stat.find(str) != stat.end())
				stat[str]++;
			else
				stat.insert(pair<string, int>(str, 1)); 
		}
		for (const auto& it : stat)
			cout << it.first << " : " << it.second << endl; 
	}
	else
	{
		cout << "file statistics.txt not found" << endl;
	}
	system("pause");
	return 1;
}


int getInt(int& a)
{
	cin >> a;
	if (!cin.good())
		return -1;
	return 1;
}