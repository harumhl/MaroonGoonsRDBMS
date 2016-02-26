#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include "Engine.h"
using namespace std;

void Engine::open(string filename) {
	ifstream ifs;
	ifs.open(filename.c_str());
	
	// I will be using comas "," as delimeter (useful with cvs), assuming there will be no input with a comma
	// For attributes, I will be using "|" as delimeter (least used char), e.g. Name|String, ...
	// I will also assume the first line to be the title of the relation, the second line to be list of attributes
	bool isFirstLine = true, isSecondLine = true; // first = title, second = attributes
	string input;
	vector<string> tokenized;
	while(!ifs.eof()) {
		getline(ifs, input);
		if (trimString(input) == "") continue; // skip empty line
		
		if (!isFirstLine) // if (isFirstLine), then input must be the title so skip tokenizing
            tokenized = tokenize(input, ',');
		
		
        if (isFirstLine) { // title
            relations.push_back(new Relation());
            numRelations++;
            int rel_i = relations.size()-1;
            
            relations.at(rel_i)->setName(input);
            isFirstLine = false;
        }
        else if (isSecondLine) { // attributes
			// create and add attributes
			int rel_i = relations.size()-1; // the newest relation - assuming it was made in IF stmt
			
			bool isFirstDelimeter = true;
			vector<Attribute*> av;
			for (int i=0; i< tokenized.size(); i++) {
				vector<string> temp;
				temp = tokenize(tokenized.at(i), '|');
				
				if (temp.size() > 2) cerr << "More than one delimeter for a token in attribute list\n";
				
                Attribute::Type type;
				if (toUpper(temp.at(1)) == "VARCHAR" || toUpper(temp.at(1)) == "STRING")
					type = Attribute::VARCHAR;
				else if (toUpper(temp.at(1)) == "INTEGER" || toUpper(temp.at(1)) == "INT")
					type = Attribute::INTEGER;
				else cerr << "Unknown type\n"; // SHOULD I RETURN OR SOMETHING?

				av.push_back(new Attribute(type, temp.at(0)));	
			}
			relations.at(rel_i)->setAttributes(av);
			isSecondLine = false;
		}
		else { // tuples
			int rel_i = relations.size()-1; // the newest relation - assuming it was made in IF stmt
			
            // Checking for a type validation (e.g. if it's integer when int is expected)
			for (int i=0; i< tokenized.size(); i++) {
				try {
					vector<Attribute*> attributes = relations.at(rel_i)->getAttributes();
					
					if (attributes.at(i)->getType() == Attribute::INTEGER)
						int integer = stoi (tokenized.at(i)); // Checking if int when int is expected
				}
				catch (exception e) {
					cerr << "Tuple not in right format " << e.what() << endl;
				}
			}
			
			relations.at(rel_i)->addTuple (new Tuple(tokenized));
		}
	}
	ifs.close();
}
void Engine::close(string relation) {
    // Try to look for the relation
    int relation_index = findRelation (relation);
    if (relation_index == -1) return;
    
    write(relation, relation +".txt"); // making the filename as the relation name
    
    // Getting rid of the relation written to the file from the database
    relations.erase ( relations.begin()+relation_index );
}
void Engine::write(string relation, string filename) { // default arg = "Output.txt"
    ofstream ofs;
    ofs.open(filename.c_str());

    // Going Through each relation
    for (int i=0; i< relations.size(); i++) {
        
        Relation* a_relation = relations.at(i);
        
        // Write Out relation Name
        ofs << a_relation->getName() << endl;
        
        // Write Out Attributes
        vector<Attribute*> attributes = a_relation->getAttributes();
        for (int j=0; j< attributes.size(); j++) {
            Attribute* the_attribute = attributes.at(j);
            ofs << the_attribute->getName() << "|" << the_attribute->getTypeStr();
            
            // put delimeter except the end of the last attribute
            if (j != attributes.size()-1) ofs << ", ";
        }
        ofs << endl;
        
        // Write Out Tuples
        vector<Tuple*> tuples = a_relation->getTuples();
        for (int k=0; k< tuples.size(); k++) {
            Tuple* the_tuple = tuples.at(k);
            
            // Write Out each string
            vector<string> tuple_contents = the_tuple->getContents();
            for (int l=0; l< tuple_contents.size(); l++) {
                ofs << tuple_contents.at(l);
                
            // put delimeter except the end of the last string of each tuple
                if (l != tuple_contents.size()-1) ofs << ", ";
            }
            ofs << endl;
        }
    }
    ofs.close();
}

