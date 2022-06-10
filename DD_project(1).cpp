/*
Contributor: Sara Mohamed 900203032
Course: AUC // CSCE 2301-01
Date Started: 21/3/2022
Date Finished: 25/3/2022
Description: Karnaugh Map Function Calculator (<=3)

This is an individual project.
*/

#include <iostream>
#include <vector>
using namespace std;

struct cell
{
	string binrepresentation;           // binary representation of cell
	int decrepresentation;              // decimal representation of cell
	int value;                          // value, either 0 or 1

	bool operator==(cell a)
	{
		if (decrepresentation == a.decrepresentation)
			return true;
		return false;
	}
};

struct mterm
{
	vector<cell> minterm;               // vector of cells included in minterm
	int type;                           // type of minterm, see report for more detail
};

vector<vector<cell>>KMap;               // vector of vectors of cells, KMap
vector<mterm> MinTerms;                 // vector of mterms containing initially acquired minterms
vector<mterm> FilteredTerms;            // vector of mterms containing filtered minterms, used in function printing methods

void filterDuplicates();
void inputMap1();
void displayMap1();
void printFunction1();
void inputMap2();
void displayMap2();
void calcAllMinterms2();
void printFunction2();
void inputMap3();
void displayMap3();
void calcAllMinterms3();
void printFunction3();

int main()
{
    cout << endl << "This program calculates the simplified boolean function using Karnaugh Maps of one, two and three variables." << endl << endl;

	int input;

	cout << "Enter desired number of variables in K-Map: ";
	cin >> input;
	cout << endl;

	while (input > 3 || input < 1)
	{
		cout << "Invalid number of variables. Please try again: ";
		cin >> input;
	}

	if (input == 1)
		inputMap1();
	else if (input == 2)
		inputMap2();
	else if (input == 3)
		inputMap3();

	return 0;
}

void inputMap1()
{
    KMap.push_back({ {"0", 0, 0} });
    KMap.push_back({ {"1", 1, 0} });    // intializing KMap based on one variable

    int n;
    cout << "Enter number of minterms: ";
    cin >> n;

    while (n < 1 || n > 2)              // range of number of minterms for one variable
    {
        cout << "Invalid number of minterms for selected number of variables. Please try again: ";
        cin >> n;
        cout << endl;
    }

    cout << endl;

    cout << "Enter minterms: ";
    int temp;
    for (int i = 1; i <= n; i++)
    {
        cin >> temp;

        while (temp > 1 || temp < 0)
        {
            cout << temp << " is an invalid minterm. Please try again: ";
            cin >> temp;
            cout << endl;
        }

        if (temp == 0)
            KMap[0][0].value = 1;
        else if (temp == 1)
            KMap[1][0].value = 1;
    }

    cout << endl << endl;

    displayMap1();
}

void displayMap1()
{
    cout << "KMap: " << endl;

    cout << "\t" << KMap[0][0].value << endl << "\t" << KMap[1][0].value << endl;

    printFunction1();
}

void printFunction1()
{
    cout << "F = ";

    if (KMap[0][0].value == 1 && KMap[1][0].value == 1)
    {
        cout << "1";
    }
    else if (KMap[0][0].value == 1)
    {
        cout << "A'";
    }
    else
    {
        cout << "A";
    }
}

void inputMap2()
{
    KMap.push_back({ {"00", 0, 0}, {"01", 1, 0} });
    KMap.push_back({ {"10", 2, 0}, {"11", 3, 0} }); // initializing KMap based on two variables

    int n;
    cout << "Enter number of minterms: ";
    cin >> n;
    cout << endl;

    while (n < 1 || n > 4)              // range of number of minterms available based on two variables
    {
        cout << "Invalid number of minterms for selected number of variables. Please try again: ";
        cin >> n;
        cout << endl;
    }

    cout << "Enter minterms: ";
    int temp;
    for (int i = 1; i <= n; i++)
    {
        cin >> temp;

        while (temp > 3 || temp < 0)
        {
            cout << temp <<" is an invalid minterm. Please try again: ";
            cin >> temp;
            cout << endl;
        }

        if (temp == 0)
            KMap[0][0].value = 1;
        else if (temp == 1)
            KMap[0][1].value = 1;
        else if (temp == 2)
            KMap[1][0].value = 1;
        else if (temp == 3)
            KMap[1][1].value = 1;
    }

    cout << endl << endl;

    displayMap2();

}

