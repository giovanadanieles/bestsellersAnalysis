#include <bits/stdc++.h>

using namespace std;

#define begin1 "*** START OF THIS PROJECT GUTENBERG EBO"
#define begin2 "***START OF THE PROJECT GUTENBERG EBOOK"
#define begin3 "*** START OF THE PROJECT GUTENBERG EBOO"
#define begin4 "*END*THE SMALL PRINT! FOR PUBLIC DOMAIN"

#define begPhSize 39

#define end1 "*** END OF THIS PROJECT GUTENBERG EBO"
#define end2 "***END OF THE PROJECT GUTENBERG EBOOK"
#define end3 "*** END OF THE PROJECT GUTENBERG EBOO"

#define endPhSize 37

string outputBook;
string tempBookName = "tempFile";

void createClearedBook(ifstream &bookReadFile){
    string line;
    int nOfLines = 0, actNOfLines = 0;
    ofstream clearedBook(outputBook);

    bookReadFile.seekg(0, bookReadFile.beg);

    // counting number of lines of the file
    while(getline(bookReadFile, line)){
        nOfLines++;
    }

    // positioning pointers
    bookReadFile.clear();
    bookReadFile.seekg(0, bookReadFile.beg);
    clearedBook.seekp(0, clearedBook.beg);

    if(!clearedBook){
        cout << "Error: file not found." << endl;

        // erro no. 5
        return;
    }
    else{
        while(actNOfLines < nOfLines - 3){
            getline(bookReadFile, line);

            clearedBook << line << endl;

            actNOfLines++;
        }

        clearedBook.close();
    }

    return;
}

void findEndOfTheBook(ifstream &bookInFile, ofstream &bookOfFile){
    string line, comp;

    while(getline(bookInFile, line)){
        comp.clear();
        for(int i = 0; i < endPhSize; i++){
            comp += line[i];
        }

        if(comp != end1 && comp != end2 && comp != end3){
            bookOfFile << line << endl;
        }
        else{
            bookOfFile.close();
            ifstream bookReadFile( tempBookName.c_str() );

            createClearedBook(bookReadFile);

            bookReadFile.close();

            return;
        }
    }

    cout << "Error: final delimiter not found." << endl;

    // erro no. 4
    return;
}


void findBeginningOfTheBook(ifstream &bookInFile, ofstream &bookOfFile){
    string line, comp;

    // positioning pointer
    bookInFile.clear();
    bookInFile.seekg(0, bookInFile.beg);

    while(getline(bookInFile, line)){
        comp.clear();
        for(int i = 0; i < begPhSize; i++){
            comp += line[i];
        }

        if(comp == begin1 || comp == begin2 || comp == begin3 || comp == begin4){
            // consuming four existing blank lines
            getline(bookInFile, line);
            getline(bookInFile, line);
            getline(bookInFile, line);
            getline(bookInFile, line);

            findEndOfTheBook(bookInFile, bookOfFile);

            return;
        }

        line.clear();
    }

    cout << "Error: initial delimiter not found." << endl;

    // erro no. 3
    return;
}

int main(int argc, char* const argv[]){

    if(argc != 3){
        cout <<
        "To run, use: ./prog <.txt_gutenberg to be cleaned> <path to the folder where the file will be saved>" << endl;

        return 1;
    }
    else{
        string inputBook = argv[1];
        string path = argv[2];

        // Defining output file name
        outputBook += path;

        int i = 0;
        while(argv[1][i] != '.'){
            outputBook += argv[1][i];

            i++;
        }

        outputBook += "_cleared";

        ifstream bookInFile( inputBook.c_str() );
        ofstream bookOfFile( tempBookName.c_str() );

        if(!bookInFile || !bookOfFile){
            cout << "Error: file not found." << endl;

            return 2;
        }
        else{
            findBeginningOfTheBook(bookInFile, bookOfFile);

            if(remove(tempBookName.c_str()) != 0){
                cout << "Error: couldn't remove the file." << endl;
            }

            bookInFile.close();
        }
    }

    return 0;
}
