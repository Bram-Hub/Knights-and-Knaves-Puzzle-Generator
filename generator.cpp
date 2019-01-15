#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <vector>

#define NUM_PEOPLE 2

using namespace std;

int choose(int n, int k) {
    if (k == 0) {
    	 return 1;
    }
    return (n * choose(n - 1, k - 1)) / k;
}

string get_op(int opNum) {
	string result = "";
	result += (char) (opNum + 97);
	return result;
}

void find_numerical_subsets_helper(int results_size, int** results, int &results_counter, bool* current_solution, int max_num, int subset_size, int current_length, int start) {
	//first check if we have found a solution
	if (current_length == subset_size) {
		if (results_counter < results_size) {
			int sol_counter = 0;
			for (int i = 0; i < max_num; i++) {
				if (current_solution[i] == true) {
					results[results_counter][sol_counter] = i;
					sol_counter++;
				}
			}
			results_counter += 1;
		}
	}
	//if not, do some permutations
	else {
		if (start < max_num) {
			current_solution[start] = true;
			find_numerical_subsets_helper(results_size, results, results_counter, current_solution, max_num, subset_size, current_length + 1, start + 1);
			current_solution[start] = false;
			find_numerical_subsets_helper(results_size, results, results_counter, current_solution, max_num, subset_size, current_length, start + 1);
		}
	}

}

int** find_numerical_subsets(int max_num, int subset_size) {
	int num_sol = choose(max_num, subset_size);

	int** results = new int*[num_sol];
	bool* current_solution = new bool[max_num];

	for (int i = 0; i < max_num; i++) {
		current_solution[i] = false;
	}

	for (int i = 0; i < num_sol; i++) {
		results[i] = new int[subset_size];
	}

	int results_counter = 0;

	find_numerical_subsets_helper(num_sol, results, results_counter, current_solution, max_num, subset_size, 0, 0);

	delete[] current_solution;

	return results;
}

string to_str(int i) {
	stringstream out;
	out << i;
	return out.str();
}

int main() {
	//n is the number of people
	int n;
	cin >> n;

	//r is the number of rows in the table
	int r = pow(2, n);

	//Num is all of the possible sayings that can be said about 2 people
	int num_sayings = 2*n + choose(n, 2) * 10;

	//Meanings contains what each of the rows mean in the table
	string meanings[num_sayings];

	//Setup the single values for the table, A, B, etc.
	for (int i = 0; i < n; i++) {
		meanings[i] = "a " + to_str(i);
	}

	//now for the not singles ~A, ~B, etc.
	for (int i = 0; i < n; i++) {
		meanings[i + n] = "b " + to_str(i);
	}

	//now for the binary operations
	int count = 0;
	int nchoose2 = choose(n, 2);
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			for (int opnum = 2; opnum <= 11; opnum++) {
				meanings[count + 2*n + (opnum - 2)*nchoose2] = get_op(opnum) + " " + to_str(i) + " " + to_str(j);
			}
			count++;
		}
	}

	//Values is a matix of truth values for every possible saying
	bool values[num_sayings][r];

	//This var will be used to keep track of how many columns have been filled so far
	int column = 0;

	//Setup the single values for the table, A, B, etc.
	int switch_counter = r/2;
	int counter;
	bool val = true;
	for (int i = 0; i < n; i++) {
		counter = 1;
		for (int j = 0; j < r; j++) {
			values[i][j] = val;

			if (counter == switch_counter) {
				val = !val;
				counter = 0;
			}
			counter++;
		}
		val = true;
		switch_counter /= 2;
	}

	column = n;

	//now for the not singles ~A, ~B, etc.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < r; j++) {
			values[i + column][j] = !values[i][j];
		}
	}
	
	column += n;

	//now for each of the binary operators
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			for (int k = 0; k < r; k++) {
				//A ^ B
				values[column][k] = values[i][k] && values[j][k];
				//A ^ ~B
				values[column + nchoose2][k] = values[i][k] && !values[j][k];
				//~A ^ B
				values[column + 2*nchoose2][k] = !values[i][k] && values[j][k];
				//~A ^ ~B
				values[column + 3*nchoose2][k] = !values[i][k] && !values[j][k];
				//A v B
				values[column + 4*nchoose2][k] = values[i][k] || values[j][k];
				//A v ~B
				values[column + 5*nchoose2][k] = values[i][k] || !values[j][k];
				//~A v B
				values[column + 6*nchoose2][k] = !values[i][k] || values[j][k];
				//~A v ~B
				values[column + 7*nchoose2][k] = !values[i][k] || !values[j][k];
				//A <-> B
				values[column + 8*nchoose2][k] = (values[i][k] && values[j][k]) || (!values[i][k] && !values[j][k]);
				//~(A <-> B)
				values[column + 9*nchoose2][k] = (values[i][k] && !values[j][k]) || (!values[i][k] && values[j][k]);
			}
			column++;
		}
	}

	/*
	//This is for checking the calculated truth table and their meanings
	cout << "The number of operator sequences is " << num_sayings << endl;
	cout << "The number of rows is " << r << endl;
	cout << "n choose 2 is " << nchoose2 << endl;
	
	for (int i = 0; i < num_sayings; i++) {
		for (int j = 0; j < r; j++) {
			cout << values[i][j] << " ";
		}
		cout << "Meaning:" << meanings[i] << endl;
	}
	*/
	

	//Now that we have generated the table, we need to run through combinations of what people say in order to find
	//	groups that only have one solution

	//First we will generate the possible combinations of n sayings
	int** possible_sayings = find_numerical_subsets(num_sayings, n);

	vector<string> actual_solutions;
	string actual_solutions_solution;

	//We now have a list of all (num_sayings choose n) ways for n people to say something
	//From here we find each permutation (each person can say something different) for each grouping and check these values against the table
	//In order to find grouping that yield only one correct solution
	int num_sol = choose(num_sayings, n);
	//For each group of sayings
	for (int i = 0; i < num_sol; i++) {
		sort(possible_sayings[i], possible_sayings[i]+n);

		//For every permutation of that grouping
		do {

			count = 0;
			//Test each row to check for accuracy
			for (int j = 0; j < r; j++) {
				//We look at each of the n values in the possible solution
				bool all_same = true;
				for (int k = 0; k < n; k++) {
					if (values[k][j] != values[possible_sayings[i][k]][j]) {
						all_same = false;
					}
				}

				if (all_same == true) {
					count++;
					if (count == 1) {
						actual_solutions_solution = "";
						for (int k = 0; k < n; k++) {
							actual_solutions_solution += to_str(k) + " = " + to_str(values[k][j]) + "\n";
						}
					}
				}
			}

			//If there was only one row in the table that was true for all of the n, then we have a solution
			if (count == 1) {
				string solution = "";
				for (int j = 0; j < n; j++) {
					solution += to_str(j) + " - " + meanings[possible_sayings[i][j]] + "\n";
				} 
				solution += actual_solutions_solution;
				actual_solutions.push_back(solution);
			}

		} while (next_permutation(possible_sayings[i], possible_sayings[i]+n));
	}

	//This is for printing out solutions
	for (int i = 0; i < actual_solutions.size(); i++) {
		cout << actual_solutions[i] << endl;
	}	

	for (int i = 0; i < choose(num_sayings, n); i++) {
		delete[] possible_sayings[i];
	}
	delete[] possible_sayings;
}