void displayMap2()
{
    cout << "KMap: " << endl;

    for (int i = 0; i < 2; i++)
    {
        cout << "\t";
        for (int j = 0; j < 2; j++)
        {
            cout << KMap[i][j].value << "   ";
        }
        cout << endl;
    }

    calcAllMinterms2();
}

void calcAllMinterms2()
{
    int c5 = 0;                         // counter for minterms of type 5 - largest grouping for 2 variable KMap
    int c = 0;                          // counter for minterms in general
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (KMap[i][j].value == 1)  // looping over value 1 cells in KMap
            {
                if ((c5 == 0) && KMap[i][(j + 1) % 2].value == 1 && KMap[(i + 1) % 2][j].value == 1 && KMap[(i + 1) % 2][(j + 1) % 2].value == 1)
                {                       // checking if no type 5 minterm previously found, and that all cells in KMap are 1s

                    MinTerms.push_back({ { KMap[i][j], KMap[i][(j + 1) % 2], KMap[(i + 1) % 2][j], KMap[(i + 1) % 2][(j + 1) % 2] }, 5 });
                    c5++;
                    c++;
                }      
                else                    // if no type 5 minterm found
                {
                    if (KMap[i][(j + 1) % 2].value == 1)
                    {
                        MinTerms.push_back({ { KMap[i][j], KMap[i][(j + 1) % 2] }, 3 });
                        c++;
                    }
                    if (KMap[(i + 1) % 2][j].value == 1)
                    {
                        MinTerms.push_back({ { KMap[i][j], KMap[(i + 1) % 2][j] }, 2 });
                        c++;
                    }
                    if (c == 0)
                    {
                        if (KMap[(i + 1) % 2][j].value == 0 && KMap[i][(j + 1) % 2].value == 0)
                            MinTerms.push_back({ {KMap[i][j]}, 1 });
                    }
                }
            }
        }
    }

    filterDuplicates();
    printFunction2();
}

void printFunction2()
{
    /*
    function manually prints out expressions in function based on
    the type of minterm and the cells in the minterm - no calculation required
    */

    cout << endl << endl << "F = ";
    for (int i = 0; i < FilteredTerms.size(); i++)
    {
        mterm temp = FilteredTerms[i];
        vector<cell> mtemp = FilteredTerms[i].minterm;

        if (temp.type == 5)
        {
            cout << "1";
        }
        else if (temp.type == 3)
        {
            if ((find(mtemp.begin(), mtemp.end(), KMap[0][0]) != mtemp.end()) && (find(mtemp.begin(), mtemp.end(), KMap[0][1]) != mtemp.end()))
                cout << "A' ";
            else if ((find(mtemp.begin(), mtemp.end(), KMap[1][0]) != mtemp.end()) && (find(mtemp.begin(), mtemp.end(), KMap[1][1]) != mtemp.end()))
                cout << "A ";
        }
        else if (temp.type == 2)
        {
            if (find(mtemp.begin(), mtemp.end(), KMap[0][0]) != mtemp.end())
                cout << "B' ";
            if (find(mtemp.begin(), mtemp.end(), KMap[0][1]) != mtemp.end())
                cout << "B";
        }
        else if (temp.type == 1)
        {
            if (find(mtemp.begin(), mtemp.end(), KMap[0][0]) != mtemp.end())
                cout << "A'B' ";
            else if (find(mtemp.begin(), mtemp.end(), KMap[0][1]) != mtemp.end())
                cout << "A'B ";
            else if (find(mtemp.begin(), mtemp.end(), KMap[1][0]) != mtemp.end())
                cout << "AB' ";
            else if (find(mtemp.begin(), mtemp.end(), KMap[1][1]) != mtemp.end())
                cout << "AB ";
        }

        if (i != (FilteredTerms.size() - 1))
            cout << "+ ";

    }
}

