#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct Redemption {
    string portfolio;
    int dept;
    int subdept;
    string description;
    double amount;
    int reference;
    bool adjusted;
};

int main()
{
    ifstream inFile("redemptions.txt");

    if (!inFile) {
        cout << "File failed to open." << endl;
        return 1;
    }

    vector<Redemption> redemptions;
    string line;

    while (getline(inFile, line)) {

        if (line.empty()) {
            continue;
        }

        stringstream ss(line);

        string portfolio;
        string deptString;
        string subdeptString;
        string description;
        string amountString;
        string referenceString;
        string adjustedString;

        getline(ss, portfolio, ',');
        getline(ss, deptString, ',');
        getline(ss, subdeptString, ',');
        getline(ss, description, ',');
        getline(ss, amountString, ',');
        getline(ss, referenceString, ',');
        getline(ss, adjustedString, ',');

        if (portfolio.empty() || deptString.empty() || subdeptString.empty() ||
            amountString.empty() || referenceString.empty()) {
            continue;
        }

        Redemption r;

        r.portfolio = portfolio;
        r.dept = stoi(deptString);
        r.subdept = stoi(subdeptString);
        r.description = description;
        r.amount = stod(amountString);
        r.reference = stoi(referenceString);
        r.adjusted = (adjustedString == "true");

        redemptions.push_back(r);
    }

    inFile.close();

    cout << fixed << setprecision(2);

    cout << "=== HOTEL REDEMPTION ADJUSTMENT VISUALIZER ===" << endl;
    cout << endl;

    for (int i = 0; i < redemptions.size(); i++) {

        int postSubdept;
        double postAmount;
        double afterBalance;

        if (redemptions[i].amount < 0) {
            postSubdept = redemptions[i].subdept;
            postAmount = abs(redemptions[i].amount);
            afterBalance = redemptions[i].amount + postAmount;
        }
        else {
            postSubdept = redemptions[i].subdept + 50;
            postAmount = redemptions[i].amount;
            afterBalance = redemptions[i].amount - postAmount;
        }

        cout << "Portfolio: " << redemptions[i].portfolio << endl;
        cout << "Description: " << redemptions[i].description << endl;
        cout << "Reference: " << redemptions[i].reference << endl;
        cout << endl;

        cout << "Before: $" << redemptions[i].amount << endl;
        cout << "Post Adjustment: $" << postAmount << endl;
        cout << "After: $" << afterBalance << endl;
        cout << endl;

        cout << "Dept: " << redemptions[i].dept << endl;
        cout << "Original Subdept: " << redemptions[i].subdept << endl;
        cout << "Post Subdept: " << postSubdept << endl;

        if (redemptions[i].amount < 0) {
            cout << "Rule Used: Negative amount -> use original subdept" << endl;
        }
        else {
            cout << "Rule Used: Positive amount -> use subdept + 50" << endl;
        }

        if (afterBalance == 0) {
            cout << "Status: ZEROED OUT" << endl;
        }
        else {
            cout << "Status: STILL OPEN" << endl;
        }

        cout << "--------------------------------------" << endl;
    }

    return 0;
}