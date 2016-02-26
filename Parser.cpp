#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include "Parser.h"
using namespace std;

vector<Token> Parser::splitInput(string query, vector<int>& conditions)
{
  
  	iter = query.begin();
  	string parsedText = ""; 

    while( iter != query.end())
  	{

  		bool isDigit = false;
  		bool isCharacter = false;
		parsedText = "";
        tokens.clear();

  		if( *iter == ' ' || *iter == '\n')
		{
			iter++;
			continue;
		}

		else if (isalpha(*iter))
		{
			while(iter != query.end() && (isalpha(*iter) || isdigit(*iter) || *iter == '_'))
			{
				parsedText += *iter;
				iter++;
			}
		}

		else if (isdigit(*iter))
		{
			while(iter != query.end() && isdigit(*iter))
			{
				parsedText += *iter;
				iter++;
			}
			isDigit = true;
		}

		else if (count(symbols1, symbols2+7, skipChars(2)))
		{
			parsedText = skipChars(2);
			iter+=2;
		}

		else if (count(symbols1, symbols1+12, skipChars(1)))
		{
			parsedText = skipChars(1);
			iter++;
		}

		else if (*iter == '"')
		{
			iter++;
			while(iter != query.end() && *iter != '"')
			{
				parsedText += *iter;
				iter++;
			}

			if(*iter != '"')
			{
				cout << "Invalid Symbol (incomplete string)" << endl;
			}
			else
			{
				iter++; 
			}

			isCharacter = true;
		}
		
		else
		{
			cout << "Invalid Symbol (no type matching)" << endl;
		}

		if (parsedText != "")
		{
			Token recognized = recognizeToken(parsedText);
			if(isDigit) recognized = Token(Token::NUMBER, parsedText);
			if(isCharacter) recognized = Token(Token::LITERAL, parsedText);
            
			tokens.push_back(recognized);
            
            if (recognized.getTokenType() == Token::TokenTypes::WHERE) {
                conditions.push_back(tokens.size()+1);
                tokens.push_back(recognizeToken("("));
            }
            if (iter+1 == query.end()) {
                tokens.push_back(recognizeToken(")"));
            }
            

		}
	}
	tokenVector(tokens);
	
	return tokens;
  	}


string Parser::skipChars(int distance)
{
	stringstream stream;
	string::iterator it = iter;
	
	for (int i = 0; i < distance; i++)
	{
		stream << *it;
		
		if(it == query.end())
		{
			return stream.str();
		}

		it++;
	}

	return stream.str();
}

Token Parser::recognizeToken(string input)
{
    string original_input = input;
    input = toUpper(input);
    
  	if (input == "-")
    		return Token(Token::DIFF, input);
  	else if (input == "*" )
    		return Token(Token::PRODUCT, input);
	else if (input == "+" )
	  	return Token(Token::UNION, input);
	else if (input == "{" )
	  	return Token(Token::LEFTBRACE, input);
	else if (input == "}")
	  	return Token(Token::RIGHTBRACE, input);
	else if (input == "(" )
	  	return Token(Token::LEFTPAREN, input);
	else if (input == ")")
	  	return Token(Token::RIGHTPAREN, input);
	else if (input == ",")
	  	return Token(Token::COMMA, input);
	else if (input == "<-" )
	  	return Token(Token::LEFTARROW, input);
	else if (input == ";" )
	  	return Token(Token::SEMICOLON, input);
	else if (input == "=")
	  	return Token(Token::EQUALSIGN, input);
	else if (input == "==" )
	  	return Token(Token::EQ, input);
	else if (input == "!=" )
	  	return Token(Token::NEQ, input);
	else if (input == "<" )
	  	return Token(Token::LT, input);
	else if (input == ">" )
	  	return Token(Token::GT, input);
	else if (input == "<=" )
	  	return Token(Token::LEQ, input);
	else if (input == ">=" )
	  	return Token(Token::GEQ, input);
	else if (input == "||" )
	  	return Token(Token::BOR, input);
	else if (input == "&&" )
	  	return Token(Token::BAND, input);
	else if (input == "SELECT")
	  	return Token(Token::SELECT, input);
	else if (input == "PROJECT")
	  	return Token(Token::PROJECT, input);
	else if (input == "RENAME")
	  	return Token(Token::RENAME, input);
	else if (input == "OPEN")
	  	return Token(Token::OPEN, input);
	else if (input == "CLOSE")
	  	return Token(Token::CLOSE, input);
	else if (input == "WRITE")
	  	return Token(Token::WRITE, input);
	else if (input == "EXIT")
	  	return Token(Token::EXIT, input);
	else if (input == "SHOW")
	  	return Token(Token::SHOW, input);
	else if (input == "CREATE")
	  	return Token(Token::CREATE, input);
	else if (input == "TABLE")
	  	return Token(Token::TABLE, input);
	else if (input == "PRIMARY")
	  	return Token(Token::PRIMARY, input);
	else if (input == "KEY")
	  	return Token(Token::KEY, input);
	else if (input == "UPDATE")
	  	return Token(Token::UPDATE, input);
	else if (input == "SET")
	  	return Token(Token::SET, input);
	else if (input == "WHERE")
	  	return Token(Token::WHERE, input);
	else if (input == "INSERT")
	  	return Token(Token::INSERT, input);
	else if (input == "INTO")
	  	return Token(Token::INTO, input);
	else if (input == "VALUES")
	  	return Token(Token::VALUES, input);
	else if (input == "FROM")
	  	return Token(Token::FROM, input);
	else if (input == "RELATION")
	  	return Token(Token::RELATION, input);
	else if (input == "DELETE")
	  	return Token(Token::DELETE, input);
	else if (input == "VARCHAR")
	  	return Token(Token::VARCHAR, input);
	else if (input == "INTEGER")
	  	return Token(Token::INTEGER, input);
	else
	  	return Token(Token::IDENTIFIER, original_input);
  
}

//creates and returns a vector of token vectors
void Parser::tokenVector(vector<Token> tokens){
    vtokens.push_back(tokens);
}

string Parser::toUpper (string str) {
    for(int i = 0; i < str.size(); i++) {
        str.at(i) = toupper(str.at(i));
    }
    return str;
}
