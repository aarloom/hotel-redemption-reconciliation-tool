#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <map>

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

struct Adjustment {
    string portfolio;
    int dept;
    int postSubdept;
    double amount;
    int reference;
    string ruleUsed;
};

int main()
{
    ifstream inFile("redemptions.txt");

    if (!inFile) {
        cout << "File failed to open." << endl;
        return 1;
    }

    vector<Redemption> redemptions;
    vector<Adjustment> adjustments;
    map<string, double> portfolioTotals;

    string line;

    while (getline(inFile, line)) {

        if (line.empty()) {
            continue;
        }

        stringstream ss(line);

        string portfolio, deptString, subdeptString, description;
        string amountString, referenceString, adjustedString;

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

        if (!r.adjusted) {
            portfolioTotals[r.portfolio] += r.amount;
        }
    }

    inFile.close();

    cout << fixed << setprecision(2);

    cout << "==========================================" << endl;
    cout << " HOTEL REDEMPTION RECONCILIATION REPORT" << endl;
    cout << "==========================================" << endl << endl;

    cout << "=== PORTFOLIO TOTALS BEFORE ADJUSTMENT ===" << endl;

    for (auto const& item : portfolioTotals) {
        cout << item.first << " Total: $" << item.second << endl;
    }

    cout << endl;
    cout << "=== GENERATED ADJUSTMENT POSTINGS ===" << endl << endl;

    for (int i = 0; i < redemptions.size(); i++) {

        if (redemptions[i].adjusted) {
            cout << "Portfolio: " << redemptions[i].portfolio << endl;
            cout << "Description: " << redemptions[i].description << endl;
            cout << "Reference: " << redemptions[i].reference << endl;
            cout << "Status: ALREADY ADJUSTED - SKIPPED" << endl;
            cout << "------------------------------------------" << endl;
            continue;
        }

        int postSubdept;
        double postAmount;
        double afterBalance;
        string ruleUsed;

        if (redemptions[i].amount < 0) {
            postSubdept = redemptions[i].subdept;
            postAmount = abs(redemptions[i].amount);
            afterBalance = redemptions[i].amount + postAmount;
            ruleUsed = "Negative amount -> use original subdept";
        }
        else {
            postSubdept = redemptions[i].subdept + 50;
            postAmount = redemptions[i].amount;
            afterBalance = redemptions[i].amount - postAmount;
            ruleUsed = "Positive amount -> use subdept + 50";
        }

        Adjustment a;
        a.portfolio = redemptions[i].portfolio;
        a.dept = redemptions[i].dept;
        a.postSubdept = postSubdept;
        a.amount = postAmount;
        a.reference = redemptions[i].reference;
        a.ruleUsed = ruleUsed;

        adjustments.push_back(a);

        cout << "Portfolio: " << redemptions[i].portfolio << endl;
        cout << "Description: " << redemptions[i].description << endl;
        cout << "Reference: " << redemptions[i].reference << endl;
        cout << endl;

        cout << "Original Transaction" << endl;
        cout << "Dept: " << redemptions[i].dept << endl;
        cout << "Subdept: " << redemptions[i].subdept << endl;
        cout << "Before Balance: $" << redemptions[i].amount << endl;
        cout << endl;

        cout << "Generated Adjustment" << endl;
        cout << "Dept: " << redemptions[i].dept << endl;
        cout << "Post Subdept: " << postSubdept << endl;
        cout << "Adjustment Amount: $" << postAmount << endl;
        cout << endl;

        cout << "After Balance: $" << afterBalance << endl;
        cout << "Rule Used: " << ruleUsed << endl;

        if (afterBalance == 0) {
            cout << "Status: ZEROED OUT" << endl;
        }
        else {
            cout << "Status: STILL OPEN" << endl;
        }

        cout << "------------------------------------------" << endl;
    }

    ofstream outFile("adjustments.csv");

    if (!outFile) {
        cout << "Failed to create adjustments.csv" << endl;
        return 1;
    }

    outFile << "portfolio,dept,post_subdept,amount,reference,rule_used\n";

    for (int i = 0; i < adjustments.size(); i++) {
        outFile << adjustments[i].portfolio << ","
                << adjustments[i].dept << ","
                << adjustments[i].postSubdept << ","
                << adjustments[i].amount << ","
                << adjustments[i].reference << ","
                << adjustments[i].ruleUsed << "\n";
    }

    outFile.close();

    cout << endl;
    cout << "==========================================" << endl;
    cout << "Adjustment file created: adjustments.csv" << endl;
    cout << "Total adjustments generated: " << adjustments.size() << endl;
    cout << "==========================================" << endl;

    return 0;
}