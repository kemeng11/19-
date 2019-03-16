#include<stdio.h>
#include "iostream"
#include<vector>
using namespace std;

bool carDataRead(string carPath, vector<vector<int> > &carData){



}

bool roadDataRead(string roadPath, vector<vector<int> > &roadData){



}

bool crossDataRead(string crossPath, vector<vector<int> > &crossData){



}
bool answerDataWrite(string answerPath, vector<vector<int> > &plannedPath){



}

int main()
{
    std::cout << "Begin" << std::endl;
    string carPath = ".\config\car.txt";
    string roadPath = ".\config\cross.txt";
    string crossPath = ".\config\road.txt";
    string answerPath = ".\config\answer.txt";




	std::cout << "carPath is " << carPath << std::endl;
	std::cout << "roadPath is " << roadPath << std::endl;
	std::cout << "crossPath is " << crossPath << std::endl;
	std::cout << "answerPath is " << answerPath << std::endl;

	// TODO:read input filebuf
	// TODO:process
	// TODO:write output file

	return 0;
}
