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
        	/*case Token::DELETE:
        	    	deleteRows();
        	    	break;
        	case Token::UPDATE:
        	    	update();
        	    	break;*/
        	case Token::CREATE:
        	    	//create();
        	    	break;
        	/*case Token::INSERT:
        	    	insert();
        	    	break;*/
	}
}
void Executer::query(){
	cout << "query branch taken" << endl;
	string relationName = token.getValue();
	cout << "We want a relation named " << relationName << endl;
	expect(Token::LEFTARROW);
	nextToken();
	Relation* relPtr;
	relPtr = expr();
	cerr << "The program doesn't crash" << endl;
	//engine->renameRelation(relPtr, relationName);
	//engine->createRelation(relPtr);

}
void Executer::expect(Token::TokenTypes type){
	if(tokens[currentIndex+1].getTokenType() == type){
		nextToken();
	}
	else
		cerr << "Sorry expected different token type" << endl;
}
void Executer::setToken(){
	token = tokens[currentIndex];
}
void Executer::nextToken(){
	bool endCheck = atEnd();
	if(endCheck == true)
		cerr << "sorry we are at the end of the vector of tokens" << endl;
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
    
    if(lookAhead(Token::UNION) || lookAhead(Token::PRODUCT) || lookAhead(Token::DIFF))
        relation = combine(relation);
    return relation;
}
vector<Attribute*> Executer::getAttributeList(){
	expect(Token::LEFTPAREN);
	nextToken();
	vector<Attribute*> attList;
	while(token.getTokenType() == Token::IDENTIFIER){
		attList.push_back(new Attribute(VARCHAR, token.getValue()));
		nextToken();
		if((token.getTokenType() != Token::COMMA)&&(token.getTokenType() != Token::RIGHTPAREN))
			cerr << "Attribute list in wrong format" << endl;
		if(token.getTokenType() == Token::COMMA)
			nextToken();
	}
	//now we should be left with right paren
	nextToken();
	return attList;
}
Relation* Executer::combine(Relation* relation){
	Relation* relation1 = relation;
	nextToken();
	Token op = token;
	nextToken();
	Relation* relation2 = atomicExpr();
	switch(op.getTokenType()){
		case Token::PRODUCT:
			//return engine->crossProduct(relation1->getName(), relation2->getName);
			break;
		case Token::UNION:
			return engine->union_(relation1->getName(), relation2->getName());
			break;
		case Token::DIFF:
			return engine->difference(relation1->getName(), relation2->getName());
			break;
	}

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