void Engine::exit_(){
	cerr << "Exiting Program Now";
	exit(0);
}
void Engine::show(string relation) { // TEMP implementation
    int relation_index = findRelation (relation);
    if (relation_index == -1) return;
    
    Relation* the_relation = relations.at(relation_index);

    this->show(the_relation);
}
void Engine::show(Relation* the_relation) {
    
    cout << "Relation name: " << the_relation->getName() << endl;
    cout << "Attributes #" << the_relation->getAttributes().size() << endl;
    cout << "Tuples #" << the_relation->getTuples().size() << endl << endl;
    
    // Print Out Attributes in format of typename[type], ...
    vector<Attribute*> attributes = the_relation->getAttributes();
    for (int j=0; j< attributes.size(); j++) {
        cout << attributes.at(j)->getName() << "[" << attributes.at(j)->getTypeStr() << "]\t";
    }
    cout << endl;
    
    // Print Out Tuples
    vector<Tuple*> tuples = the_relation->getTuples();
    for (int j=0; j< tuples.size(); j++) {
        // print out each string
        for (int k=0; k< tuples.at(j)->getContents().size(); k++) {
            cout << tuples.at(j)->getContents().at(k) << "\t";
        }
        cout << endl;
    }
    cout << endl;
    
}
void Engine::createRelation(string relation, vector<Attribute*> attributes) {
	relations.push_back(new Relation(relation, attributes));
	numRelations++;
}
void Engine::createRelation(Relation* relation) {
	relations.push_back(relation);
	numRelations++;
}

void Engine::dropRelation(string relation){
	int relation_index = findRelation (relation);
	if (relation_index == -1) return;
    
	relations.erase( relations.begin()+relation_index );
	numRelations--;
}
void Engine::renameRelation(string relation, string new_name) {
    int relation_index = findRelation (relation);
    if (relation_index == -1) return;
    
    relations.at(relation_index)->setName(new_name);
}

