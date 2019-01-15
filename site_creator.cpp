#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

//Converts an int to a string
string to_str(int i) {
    stringstream out;
    out << i;
    return out.str();
}

string charToStr(char c) {
    string temp = "";
    temp += c;
    return temp;
}

//Will grab some random names and push them into currentSolutionNames
void generate_names(vector<string> & allNames, vector<string> & currentSolutionNames, int n) {
    int randNum;
    for (int i = 0; i < n; i++) {
        randNum = rand() % allNames.size();
        string name = allNames[randNum];
        bool seen = false;

        for (int j = 0; j < currentSolutionNames.size(); j++) {
            if (name == currentSolutionNames[j]) {
                seen = true;
            }
        }

        if (seen == false) {
            currentSolutionNames.push_back(name);
        } 
        else {
            i--;
        }
    }

    for (int i = 0; i < currentSolutionNames.size(); i++) {
        currentSolutionNames[i][0] = toupper(currentSolutionNames[i][0]);

        for(int j = 1 ; j < currentSolutionNames[i].length() ; j++)
            currentSolutionNames[i][j] = tolower(currentSolutionNames[i][j]);
    }

}

string create_identifier(string & solutionCode, vector<string> & names) {
    string result = "<p>";
    
    string temp = charToStr(solutionCode[0]);
    result += names[atoi(temp.c_str())];

    result += " is a <span class=\"spoiler\">";

    temp = charToStr(solutionCode[4]);
    if (temp == "0") {
        result += "knave.";
    }
    else if (temp == "1") {
        result += "knight.";
    }

    result += "</span></p>";

    return result;
}

string create_saying(string & solutionCode, vector<string> & names) {
    string result = "<p>";
    string temp;
    string sayerName;

    //Push the name of the sayer onto the result
    temp = charToStr(solutionCode[0]);
    sayerName = names[atoi(temp.c_str())];
    result += sayerName;
    result += " ";

    //Push some variation of says
    int randNum;
    randNum = rand() % 4;

    switch(randNum) {
        case 0:
            result += "tells you that, \"";
            break;
        case 1:
            result += "wants you to know that, \"";
            break;
        case 2:
            result += "lets you know that, \"";
            break;
        case 3:
            result += "says that, \"";
            break;
    }

    char messageCode = solutionCode[4];
    temp = charToStr(solutionCode[6]);
    string p1 = names[atoi(temp.c_str())];
    string p2;
    string p1connective, p2connective;

    if (messageCode >= 'c') {
        temp = charToStr(solutionCode[8]);
        p2 = names[atoi(temp.c_str())];
    } else {
        p2 = "";
    }

    p1connective = " is ";
    p2connective = " is ";

    if (p1 == sayerName) {
        p1 = "I";
        p1connective = " am ";
    }
    else if (p2 == sayerName) {
        p2 = "I";
        p2connective = " am ";
    }

    switch(messageCode) {
        case 'a':
            randNum = rand() % 2;
            if (rand == 0) {
                result = result + p1 + p1connective + "a knight.";
            } else {
                result = result + p1 + p1connective + "not a knave.";
            }
            break;
        case 'b':
            randNum = rand() % 2;
            if (rand == 0) {
                result = result + p1 + p1connective + "a knave.";
            } else {
                result = result + p1 + p1connective + "not a knight.";
            }
            break;
        case 'c':
            randNum = rand() % 2;
            if (rand == 0) {
                result = result + p1 + p1connective + "a knight and " + p2 + p2connective + "a knight.";
            } else {
                result = result + p1 + " and " + p2 + " are both knights";
            }
            break;
        case 'd':
            randNum = rand() % 2;
            if (rand == 0) {
                result = result + p1 + p1connective + "a knight but " + p2 + p2connective + "a knave.";
            } else {
                result = result + p1 + p1connective + "a knight and " + p2 + p2connective + "not.";
            }
            break;
        case 'e':
            if (rand == 0) {
                result = result + p1 + p1connective + "not a knight but " + p2 + p2connective + ".";
            } else {
                result = result + p1 + p1connective + "not a knight, though " + p2 + p2connective + "one.";
            }
            break;
        case 'f':
            if (rand == 0) {
                result = result + "Both " + p1 + " and " + p2 + " are knaves.";
            } else {
                result = result + p1 + p1connective + "a knave and so" + p2connective + p2 + ".";
            }
            break;
        case 'g':
            if (rand == 0) {
                result = result + "Either " + p1 + p1connective + "a knight or " + p2 + p2connective + ".";
            } else {
                result = result + p1 + " and " + p2 + " can not both be knaves.";
            }
            break;
        case 'h':
            if (rand == 0) {
                result = result + "Either " + p1 + p1connective + "a knight or " + p2 + p2connective + "a knave.";
            } else {
                result = result + "It cannot be that both " + p1 + p1connective + "a knave and " + p2 + p2connective + "a knight.";
            }
            break;
        case 'i':
            if (rand == 0) {
                result = result + "If " + p1 + p1connective + "a knight, then " + p2 + p2connective + "a knight.";
            } else {
                result = result + "Either " + p1 + p1connective + "a knave or " + p2 + p2connective + "a knight.";
            }
            break;
        case 'j':
            if (rand == 0) {
                result = result + p1 + " and " + p2 + " are not both knights.";
            } else {
                result = result + p1 + p1connective + "a knave or " + p2 + p2connective + "a knave.";
            }
            break;
        case 'k':
            if (rand == 0) {
                result = result + p1 + p1connective + "the same type of person as " + p2 + p2connective + ".";
            } else {
                result = result + p1 + p1connective + "not different than " + p2 + p2connective + ".";
            }
            break;
        case 'l':
            if (rand == 0) {
                result = result + p1 + p1connective + "different than " + p2 + p2connective + ".";
            } else {
                result = result + p1 + " and " + p2 + " are not both knights and they are not both knaves.";
            }
            break;
    }

    result += "\"</p>";
    return result;
}

