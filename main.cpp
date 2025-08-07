#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

struct Service {
    string description;
    double rate;
    int quantity;
};

int main() {
    string influencerName, clientName, clientEmail;
    int numServices;
    double taxRate;

    cout << "===== Customer Invoice Generator =====\n";

    cout << "Enter your name (Influencer): ";
    getline(cin, influencerName);

    cout << "Enter client/brand name: ";
    getline(cin, clientName);

    cout << "Enter client email: ";
    getline(cin, clientEmail);

    do {
        cout << "Enter number of services provided: ";
        cin >> numServices;
        if (numServices <= 0) {
            cout << "❌ Please enter at least one service.\n";
        }
    } while (numServices <= 0);

    vector<Service> services(numServices);

    for (int i = 0; i < numServices; ++i) {
        cin.ignore();
        cout << "\nService #" << i + 1 << " description: ";
        getline(cin, services[i].description);

        do {
            cout << "Rate for this service: $";
            cin >> services[i].rate;
            if (services[i].rate <= 0) {
                cout << "❌ Rate must be greater than $0. Please enter again.\n";
            }
        } while (services[i].rate <= 0);

        do {
            cout << "Quantity: ";
            cin >> services[i].quantity;
            if (services[i].quantity <= 0) {
                cout << "❌ Quantity must be greater than 0. Please enter again.\n";
            }
        } while (services[i].quantity <= 0);
    }

    do {
        cout << "\nEnter tax rate (e.g., 8.5 for 8.5%): ";
        cin >> taxRate;
        if (taxRate < 0) {
            cout << "❌ Tax rate cannot be negative. Please enter again.\n";
        }
    } while (taxRate < 0);

    double subtotal = 0;
    for (const auto& service : services) {
        subtotal += service.rate * service.quantity;
    }

    double taxAmount = subtotal * (taxRate / 100);
    double total = subtotal + taxAmount;

    time_t now = time(0);
    tm* localTime = localtime(&now);
    int invoiceNumber = static_cast<int>(now);

    char dateStr[11];
    strftime(dateStr, sizeof(dateStr), "%m/%d/%Y", localTime);

    string filename = "invoice_" + clientName + "_" + to_string(invoiceNumber) + ".txt";
    ofstream outFile(filename);

    outFile << fixed << setprecision(2);
    outFile << "=========== INVOICE ===========" << endl;
    outFile << "Invoice #: " << invoiceNumber << endl;
    outFile << "Date: " << dateStr << endl;
    outFile << "-------------------------------" << endl;
    outFile << "Influencer: " << influencerName << endl;
    outFile << "Client: " << clientName << endl;
    outFile << "Email: " << clientEmail << endl;
    outFile << "-------------------------------" << endl;
    outFile << left << setw(25) << "Service" << setw(10) << "Rate" << setw(10) << "Qty" << "Total" << endl;

    for (const auto& service : services) {
        double totalLine = service.rate * service.quantity;
        outFile << left << setw(25) << service.description
                << "$" << setw(9) << service.rate
                << setw(10) << service.quantity
                << "$" << totalLine << endl;
    }

    outFile << "-------------------------------" << endl;
    outFile << "Subtotal: $" << subtotal << endl;
    outFile << "Tax (" << taxRate << "%): $" << taxAmount << endl;
    outFile << "Total Due: $" << total << endl;
    outFile << "===============================" << endl;

    outFile.close();

    cout << "\n✅ Invoice saved to file: " << filename << endl;
    cout << "Thank you for using the Customer Invoice Generator!\n";

    return 0;
}