void Engine::renameAttribute(string relation, int attribute_index, string new_name) {
	int relation_index = findRelation (relation);
	if (relation_index == -1) return;
    
	relations.at(relation_index)->getAttribute(attribute_index)->setName(new_name);
}
void Engine::insertTuple(string relation, Tuple* tuple) {
	int relation_index = findRelation (relation);
	if (relation_index == -1) return;
    
	relations.at(relation_index)->addTuple(tuple);
}
void Engine::deleteTuple(string relation, int tuple_index) {
	int relation_index = findRelation (relation);
	if (relation_index == -1) return;
	relations.at(relation_index)->removeTuple(tuple_index);
}
void Engine::update(Relation* relation, int attributeIndex, Tuple* tuple, string newData){
	tuple->changeContent(attributeIndex, newData);
}
Relation* Engine::select(string relation, vector<string> attributeNames, Tree* tree) {
	/* party = "Republican" 
	OR Years > 3 
	OR Name In USRepTable (== EXISTS (USREP)) 
	OR Party = ANY (CurrentPTable) 
	OR Years > All (YearTABLE) */
	
	// The Ideal data structure for Conditions will be tree
    
    int relation_index = findRelation (relation);
    if (relation_index == -1) return nullptr;

    Relation* given_relation = relations.at(relation_index);
    
    // Filling Up Attributes For the_relation
    vector<Attribute*> given_attributes = given_relation->getAttributes();
    vector<int>        attribute_indices; // Which attribute/column to save
    vector<Attribute*> the_attributes = findAttributes(relation, attributeNames, attribute_indices);
    
    Relation* the_relation = new Relation("Relation from SELECT command", the_attributes);

    // Filling Up Tuples For the_relation
    vector<Tuple*> given_tuples = given_relation->getTuples();
//    vector<int> tuple_indices; // Which tuple/row to save
    
    // fill up vector<Tuple*> the_tuples for the_relation under vector<Attribute*> the_attributes
    for (int i=0; i< given_tuples.size(); i++) {
        // Outer Loop goes through every tuple/row
        Tuple* a_tuple = given_tuples.at(i);
        
        if (tree->evalTree(a_tuple, given_attributes, NULL))
            the_relation->addTuple(a_tuple);
    }

    return the_relation;
}
Relation* Engine::project(string relationName, vector<Attribute*> attributes){
    int index = findRelation(relationName);
    Relation* theRelation = relations.at(index);
    vector<Attribute*> oldAttributes = theRelation->getAttributes();
    Relation* project_relation = new Relation("projection", attributes);
    vector<Tuple*> newTuples;// = relation_1->getTuples();
    int numCols = attributes.size();
    int numRows = theRelation->getTuples().size();
    Tuple* tempPtr;
    string tempData;
    int oldColumnIndex, newColumnIndex;
    string currentColumn;
    for(int i = 0; i < numRows; i++){
        Tuple* tempTuple = new Tuple;
        tempPtr = theRelation->getTuple(i);
        for(int j = 0; j < numCols; j++){
            oldColumnIndex = theRelation->findAttribute(attributes.at(j)->getName());
            tempTuple->addContent(tempPtr->getContent(oldColumnIndex));
            //currentColumnIndex = theRelation->findAttribute(attributes.at(j))->getName();
            //tempData = tempPtr->getContent(j);
        }
        project_relation->addTuple(tempTuple);
    }
    return project_relation;
}
Relation* Engine::union_(string relation1, string relation2){
    if(isUnionCompatible(relation1, relation2) == false){
		cerr << "Error! Can't take the union of two non-union-compatible relations";
	}
	int relation1_index = findRelation(relation1);
	int relation2_index = findRelation(relation2);
    if (relation1_index == -1 || relation2_index == -1) return nullptr;
	
	Relation* relation_1 = relations.at(relation1_index);
	Relation* relation_2 = relations.at(relation2_index);

	vector<Attribute*> attributes1 = relations.at(relation1_index)->getAttributes();
	vector<Attribute*> attributes2 = relations.at(relation2_index)->getAttributes();

	vector<Tuple*> tuples1 = relation_1->getTuples();
	vector<Tuple*> tuples2 = relation_2->getTuples();
	string name = "Union";
	Relation* union_relation = new Relation(name, attributes1);
	for(int i = 0; i < tuples1.size(); i++){
		Tuple* tuple = relations.at(relation1_index)->getTuple(i);
		union_relation->addTuple(tuple);
	}
	for(int j = 0; j < tuples2.size(); j++){
		Tuple* tuple = relations.at(relation2_index)->getTuple(j);
		if(tupleExists(union_relation, tuple) == false){
			union_relation->addTuple(tuple);
		}
	}
	return union_relation;
}
Relation* Engine::difference(string relation1, string relation2){
	if(isUnionCompatible(relation1, relation2) == false){
		cerr << "Error! Can't take the differnece of a two non-union-compatible relations";
	}

	int relation1_index = findRelation(relation1);
	int relation2_index = findRelation(relation2);
    if (relation1_index == -1 || relation2_index == -1) return nullptr;

	Relation* relation_1 = relations.at(relation1_index);
	Relation* relation_2 = relations.at(relation2_index);

	vector<Attribute*> attributes1 = relation_1->getAttributes();
	vector<Attribute*> attributes2 = relation_2->getAttributes();

	vector<Tuple*> tuples1 = relation_1->getTuples();
	vector<Tuple*> tuples2 = relation_2->getTuples();

	string name = "Difference";
	Relation* differenceRelation = new Relation( name, attributes1);

	for(int i = 0; i < tuples1.size(); i++){
		Tuple* tuple = relations.at(relation1_index)->getTuple(i);
		differenceRelation->addTuple(tuple);
	}

	for(int j = 0; j < tuples2.size(); j++){
		Tuple* tempTuple = relations.at(relation2_index)->getTuple(j);
		if(tupleExists(differenceRelation, tempTuple))
			deleteTuple(differenceRelation->getName(), j);
	}
	return differenceRelation;
}
Relation* Engine::crossProduct(string relation1, string relation2) {
	int relation1_index = findRelation (relation1);
	int relation2_index = findRelation (relation2);
    if (relation1_index == -1 || relation2_index == -1) return nullptr;
	
	// WE NEED TO GET THE NAMING ALL SAME!!!
	Relation* relation_1 = relations.at(relation1_index);
	Relation* relation_2 = relations.at(relation2_index);
	vector<Attribute*> attributes1 = relation_1->getAttributes();
	vector<Attribute*> attributes2 = relation_2->getAttributes();
	vector<Tuple*> tuples1 = relation_1->getTuples();
	vector<Tuple*> tuples2 = relation_2->getTuples();
	
	pair<int,int> sameAttributeIndex = findSameAttribute(relation1, relation2);
	if (sameAttributeIndex.first != -1) cerr << "Same Attributes Found For Cross Product\n";
	
	vector<Attribute*> the_attributes;
	// the_attributes = attributes1 + attributes2
	the_attributes.reserve(attributes1.size() + attributes2.size() ); // preallocate memory
	the_attributes.insert( the_attributes.end(), attributes1.begin(), attributes1.end() );
	the_attributes.insert( the_attributes.end(), attributes2.begin(), attributes2.end() );

	string temp = "crossProduct of " +relation_1->getName() +" & " +relation_2->getName();
	Relation* the_relation = new Relation(temp, the_attributes);
	
	for (int i=0; i< tuples1.size(); i++) {
		for (int j=0; j< tuples2.size(); j++) {
			vector<string> the_tuple_contents;
			vector<string> tuples1_content = tuples1.at(i)->getContents();
			vector<string> tuples2_content = tuples2.at(j)->getContents();
            
			// the_tuple_contents = tuples1_content + tuples2_content
			the_tuple_contents.reserve(tuples1_content.size() + tuples2_content.size() ); // preallocate memory
			the_tuple_contents.insert( the_tuple_contents.end(), tuples1_content.begin(), tuples1_content.end() );
			the_tuple_contents.insert( the_tuple_contents.end(), tuples2_content.begin(), tuples2_content.end() );
			
			the_relation->addTuple(new Tuple(the_tuple_contents));
		}
	}
	
	return the_relation;
}
Relation* Engine::naturalJoin(string relation1, string relation2) {
	int relation1_index = findRelation (relation1);
	int relation2_index = findRelation (relation2);
    if (relation1_index == -1 || relation2_index == -1) return nullptr;
	
	// WE NEED TO GET THE NAMING ALL SAME!!!
	Relation* relation_1 = relations.at(relation1_index);
	Relation* relation_2 = relations.at(relation2_index);
	vector<Attribute*> attributes1 = relation_1->getAttributes();
	vector<Attribute*> attributes2 = relation_2->getAttributes();
	vector<Tuple*> tuples1 = relation_1->getTuples();
	vector<Tuple*> tuples2 = relation_2->getTuples();
	
	vector<pair<int,int>> matchingColumns = attributesInBoth(relation1, relation2);
	//need a function which compares tuples in 2 relations and finds a common index
	//of all tuple pairs, in order to populate the final naturaljoin relation
	if(matchingColumns.size() == 0){
		cerr << "Error, these relations cannot be joined";
	}
	pair<int,int> sameAttributeIndex = matchingColumns.back();
	//need a pair<int,int> sameTupleIndex; that compares relations based on the
	//datapoints in tuples at the common attribute index, only adding tuples that are ;
	matchingColumns.pop_back();
	int index1 = sameAttributeIndex.first;
	string commonAttName = attributes1.at(index1)->getName();
	int index2 = sameAttributeIndex.second;
	vector<Attribute*> the_attributes;
	vector<Tuple*> theTuples;
	int priorityRelation; //is a 1 or 2 depending on which attribute list was longer
	if(attributes1.size() >= attributes2.size()){
		the_attributes = attributes1;
		Attribute* tempAtt;
		for(int i = 0; i < attributes2.size(); i++){
			if(i != index2){
				tempAtt = attributes2.at(i);
				the_attributes.push_back(tempAtt);
			}
		}
		priorityRelation = 1;
	}
	else{
		the_attributes = attributes2;
		Attribute* tempAtt;
		for(int i = 0; i < attributes1.size(); i++){
			if(i != index1){
				tempAtt = attributes1.at(i);
				the_attributes.push_back(tempAtt);
			}
		}
		priorityRelation = 2;
	}
	//if(priorityRelation == 1){
		//theTuples = tuples1;

	//}
	//else{
	//	theTuples = tuples2;
	//}
	vector<pair<int,int>> commonTuples = tuplesInBoth(relation1, relation2, commonAttName);
	//cout << "Found " << commonTuples.size() << " common tuples" << endl;
	int first, second;
	pair<int,int> currentTuple;
	Tuple* t1;
	Tuple* t2;
	string newData;
	for(int j = 0; j <= commonTuples.size()+1; j++){
		currentTuple = commonTuples.back();
		commonTuples.pop_back();
		first = currentTuple.first;
		second = currentTuple.second;
		t1 = tuples1.at(first);
		t2 = tuples2.at(second);
		for(int k = 0; k < attributes2.size(); k++){
			if(attributes2.at(k)->getName() != commonAttName){
				newData = t2->getContent(k);
				t1->addContent(newData);
			}
		}
		//cout << "trying to addtuple " << j << " to the rel" << endl;
		theTuples.push_back(t1);
		//cout << "added tuple" << endl;
	}

	Relation* the_joined_relation = new Relation("joinedRelation", the_attributes);
	the_joined_relation->setTuple(theTuples);
	relations.push_back(the_joined_relation);
	return the_joined_relation;
}
//Checks to see if a tuple exists in a relation
bool Engine::tupleExists(Relation* relation, Tuple* tuple){
	for(int i = 0; i < relation->getTuples().size(); i++){
		Tuple* tupleCheck = relation->getTuple(i);
		if(tupleCheck->getContents() == tuple->getContents())
			return true;
	}
	return false;
}
vector<pair<int,int>> Engine::attributesInBoth(string relation1, string relation2){
	int nummatches = 0;
	int relation1_index = findRelation (relation1);
	int relation2_index = findRelation (relation2);
	vector<Attribute*> attributes1 = relations.at(relation1_index)->getAttributes();
	vector<Attribute*> attributes2 = relations.at(relation2_index)->getAttributes();
	pair<int, int> indices;
	vector<pair<int,int>> matchingColumns;
	for(int i = 0; i< attributes1.size();i++){
		for(int j = 0; j < attributes2.size(); j++){
			if(attributes1.at(i)->getName() == attributes2.at(j)->getName()){
							indices.first = i;
							indices.second = j;
							matchingColumns.push_back(indices);
							nummatches++;
			}
		}
	}
	//cout << "Found " << nummatches << " number of matching colums\n";
	return matchingColumns;
}
vector<pair<int,int>> Engine::tuplesInBoth(string relation1, string relation2, string commonAtt){
	int relation1_index = findRelation (relation1);
	int relation2_index = findRelation (relation2);
	vector<Tuple*> tuples1 = relations.at(relation1_index)->getTuples();
	vector<Tuple*> tuples2 = relations.at(relation2_index)->getTuples();
	int attribute1index = relations.at(relation1_index)->findAttribute(commonAtt);
	int attribute2index = relations.at(relation2_index)->findAttribute(commonAtt);
	pair<int, int> indices;
	vector<pair<int,int>> matches;
	string data1, data2;
	Tuple* tempTuple1;
	Tuple* tempTuple2;
	for(int i = 0; i < tuples1.size(); i++){
		tempTuple1 = tuples1.at(i);
		data1 = tempTuple1->getContent(attribute1index);
		for(int j = 0; j < tuples2.size(); j++){
			tempTuple2 = tuples2.at(j);
			data2 = tempTuple2->getContent(attribute2index);
			//cout<<data2 << " versus " << data1 << endl;
			if(data1 == data2){
				indices.first = i;
				indices.second = j;
				matches.push_back(indices);
			}
		}
	}
	return matches;

}
void Engine::changeRelationName (int relation_index, string relation) {
	relations.at(relation_index)->setName(relation);
}
string Engine::relationName(int index){
	string name = relations.at(index)->getName();
	return name;
}
vector<string> Engine::tokenize (string input, char delimeter) {
	vector<string> tokenized;
	string token;
	
	stringstream ss(input); // Turn the string into a stream.
  	
  	while(getline(ss, token, delimeter)) { // args: input, output_str, delimeter
  		token = trimString(token); 
    		tokenized.push_back(token);
  	}
	return tokenized;
}
pair<int,int> Engine::findSameAttribute (string relation1, string relation2) { 
	// if attributes of same name are found from each relation, then return the indices from relations, 
	// or not found, then return the pair <-1, ?>
	// if more than one attributes are found to be same, then return the pair <-99, ?>
	
	int relation1_index = findRelation (relation1);
	int relation2_index = findRelation (relation2);
    if (relation1_index == -1 || relation2_index == -1) return pair<int,int>();
	
	vector<Attribute*> attributes1 = relations.at(relation1_index)->getAttributes();
	vector<Attribute*> attributes2 = relations.at(relation2_index)->getAttributes();
	
	pair<int,int> indices;
	indices.first = -2; // random number, neither -1 nor -99
	bool found_only_once = false; // To find if more than one attributes from each relation are same
	for (int i=0; i< attributes1.size(); i++) {
		for (int j=0; j< attributes2.size(); j++) {
			if (attributes1.at(i)->getName() == attributes2.at(j)->getName())
				indices.first = i;
				indices.second = j;
				if (found_only_once == false) found_only_once = true;
				if (found_only_once == true) indices.first = -99; // MORE THAN ONE ATTRIBUTES ARE SAME!
		}
	}
	if (found_only_once == false) indices.first = -1; // found_only_once == false, thus not found
	
	return indices;
}
string Engine::trimString (string str) {
	size_t first = str.find_first_not_of(' ');
	size_t last = str.find_last_not_of(' ');
	
    	if (str == "" || str.size() < first+last) return ""; // empty string
    	
    	return str.substr(first, (last-first+1));
}
string Engine::toUpper (string str) {
	for(int i = 0; i < str.size(); i++) {
		str.at(i) = toupper(str.at(i));
	}
	return str;
}
bool Engine::isUnionCompatible (string relation1, string relation2) {
	// the two relations must have the same set of attributes (same number AND data type for the attributes)
	int rel_i1 = findRelation (relation1);
	int rel_i2 = findRelation (relation2);
	if (rel_i1 == -1 || rel_i2 == -2) { 
		cerr << "Relation Not Found For Union Compatibility Check\n"; 
		return false; 
	}
	// Different number of attributes
	if (relations.at(rel_i1)->getAttributes().size() != relations.at(rel_i2)->getAttributes().size())
		return false;
	vector<Attribute*> attributes1 = relations.at(rel_i1)->getAttributes(); // vector does deep copy
	vector<Attribute*> attributes2 = relations.at(rel_i2)->getAttributes();
	// If we find attributes of same type from each vector, then they will be eraseed from each vector
	for (int i=0; i< attributes1.size(); i++) {
		for (int j=0; j< attributes2.size(); j++) {
			if (attributes1.at(i)->getType() == attributes2.at(j)->getType()) {
				attributes1.erase( attributes1.begin()+i );
				attributes2.erase( attributes2.begin()+j );
				i = i-1; // attributes1.at(i) is erased, so the next element i+1 moves to i.
				break; // start with new attributes1 element and from attributes2[0]
			}
			// The inner for loop went through the whole attributes2, but did not find a match?
			if (j == attributes2.size()-1)
				return false;
			// Every attribute from each attributes matched up, so they are union compatible!
			if (attributes1.size() == 0 && attributes2.size() == 0)
				return true;
		}
		if (attributes1.size() == 0 && attributes2.size() == 0)
			return true;
	}
	if (attributes1.size() == 0 && attributes2.size() == 0)
		return true;
	return false;
}
bool Engine::testCondition (string relation, Tuple* tuple, Condition* condition) {
    int relation_index = findRelation (relation);
    if (relation_index == -1) return false;

    vector<Attribute*> the_attributes = relations.at(relation_index)->getAttributes();
    Attribute* condition_attribute;
    int condition_attribute_index;
    for (int i=0; i< the_attributes.size(); i++) {
        if (the_attributes.at(i)->getName() == condition->getOp1()) {
            condition_attribute = the_attributes.at(i);
            condition_attribute_index = i;
            break;
        }
    }
    string given_content = tuple->getContents().at(condition_attribute_index);
    string comparing_content = condition->getOp2();
    cerr<< "GIVEN: " << given_content << "\tCOMPARING: " << comparing_content << endl;

    if      (condition->getOp() == "==") return given_content == comparing_content ;
    else if (condition->getOp() == "!=") return given_content != comparing_content ;
    
    int given_int = -1, comparing_int = -1;
    if (condition_attribute->getType() == Attribute::INTEGER) {
        given_int = stoi (given_content);
        comparing_int = stoi (condition->getOp2());
    }
    if      (condition->getOp() == "<")  return given_int < comparing_int ;
    else if (condition->getOp() == "<=") return given_int <= comparing_int ;
    else if (condition->getOp() == ">")  return given_int > comparing_int ;
    else if (condition->getOp() == ">=") return given_int >= comparing_int ;
    return false;
}
int Engine::findRelation (string relation) {
	for (int i=0; i<relations.size(); i++) {
		if (relations.at(i)->getName() == relation)
			return i;
	}
	cerr << "Relation with given name \"" << relation << "\" not found." << endl;
	return -1; // not found
}
vector<Attribute*> Engine::findAttributes(string relation, vector<string> attributeNames, vector<int>& attribute_indices) {
    int relation_index = findRelation (relation);
    if (relation_index == -1) return {};
    
    Relation* the_relation = relations.at(relation_index);
    vector<Attribute*> the_attributes; //  = findAttributes(relation, attributeNames, );
    
    // fill up vector<Attribute*> the_attributes for the_relation from vector<string> attributeNames
    for (int i=0; i< attributeNames.size(); i++) {
        for (int j=0; i< the_relation->getAttributes().size(); j++) {
            if (attributeNames.at(i) == the_relation->getAttributes().at(j)->getName()) {
                the_attributes.push_back( the_relation->getAttributes().at(j) );
                attribute_indices.push_back(j);
                break; // Going to next i
            }
        }
    }
    return the_attributes;
}