int main() {
    int n, OFFSET, ALTERNATOR;

    srand(time(NULL));
    cout << "Please enter the size of the puzzles you are going to create ==>";
    cin >> n;
    cout << endl;

    if (n != 2 && n != 3 && n != 4) {
        cout << "That is not a very good n";
    }

    cout << "Please enter an offset to the start of the file names ==>";
    cin >> OFFSET;
    cout << endl;

    cout << "Please enter the number you would like to add between html file creations ==>";
    cin >> ALTERNATOR;
    cout << endl;

    if (ALTERNATOR == 0) {
        ALTERNATOR = 1;
    }

    vector<string> allNames;

    string line;
    ifstream nameFile("names.txt");

    //Read in the list of names
    if (nameFile.is_open()) {
        while (getline (nameFile,line)) {
            allNames.push_back(line);
        }
    }
    else {
       cout << "There was an error opening up the name file!" << endl;
       return 1;
    }

    nameFile.close();

    //Now we need to load the solutions
    string solutionFileName = "result" + to_str(n) + ".txt";
    ifstream solutionFile(solutionFileName.c_str());

    vector<string> sayings;
    vector<string> solutions;

    int num_solutions = 0;

    if (solutionFile.is_open()) {
        while (!solutionFile.eof()) {
            //Read in what the people will say
            for (int i = 0; i < n; i++) {
                getline(solutionFile, line);
                
                //This is just in case there is an extra \n at the end of the txt file
                if (line != "\n") {
                    sayings.push_back(line);
                }
            }
            //Read in what the people are
            for (int i = 0 ; i < n; i++) {
                getline(solutionFile, line);
                solutions.push_back(line);
            }

            //Catch the blank line
            getline(solutionFile, line);

            num_solutions++;
        } 
    }
    else {
        cout << "There was an error opening up the solutions file!" << endl;
        return 1;
    }

    solutionFile.close();

    cout << "The number of found solutions is " << num_solutions << ". Solution numbers will start at " << (OFFSET + 1) << " and every " << ALTERNATOR << " solutions will be generated" << endl;

    int counter = OFFSET;
    vector<string> currentSolutionNames;
    vector<string> html;
    vector<string> identity;

#if 0
    //Debug info
    for (int i = 0; i < allNames.size(); i++) {
        cout << "Name[" << i << "] is " << allNames[i] << endl;
    }
    for (int i = 0; i < sayings.size(); i++) {
        cout << sayings[i] << endl;
    }
    for (int i = 0; i < solutions.size(); i++) {
        cout << solutions[i] << endl;
    }
#endif

#if 1
    //For each of the solutions
    for (int i = 0; i < sayings.size(); i += (ALTERNATOR * n)) {
        //Add to the solution count
        counter++;

        //Clear the solutions from last time
        html.clear();
        identity.clear();
        currentSolutionNames.clear();

        //Generate some random names
        generate_names(allNames, currentSolutionNames, n);

        //For each of the people in the solution
        for (int j = 0; j < n; j++) {
            html.push_back(create_saying(sayings[i + j], currentSolutionNames));
            identity.push_back(create_identifier(solutions[i + j], currentSolutionNames));
        }

        //Write the html file with our new fangled sayings and solutions
        string htmlFileName = "Puzzles/knightsandknaves" + to_str(counter) + ".html";
        ofstream htmlFile;
        htmlFile.open(htmlFileName.c_str());
        htmlFile << "<!DOCTYPE html><style type=\"text/css\">.spoiler{color: black;background-color:black;display:inline;}.spoiler:hover{color: white;}</style><html><title>Knights and Knaves</title><link rel=\"stylesheet\" href=\"http://www.w3schools.com/lib/w3.css\"><body><div class=\"w3-container w3-padding-32 w3-dark-grey\"><img src=\"kak.png\" style=\"height:300px; display:block; margin:auto;\"><h1 style=\"text-align:center;\">Knights and Knaves Puzzle #" << counter << "</h1></div><div class=\"w3-container w3-padding-16 w3-light-grey\"><h3>While traveling, you come across a group. You introduce yourself, and they tell you that their names are ";
        
        for (int i = 0; i < n; i++) {
            if (n == 2) {
                if (i == 0) {
                    htmlFile << currentSolutionNames[i];
                }
                else {
                    htmlFile << " and " << currentSolutionNames[i] << ".";
                }
            }
            else {
                if (i == (n - 1)) {
                    htmlFile << " and " << currentSolutionNames[i] << ".";
                }
                else {
                    htmlFile << currentSolutionNames[i] << ", ";
                }
            }
        }

        htmlFile << "</h3>";

        for (int i = 0; i < n; i++) {
            htmlFile << html[i];
        }

        htmlFile << "<h3>Solution:</h3>";

        for (int i = 0; i < n; i++) {
            htmlFile << identity[i];
        }

        htmlFile << "<div class=\"w3-container w3-padding-16 w3-dark-grey\"><h3 style=\"text-align:center\">Puzzle #";
        htmlFile << counter;
        htmlFile << "</h3><p style=\"text-align:left; display:inline-block; width:49%;\"><a href=\"";
        htmlFile << "knightsandknaves" << counter - 1 << ".html";
        htmlFile << "\">&lt&lt Previous Puzzle</a></p><p style=\"text-align:right; display:inline-block; width:50%;\"><a href=\"";
        htmlFile << "knightsandknaves" << counter + 1 << ".html";
        htmlFile << "\">Next Puzzle &gt&gt</a></p></div></body></html>";

        htmlFile.close();
    }
#endif
    
    return 0;
}
