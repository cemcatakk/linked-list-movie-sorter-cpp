#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace::std;

class Movie{
	public:
	string name;
	float rate;
	int year;
	Movie* nameNext;
	Movie* rateNext;
	Movie* yearNext;
	Movie(string n,float r,int y){
		name=n;
		rate=r;
		year=y;
		nameNext=NULL;
		rateNext=NULL;
		yearNext=NULL;
	}
};
Movie* namehead=NULL;
Movie* yearhead=NULL;
Movie* ratehead=NULL;
void printMovie(Movie* movie){
	cout<<movie->name<<" "<<movie->rate<<" "<<movie->year<<endl;
}
void add(string name, float rate, int year){
	Movie* movie = new Movie(name,rate,year);
	Movie* temp = NULL;
	if (namehead == NULL || namehead->name >= name) {
        movie->nameNext = namehead;
        namehead = movie;
    }
    else {
        temp = namehead;
        while (temp->nameNext != NULL&& temp->nameNext->name < movie->name) {
            temp = temp->nameNext;
        }
        movie->nameNext = temp->nameNext;
        temp->nameNext = movie;
    }
    if (ratehead == NULL || ratehead->rate >= rate) {
        movie->rateNext = ratehead;
        ratehead = movie;
    }
    else {
        temp = ratehead;
        while (temp->rateNext != NULL&& temp->rateNext->rate < movie->rate) {
            temp = temp->rateNext;
        }
        movie->rateNext = temp->rateNext;
        temp->rateNext = movie;
    }
    
    if (yearhead == NULL || yearhead->year >= year) {
        movie->yearNext = yearhead;
        yearhead = movie;
    }
    else {
        temp = yearhead;
        while (temp->yearNext != NULL&& temp->yearNext->year < movie->year) {
            temp = temp->yearNext;
        }
        movie->yearNext = temp->yearNext;
        temp->yearNext = movie;
	}
}
bool _remove(string name){
	Movie* temp = namehead;
	Movie* prev=NULL;
	if (temp != NULL && temp->name==name)
    {
        namehead = temp->nameNext; 
        ratehead = temp->rateNext; 
        yearhead = temp->yearNext; 
    }
    else
    {
	    while (temp != NULL && temp->name!=name)
	    {
	        prev = temp;
	        temp = temp->nameNext;
	    }
	    if(temp==NULL){
	    	return false;
		}
	    prev->nameNext = temp->nameNext;
	    
	    temp=ratehead;
	   	while (temp != NULL && temp->name!=name)
	    {
	        prev = temp;
	        temp = temp->rateNext;
	    }
	    if(temp==NULL){
	    	return false;
		}
	    prev->rateNext = temp->rateNext;
	    temp=yearhead;
	   	while (temp != NULL && temp->name!=name)
	    {
	        prev = temp;
	        temp = temp->yearNext;
	    }
	    if(temp==NULL){
	    	return false;
		}
	    prev->yearNext = temp->yearNext;
	}
	cout<<"Movie with name "<<name<<" removed from list."<<endl;
	return true;
}
void printByYear(){
	cout<<"Movie List Sorted By Year"<<endl;
	Movie* temp = yearhead;
	while(temp!=NULL){
		printMovie(temp);
		temp = temp->yearNext;
	}
	cout<<endl;
}
void printByName(){
	cout<<"Movie List Sorted By Name"<<endl;
	Movie* temp = namehead;
	while(temp!=NULL){
		printMovie(temp);
		temp = temp->nameNext;
	}
	cout<<endl;
}
void printByRate(){
	cout<<"Movie List Sorted By Rate"<<endl;
	Movie* temp = ratehead;
	while(temp!=NULL){
		printMovie(temp);
		temp = temp->rateNext;
	}
	cout<<endl;
}
float str2float(std::string s)
{
    float number;
    stringstream ss;
    ss << s;
    ss >> number;
    return number;
}
int str2int(std::string s)
{
    int number;
    std::stringstream ss;
    ss << s;
    ss >> number;
    return number;
}
void loadFile(string filename){
	namehead=NULL;
	yearhead=NULL;
	ratehead=NULL;
	string name,ratestring,yearstring;
	int year;
	float rate;
	std::ifstream inFile(filename.c_str());
    if (inFile.is_open())
    {
        string line;
        while( std::getline(inFile,line) )
        {
            stringstream ss(line);
            getline(ss,name,'-'); 
            getline(ss,ratestring,'-'); 
            getline(ss,yearstring,'-'); 
            rate = str2float(ratestring);
            year = str2int(yearstring);
            add(name,rate,year);
            cout<<"\n";
        }
    }
}
void saveToFileByYear(string filename){
	ofstream file;
  	file.open (filename.c_str());
	Movie* temp = yearhead;
	while(temp!=NULL){
		file<<temp->name<<"-"<<temp->rate<<"-"<<temp->year<<endl;
		temp = temp->yearNext;
	}
  	file.close();
  	cout<<"Movies saved to "<<filename<< " by year"<<endl;
}
void saveToFileByName(string filename){
	ofstream file;
  	file.open (filename.c_str());
	Movie* temp = namehead;
	while(temp!=NULL){
		file<<temp->name<<"-"<<temp->rate<<"-"<<temp->year<<endl;
		temp = temp->nameNext;
	}
  	file.close();
  	cout<<"Movies saved to "<<filename<< " by name"<<endl;
}

void saveToFileByRate(string filename){
	ofstream file;
  	file.open (filename.c_str());
	Movie* temp = ratehead;
	while(temp!=NULL){
		file<<temp->name<<"-"<<temp->rate<<"-"<<temp->year<<endl;
		temp = temp->rateNext;
	}
  	file.close();
  	cout<<"Movies saved to "<<filename<< " by rate"<<endl;
}
void update(string name,double rate){
	Movie* temp = namehead;
	while(temp!=NULL){
		if(temp->name==name){
			temp->rate=rate;
		}
		temp = temp->nameNext;
	}
	saveToFileByRate("temp.txt");
	loadFile("temp.txt");
}
int main(int argc, char** argv) {
	add("LOTR",8.8,2001);
	add("Matrix",8.7,1999);
	add("Instersteller",8.6,2014);
	printByName();
	update("Instersteller",9);
	printByRate();
	printByYear();
	_remove("Instersteller");
	printByName();
	saveToFileByName("byname.txt");
	saveToFileByYear("byyear.txt");
	saveToFileByRate("byrate.txt");
	loadFile("byname.txt");
	printByName();
	printByRate();
	printByYear();
	
	return 0;
}
