#include <vector>
#include <string>
#include "Executer.h"
using namespace std;

void Executer::execute(Engine* eng, vector<Token> tokenVec){
	tokens = tokenVec;
	currentIndex = 0;
	engine = eng;
	setToken();
	program();
}
void Executer::program(){
	if(token.getTokenType() == Token::IDENTIFIER)
		query();
	else
		command();
}
void Executer::command(){
	Relation* relation;
	switch(token.getTokenType())
    	{
        	case Token::EXIT:
        		engine->exit_();
        		break;
        	case Token::WRITE:
        	   	expect(Token::IDENTIFIER);
        	    	engine->write(token.getValue());
        	    	break;
        	case Token::OPEN:
        	    	expect(Token::IDENTIFIER);
        	    	engine->open(token.getValue());
        	    	break;
        	case Token::SHOW:
        		nextToken();
        	    	relation = atomicExpr();
        	    	engine->show(relation->getName());
        	    	break;
        	case Token::CLOSE:
        	    	nextToken();
        	    	engine->close(token.getValue());
        	    	break;
        	case Token::DELETE:
        	    	delete_();
        	    	break;
        	/*case Token::UPDATE:
        	    	update();
        	    	break;*/
        	case Token::CREATE:
        	    	create();
        	    	break;
        	case Token::INSERT:
        	    	insert();
        	    	break;
	}
}

void Executer::insert(){
	expect(Token::INTO);
	expect(Token::IDENTIFIER);

	string relationName = token.getValue();

	expect(Token::VALUES);
	expect(Token::FROM);

	nextToken();

	// Token can be either a ( or RELATION
	if(token.getTokenType() == Token::RELATION)
	{
		nextToken();

		// Inserting from expression
		Relation* relation = expr();

		vector<Tuple*> tuples = relation ->getTuples();

		for(int i=0; i<tuples.size(); i++)
		{
			engine->insertTuple(relationName, tuples[i]);
		}
	}
	else if(token.getTokenType() == Token::LEFTPAREN)
	{
		vector<string> tupleContents;
		//Tuple* tuple;

		do
		{
			nextToken();
			tupleContents.push_back(token.getValue());
			nextToken();
		}
		while(token.getTokenType() == Token::COMMA);
//
		//Segmentation Fault here
		cout << "SegStart" << endl;
		for(int i = 0; i< tupleContents.size(); i++)
		{
			cout << tupleContents[i] << endl;
		}
		Tuple* tuple = new Tuple(tupleContents);
//
		cout << "SegEnding" << endl;
		if(token.getTokenType() != Token::RIGHTPAREN) 
			cout << "Expected RIGHTPAREN" << endl;;

		engine->insertTuple(relationName, tuple);
	}

}

void Executer::create(){

	expect(Token::TABLE);
	expect(Token::IDENTIFIER);
	string relationName = token.getValue();

	// Read in the attributes and types
	expect(Token::LEFTPAREN);
	cout << "first expect" << endl;

	nextToken();
	vector<Attribute*> attributes;

	while(token.getTokenType() != Token::RIGHTPAREN)
	{
		string name = token.getValue();

		nextToken();
		if( (token.getTokenType() != Token::VARCHAR) && (token.getTokenType() != Token::INTEGER)) 
			cout << "Expected INTEGER or VARCHAR";

        Attribute::Type type;
		switch (token.getTokenType()){
			case Token::VARCHAR:
			{
				type = Attribute::VARCHAR;
			}
				break;
			case Token:: INTEGER:
			{
				type = Attribute::INTEGER;
			}
				break;
			case Token:: ENUM:
			{
				type = Attribute::ENUM;
			}
				break;
		}		

		Attribute* attribute;
		if(type == Attribute::VARCHAR)
		{/*
			int size;
			expect(Token::LEFTPAREN);
			//cout << "I think it fails here" << endl;
			expect(Token::NUMBER);
			//cout << "or here" << endl;
			size = token.getNumValue();
			expect(Token::RIGHTPAREN);
*/
			attribute = new Attribute(type, name);

		}
		else
		{
			attribute = new Attribute(type, name);
			//cout << name << "has been created" << endl;
		}

		attributes.push_back(attribute);
		cout << "attribute " << name << "has been created" << endl;

		if( ! lookAhead(Token::RIGHTPAREN))
		{
			expect(Token::COMMA);
		}
		nextToken();
	}

	expect(Token::PRIMARY);
	expect(Token::KEY);

	vector<Attribute*> keys = getAttributeList();
	engine-> createRelation(relationName, attributes);

}

void Executer::delete_(){
	expect(Token::FROM);
	expect(Token::IDENTIFIER);
	string relationName = token.getValue();
	expect(Token::WHERE);
	int recurIndex = currentIndex+1;
	cout << "the where starts at " << recurIndex << endl;
}

void Executer::query(){
	cout << "query branch taken" << endl;
	string relationName = token.getValue();
	cout << "We want a relation named " << relationName << endl;
	expect(Token::LEFTARROW);
	nextToken();
	Relation* relPtr;
	relPtr = expr();
	tempRelation = relPtr;
	cerr << "The program doesn't crash" << endl;
	//engine->renameRelation(relPtr, relationName);
	//engine->createRelation(relPtr);

}

