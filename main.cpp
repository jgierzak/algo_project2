#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;



void calculate() {
	ifstream infile;
	ofstream outfile("output.txt");
	
	infile.open("input.txt");

	// can't find file
	if (!infile.is_open()) {
		cout << "Cannot open input.txt" << endl;
		return;
	}
	// file found; initialization of array begins
	if (infile.good()) {
		string junk;
		int numInstances;
		int instCtr;
		unsigned int numElements;

		int t;
		int sum;

		// time to start getting everything we need.


		infile >> numInstances;
		getline(infile, junk);
		cout << "Number of Instances: " << numInstances << endl;
		for (int instCtr = 0; instCtr < numInstances; instCtr++) {

			cout << "Instance Number: " << instCtr + 1 << endl;
			infile >> numElements;
			infile >> t;
			getline(infile, junk);

			// make the arrays!!!
			// and initializes map to -1; this marks boundaries
			// for subsequent operations to go more smoothly
			vector<int> orig(numElements);
			vector< vector<int> > map;
			map.resize(numElements, vector<int>(numElements, -1));

			// fill in the 1D array
			for (int a = 0; a < numElements; a++) {
				infile >> orig[a];
				//cout << orig[a] << " ";
			}
			getline(infile, junk);
			//cout << endl << endl;

			// create a 2D array of inequality scores
			// unfilled cells were set to -1
			for (int i = 0; i < numElements; i++) {
				int j = i;
				sum = 0;
				for (int a = i; a < j + 1; a++) {
					if (a == numElements) break;
					sum += orig[a];
				}
				while(sum <= t) {
					sum = 0;
					for (int a = i; a < j+1; a++) {
						if (a == numElements) break;
						sum += orig[a];
					}
					if (i == 0) {
						if (i == j) {
							map[i][j] = (t - orig[j]) * (t - orig[j]);
						}
						else {							
							map[i][j] = (t - sum)*(t - sum);
						}
					}
					else {
						
						int min;
						for (int u = 0; u < numElements; u++) {
							min = map[u][i - 1];
							if (min >= 0) break;
						}
						if (i == j) {
							for (int p = 0; p < i - 1; p++) {
								if ((map[p][i - 1] < min) && (map[p][i - 1] >= 0)) {
									min = map[p][i - 1];
								}								
							}
							map[i][j] = ((t - orig[j])*(t - orig[j])) + min;
						}
						else {
							
							for (int p = 0; p < i - 1; p++) {
								if ((map[p][i - 1] < min) && (map[p][i - 1] >= 0)) {
									min = map[p][i - 1];
								}
							}
							map[i][j] = ((t - sum)*(t - sum)) + min;
						}						
					}
					j++;
					sum = 0;
					
					for (int a = i; a < j+1; a++) {
						if (a == numElements) break;
						sum += orig[a];
					}
					if ((j == numElements) || (sum > t)) break;
					
					
				}
			}

			/*for (int w = 0; w < numElements; w++) {
				cout << map[w][w] << " ";
			}
			cout << endl;*/

			// and for the rest...
			int j = numElements - 1;
			int k = 0;
			int last = numElements - 1;
			vector<int> partitions;
			
			
			// partitioning loop
			do {
				int vmin = map[j][j];
				k = j;
				for (int i = j; i >= 0; i--) {
					if (map[i][j] < 0) {
						break;
					}
					else if(map[i][j] < vmin){
						vmin = map[i][j];
						k = i;
					}
				}
				int i = k;				
				partitions.push_back( (last - i) + 1);
				last = i - 1;
				j = i - 1;

				

				if (j < 0) break;
				
			} while (j >= 0);
			for (int s = 0; s < partitions.size(); s++) {
				outfile << partitions[s] << " ";
			}			
			outfile << '\n';
			
			if (instCtr + 1 == numInstances) break;
		}

	}
	// if file contents are formatted incorrectly
	//if (!infile.eof()) {
	//	cout << endl << "Error reading file." << endl;
	//}

	// time to go!!!
	cout << "Computations complete.\n" << endl;
	infile.close();
	outfile.close();
}

int main() {
	cout << "Analysis of Algorithms" << endl;
	cout << "Project 2 - Dynamic Programming" << endl << endl;

	calculate();

	cout << "Goodbye! :D" << endl;

	cin.get();
	return 0;
}