void inputMap3()
{
    KMap.push_back({ {"000", 0, 0}, { "001", 1, 0 }, { "011", 3, 0 }, { "010", 2, 0 } });
    KMap.push_back({ {"100", 4, 0}, {"101", 5, 0}, {"111", 7, 0}, {"110", 6, 0} });  // intiializing KMap based on 3 variables

    int n;
    cout << "Enter number of minterms: ";
    cin >> n;
    cout << endl;

    while (n < 1 || n > 8)                  // range of allowed number of minterms based on 3 variables
    {
        cout << "Invalid number of minterms for selected number of variables. Please try again: ";
        cin >> n;
        cout << endl;
    }

    cout << "Enter minterms: ";
    int temp;
    for (int i = 1; i <= n; i++)
    {
        cin >> temp;

        while (temp > 7 || temp < 0)        // range of allowed minterms based on three variables
        {
            cout << temp << " is an invalid minterm. Please try again: ";
            cin >> temp;
            cout << endl;
        }

        if (temp == 0)
            KMap[0][0].value = 1;
        else if (temp == 1)
            KMap[0][1].value = 1;
        else if (temp == 2)
            KMap[0][3].value = 1;
        else if (temp == 3)
            KMap[0][2].value = 1;
        else if (temp == 4)
            KMap[1][0].value = 1;
        else if (temp == 5)
            KMap[1][1].value = 1;
        else if (temp == 6)
            KMap[1][3].value = 1;
        else if (temp == 7)
            KMap[1][2].value = 1;
    }

    cout << endl << endl;

    displayMap3();
}

void displayMap3()
{
    cout << "KMap: " << endl;

    for (int i = 0; i < 2; i++)
    {
        cout << "\t";
        for (int j = 0; j < 4; j++)
        {
            cout << KMap[i][j].value << "   ";
        }
        cout << endl;
    }

    calcAllMinterms3();
}

void calcAllMinterms3()
{
    int c6 = 0; int c41 = 0;                // counter of minterms of type 6, and of type 4 for entire map
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int c(0), c5(0), c4(0);         // counter of minterms of all types, of type 5, and of type 4 for this particular loop; respectively
            if (KMap[i][j].value == 1)
            {
                if ((c6 == 0) && KMap[0][0].value == 1 && KMap[0][1].value == 1 && KMap[0][2].value == 1 && KMap[0][3].value == 1 &&
                    KMap[1][0].value == 1 && KMap[1][1].value == 1 && KMap[1][2].value == 1 && KMap[1][3].value == 1)
                {
                    MinTerms.push_back({ { KMap[0][0], KMap[0][1], KMap[0][2], KMap[0][3], KMap[1][0], KMap[1][1], KMap[1][2], KMap[1][3] }, 6 });
                    c6++;
                }
                else
                {
                    if (KMap[i][(j + 1) % 4].value == 1 && KMap[(i + 1) % 2][j].value == 1 && KMap[(i + 1) % 2][(j + 1) % 4].value == 1)
                    {
                        MinTerms.push_back({ { KMap[i][j], KMap[i][(j + 1) % 4], KMap[(i + 1) % 2][j], KMap[(i + 1) % 2][(j + 1) % 4] }, 5 });
                        c5++;
                        c++;
                    }
                    if (KMap[i][(j + 1) % 4].value == 1 && KMap[i][(j + 2) % 4].value == 1 && KMap[i][(j + 3) % 4].value == 1 &&
                        KMap[i][(j + 4) % 4].value == 1)
                    {
                        if (c41 == 0)                   // this is because there cannot be more than 1 minterm of type 4, since that would mean the whole
                                                        // map is of value 1, which is a minterm of type 6
                        {
                            MinTerms.push_back({ { KMap[i][j], KMap[i][(j + 1) % 4], KMap[i][(j + 2) % 4], KMap[i][(j + 3) % 4]}, 4 });
                        }
                        c4++;
                        c41++;
                        c++;
                    }
                    if (c5 == 0)
                    {
                        if ((c4 == 0) && KMap[i][(j + 1) % 4].value == 1)
                        {
                            MinTerms.push_back({ { KMap[i][j], KMap[i][(j + 1) % 4] }, 3 });
                            c++;
                        }
                        if (KMap[(i + 1) % 2][j].value == 1)
                        {
                            MinTerms.push_back({ { KMap[i][j], KMap[(i + 1) % 2][j] }, 2 });
                            c++;
                        }
                        if (c == 0)
                        {
                            if (KMap[(i + 1) % 2][j].value == 0 && KMap[i][(j + 1) % 4].value == 0)
                                MinTerms.push_back({ {KMap[i][j]}, 1 });
                        }
                    }
                }
            }
        }
    }

    filterDuplicates();
    printFunction3();
}

