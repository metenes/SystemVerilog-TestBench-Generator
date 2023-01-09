#ifndef TESTCASEGEN
#define TESTCASEGEN

#include<string>
#include<vector>
#include <utility>

using namespace std; 

class TestCaseGen {
public: 
	TestCaseGen( string fileName ,vector<string> varList, vector<string> outList , vector<pair<int, string> > clkList, string modName  );
	string TestCase(); 
	string modCase();
	void display(); 

private:
	string fileName; 
	// Lists
	vector<string> varList; 
	vector<string> outList;
	vector< pair<int, string> > clkList;
	// Module 
	string modName; 
};
#endif // TESTCASEGEN.H

