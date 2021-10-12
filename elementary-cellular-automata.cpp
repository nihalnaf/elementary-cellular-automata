#include <iostream>

#include <string>

using std::cout;
using std::cin;
using std::endl;

using std::string;
using std::to_string;

//function that calculates and returns integer sum of each element in CA line
int get_line_sum(const string & row) {
  int line_sum = 0; //initialize line_sum to be 0
  for (char chr: row) {
    line_sum += static_cast < int > (chr) - 48; //add ASCII value of each character in line - 48 to subtract ASCII value of 0
  }
  return line_sum;
}

//function that calculates and returns the next state of a neighborhood given the rules
char get_next_state(const string & neighborhood,
  const string & rules) {
  char result = '0'; //initialize the result to be '0' so next state is 0 if rule is not defined
  for (unsigned long i = 0; i < rules.length(); i += 9) {
    string temp_rule = rules.substr(i, 3); //initialize a temp_rule variable to be a substring of the rule on the left side
    if (temp_rule == neighborhood) {
      result = rules[i + 7]; //if rule substring is same as neighborhood set the result to be the number on the right side of the rule
    }
  }
  return result;
}

//function that updates the actual CA line
void update_line(string & row,
  const string & rules) {
  string row_copy = row; //make a copy of the line so we can perform CA with respect to original line rather than the altered one
  for (unsigned long i = 0; i < row.length(); i++) {
    string neighborhood;
    if (i == 0) {
      neighborhood = to_string(row_copy[row.length() - 1] - 48) +
        to_string(row_copy[i] - 48) + to_string(row_copy[i + 1] - 48); //special case for the first neighborhood
    } else if (i == row.length() - 1) {
      neighborhood = to_string(row_copy[i - 1] - 48) +
        to_string(row_copy[i] - 48) + to_string(row_copy[0] - 48); //special case for the last neighborhood
    } else {
      neighborhood = to_string(row_copy[i - 1] - 48) +
        to_string(row_copy[i] - 48) + to_string(row_copy[i + 1] - 48); //every other case
    }
    row[i] = get_next_state(neighborhood, rules); //change the state
  }
}

//function to run cellular automata for a certain set of rules, iterations, and starting line
string run_cellular_automata(const string & rules,
  const int & iterations, string & row) {
  string result;
  for (int i = 0; i < iterations; i++) {
    result += row + " sum = " + to_string(get_line_sum(row)) + "\n"; //print line and sum
    update_line(row, rules); //update the line
  }
  return result;
}

int main() {
  string rules;
  string input;

  cout << "Enter rules in this format: 000 -> 0" << endl;
  cout << "Replace the 0's with the numbers in the rule" << endl;
  cout << "Enter each rule on a new line, and when finished, enter a '.' on its own line" << endl;
  while (getline(cin, input)) {
    if (input == ".") { //collect input lines until user enters a '.' on its own line
      break;
    }
    rules += input + "\n";
  }

  int iterations;
  cout <<  "Enter iterations: " << endl;
  cin >> iterations; //collect input for iterations
  iterations = static_cast < int > (iterations);

  string row;
  getline(cin, row);
  cout << "Enter the starting line: " << endl;
  getline(cin, row); //second getline because the first one reads the new line after cin for iterations

  cout << run_cellular_automata(rules, iterations, row); //print result of running CA
  return 0;
}