void printFunction3()
{
    /*
    function manually prints out expressions in function based on
    the type of minterm and the cells in the minterm - no calculation required
    */

    cout << endl << "F = ";
    for (int i = 0; i < FilteredTerms.size(); i++)
    {
        mterm temp = FilteredTerms[i];
        vector<cell> mtemp = FilteredTerms[i].minterm;

        if (temp.type == 6)
        {
            cout << "1";
            return;
        }
        else if (temp.type == 5)
        {
            if ((find(mtemp.begin(), mtemp.end(), KMap[0][0]) != mtemp.end()) && (find(mtemp.begin(), mtemp.end(), KMap[0][1]) != mtemp.end()))
                cout << "B' ";
            else if ((find(mtemp.begin(), mtemp.end(), KMap[0][1]) != mtemp.end()) && (find(mtemp.begin(), mtemp.end(), KMap[0][2]) != mtemp.end()))
                cout << "C ";
            else if ((find(mtemp.begin(), mtemp.end(), KMap[0][2]) != mtemp.end()) && (find(mtemp.begin(), mtemp.end(), KMap[0][3]) != mtemp.end()))
                cout << "B ";
            else
                cout << "C' ";
        }
        else if (temp.type == 4)
        {
            if (find(mtemp.begin(), mtemp.end(), KMap[0][0]) != mtemp.end())
                cout << "A' ";
            else
                cout << "A ";
        }
        else if (temp.type == 3)
        {
            if ((find(mtemp.begin(), mtemp.end(), KMap[0][0]) != mtemp.end()) && (find(mtemp.begin(), mtemp.end(), KMap[0][1]) != mtemp.end()))
                cout << "A'B' ";
            else if ((find(mtemp.begin(), mtemp.end(), KMap[0][1]) != mtemp.end()) && (find(mtemp.begin(), mtemp.end(), KMap[0][2]) != mtemp.end()))
                cout << "A'C ";
            else if ((find(mtemp.begin(), mtemp.end(), KMap[0][2]) != mtemp.end()) && (find(mtemp.begin(), mtemp.end(), KMap[0][3]) != mtemp.end()))
                cout << "A'B ";
            else if ((find(mtemp.begin(), mtemp.end(), KMap[0][3]) != mtemp.end()) && (find(mtemp.begin(), mtemp.end(), KMap[0][0]) != mtemp.end()))
                cout << "A'C' ";
            else if ((find(mtemp.begin(), mtemp.end(), KMap[1][0]) != mtemp.end()) && (find(mtemp.begin(), mtemp.end(), KMap[1][1]) != mtemp.end()))
                cout << "AB' ";
            else if ((find(mtemp.begin(), mtemp.end(), KMap[1][1]) != mtemp.end()) && (find(mtemp.begin(), mtemp.end(), KMap[1][2]) != mtemp.end()))
                cout << "AC ";
            else if ((find(mtemp.begin(), mtemp.end(), KMap[1][2]) != mtemp.end()) && (find(mtemp.begin(), mtemp.end(), KMap[1][3]) != mtemp.end()))
                cout << "AB ";
            else if ((find(mtemp.begin(), mtemp.end(), KMap[1][3]) != mtemp.end()) && (find(mtemp.begin(), mtemp.end(), KMap[1][0]) != mtemp.end()))
                cout << "AC' ";
        }
        else if (temp.type == 2)
        {
            if (find(mtemp.begin(), mtemp.end(), KMap[0][0]) != mtemp.end())
                cout << "B'C' ";
            if (find(mtemp.begin(), mtemp.end(), KMap[0][1]) != mtemp.end())
                cout << "B'C ";
            if (find(mtemp.begin(), mtemp.end(), KMap[0][2]) != mtemp.end())
                cout << "BC ";
            if (find(mtemp.begin(), mtemp.end(), KMap[0][3]) != mtemp.end())
                cout << "BC' ";
        }
        else if (temp.type == 1)
        {
            if (find(mtemp.begin(), mtemp.end(), KMap[0][0]) != mtemp.end())
                cout << "A'B'C' ";
            else if (find(mtemp.begin(), mtemp.end(), KMap[0][1]) != mtemp.end())
                cout << "A'B'C ";
            else if (find(mtemp.begin(), mtemp.end(), KMap[0][2]) != mtemp.end())
                cout << "A'BC ";
            else if (find(mtemp.begin(), mtemp.end(), KMap[0][3]) != mtemp.end())
                cout << "A'BC' ";
            else if (find(mtemp.begin(), mtemp.end(), KMap[1][0]) != mtemp.end())
                cout << "AB'C' ";
            else if (find(mtemp.begin(), mtemp.end(), KMap[1][1]) != mtemp.end())
                cout << "AB'C ";
            else if (find(mtemp.begin(), mtemp.end(), KMap[1][2]) != mtemp.end())
                cout << "ABC ";
            else if (find(mtemp.begin(), mtemp.end(), KMap[1][3]) != mtemp.end())
                cout << "ABC' ";
        }

        if (i != (FilteredTerms.size() - 1))
            cout << "+ ";

    }
}