void Executer::setToken(){
	token = tokens[currentIndex];
}
void Executer::nextToken(){
	bool endCheck = atEnd();
	if(endCheck == true)
		cerr << "sorry we are at the end of the vector of tokens @index" << currentIndex << endl;
	currentIndex ++;
	token = tokens[currentIndex];
}
bool Executer::atEnd(){
	return (currentIndex == tokens.size()-1);
}
Relation* Executer::expr(){
	switch(token.getTokenType()){
		case Token::IDENTIFIER:
			return atomicExpr();
			break;
		case Token::RENAME:
			return rename();
			break;
		case Token::LEFTPAREN:
			return atomicExpr();
			break;
		case Token::SELECT:
			break;
		case Token::PROJECT:
			return project();
			break;
		case Token::JOIN:
			//return naturalJoin();
			break;
	}
}
Relation* Executer::atomicExpr(){
    Relation* relation;
    int relIndex;
    if(token.getTokenType() == Token::IDENTIFIER){
    	relIndex = engine->findRelation(token.getValue());
    	relation = engine->getRelation(relIndex);
    }
    if(token.getTokenType() == Token::LEFTPAREN){
        nextToken();
        relation = expr();
        expect(Token::RIGHTPAREN);
        return relation;
    }
    
    if(lookAhead(Token::UNION) || lookAhead(Token::PRODUCT) || lookAhead(Token::DIFF) || lookAhead(Token::JOIN)){
        relation = combine(relation);
        //string rname = relation->getName();
        //cout << "Diff made a relation named " << rname << endl;
        engine->show(relation);
    }
    return relation;
}
vector<Attribute*> Executer::getAttributeList(){
	expect(Token::LEFTPAREN);
	nextToken();
	vector<Attribute*> attList;
	while(token.getTokenType() == Token::IDENTIFIER){
        attList.push_back(new Attribute(Attribute::VARCHAR, token.getValue()));
		nextToken();
		if((token.getTokenType() != Token::COMMA)&&(token.getTokenType() != Token::RIGHTPAREN))
			cerr << "Attribute list in wrong format" << endl;
		if(token.getTokenType() == Token::COMMA)
			nextToken();
	}
	//now we should be left with right paren
	//if(lookAhead)
	nextToken();
	return attList;
}
Relation* Executer::combine(Relation* relation){
	Relation* relation1 = relation;
	nextToken();
	Token op = token;
	nextToken();
	Relation* relation2 = atomicExpr();
	string name1, name2;
	name1 = relation1->getName();
	name2 = relation2->getName();
	switch(op.getTokenType()){
		case Token::PRODUCT:
			return engine->crossProduct(name1, name2);
			break;
		case Token::UNION:
			return engine->union_(relation1->getName(), relation2->getName());
			break;
		case Token::DIFF:
			return engine->difference(relation1->getName(), relation2->getName());
			break;
		case Token::JOIN:
			return engine->naturalJoin(name1, name2);
			break;
	}

}

void Executer::expect(Token::TokenTypes type){
	string typestr[47] = {"FROM", "SEMICOLON", "LEFTPAREN", "RIGHTPAREN", "COMMA", "EQUALSIGN",
			"LEFTBRACE", "RIGHTBRACE", "LEFTARROW", "TABLE", "PRIMARY", "KEY", "SET", "NUMBER",
			"INTO", "UPDATE", "INSERT", "VALUES", "RELATION", "DELETE", "WHERE", "VARCHAR", "INTEGER", "ENUM",
            "CLOSE", "WRITE", "EXIT", "SHOW", "CREATE", "PKEY", "UNION", "DIFF", "PRODUCT", "OPEN",
            "GEQ", "LITERAL", "PROJECT", "RENAME", "IDENTIFIER", "SELECT", "EQ", "NEQ", "LT", "GT", "LEQ", "BOR", "BAND"};
	if(tokens[currentIndex+1].getTokenType() == type){
		nextToken();
	}
	else
		cout << "Sorry expected A "<< typestr[type] << " token type at index " << currentIndex << endl;
}

bool Executer::lookAhead(Token::TokenTypes type){
    if(!atEnd()){
        if(tokens[currentIndex + 1].getTokenType() == type)
            return true;
    }
    return false;

}
Relation* Executer::rename(){
	vector<Attribute*> aList = getAttributeList();
	Relation* relation = atomicExpr();

	string relationName = relation-> getName();
	int attributeIndex = relation -> findAttribute(aList[0] -> getName());
	engine -> renameAttribute(relationName, attributeIndex, aList[1] -> getName());
}
Relation* Executer::project(){
	vector<Attribute*> aList = getAttributeList();
	//cout << aList.at(0)->getName() << " and also by " << aList.at(0)->getName() << endl;
	Relation* relation = atomicExpr();

	cout << relation -> getName() << endl;
	Relation* newRel = engine->project(relation->getName(), aList);
	engine->createRelation(newRel);
	engine->show(newRel);
	return newRel;
}
