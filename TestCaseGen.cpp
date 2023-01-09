#include "TestCaseGen.h"
#include <iostream>
#include<string>
#include <fstream>
#include <utility>

using namespace std; 

TestCaseGen::TestCaseGen(string fileName, vector<string> varList, vector<string> outList, vector<pair<int, string> > clkList, string modName) {
	this->fileName = fileName; 
	this->varList = varList; 
	this->modName = modName; 
	this->outList = outList; 
	this->clkList = clkList; 
}

string TestCaseGen::TestCase() {
	string output_text = "";
	for (int j = 0; j < pow(2, varList.size()); j++) {
		for (int i = 0; i < varList.size(); i++) {
			string curVar = varList.at(i);
			int out = int(j / pow(2, varList.size() - 1 - i)) % 2;
			string curLine = curVar + " = " + to_string(out) + "; ";
			output_text += curLine;
		}
		output_text += "\n";
	}
	return output_text; 
}

string TestCaseGen::modCase() {
	string output_text = "module " + this->modName + "_tb(); \n"; 
	for (int i = 0; i < this->varList.size(); i++) {
		output_text += "logic " + varList.at(i) + "; \n";
	}
	output_text += " \n";
	for (int i = 0; i < this->outList.size(); i++) {
		output_text += "reg " + outList.at(i) + "; \n";
	}
	output_text += " \n";
	for (int i = 0; i < this->clkList.size(); i++) {
		pair<int, string> curPair = clkList.at(i); 
		output_text += "initial begin \n"; 
		output_text += "clk = 0 \n";
		output_text += "forever #"+ to_string(curPair.first) + " clk = ~clk \n";
		output_text += "end \n"; 
		output_text += " \n";
	}	
	output_text += this->modName + " MUT( " + varList.at(0);
	for (int i = 1; i < varList.size(); i++) {
		output_text += ", " + varList.at(i);
	}
	output_text += " ) \n";
	output_text += "initial begin \n";
	output_text +=  TestCase();
	output_text += "end \n";
	output_text += "endmodule \n";
	return output_text; 
}

void TestCaseGen::display() {
	string out = "";
	out += modCase(); 
	cout << out << endl; 
}