void filterDuplicates()
{
    vector<bool> exclude(MinTerms.size(), false);       // vector of bools of size equal to the size of Minterms, each index corresponds to index in Minterms
    for (int i = 0; i < MinTerms.size(); i++)
    {
        mterm temp = MinTerms[i];
        vector<bool> same(temp.minterm.size(), false);  //vector of bools of size equal to number of cells in minterm temp
        int c = 0;

        for (int k = 0; k < temp.minterm.size(); k++)
        {                                               // looping through each cell in temp
            for (int j = 0; j < MinTerms.size(); j++)
            {                                           // looping through all minterms in Minterms
                if ((j != i) && (!exclude[i]) && (!exclude[j]))
                {
                    for (int l = 0; l < MinTerms[j].minterm.size(); l++)
                    {                                   // looping through each cell in each minterm in Minterms
                        if (((temp.type <= MinTerms[j].type) || ((temp.type == 3 && MinTerms[j].type == 2) || (temp.type == 2 && MinTerms[j].type == 3))) && temp.minterm[k] == MinTerms[j].minterm[l])
                            same[k] = true;
                    }
                }
            }
        }

        for (bool x : same)
        {
            if (x == true)
                c++;
        }

        if (c < same.size())                        // if not all cells in temp are present in other minterms
            FilteredTerms.push_back({ temp.minterm, temp.type });
        else                                        // if all cells in temp are present in other minterms, exclude temp from further comparisons
            exclude[i] = true;
    }
}