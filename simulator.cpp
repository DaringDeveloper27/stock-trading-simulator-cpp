#include <ios>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <iomanip>
#include <fstream>
using namespace std;

// Random Price Generator
class MarketEngine {
    public:
        static double generateNextPrice(double currentPrice, double volatility = 0.02){
            static random_device rd;
            static mt19937 gen(rd()); // Mersenne Twister Algorithm 
            // Normal Distribution
            normal_distribution<> d(0, currentPrice * volatility);
            return currentPrice + d(gen);
        }
};

// Stock Assest
struct Stock {
    string symbol;
    double price;
};

// Portfolio Management
class Portfolio {
    private:
        double balance;
        map<string, int> holdings; // Symbol -> Quantity
        vector<string> tradeHistory;
    public:
        Portfolio(double initialCash) : balance(initialCash){}

        // Buy Stocks
        void buy(Stock& stock, int qty){
            double cost = stock.price * qty;
            if(balance >= cost){
                balance -= cost;
                holdings[stock.symbol] += qty;
                tradeHistory.push_back("BOUGHT " + to_string(qty) + " " + stock.symbol + " $" + to_string(stock.price));
                cout << "Successfully bought " << qty << " shares of " << stock.symbol << "\n";
            }
            else{
                cout << "Insufficient Funds" << "\n";
            }
        }

        // Sell Stocks
        void sell(Stock& stock, int qty){
            if(holdings[stock.symbol] >= qty){
                balance += stock.price * qty;
                holdings[stock.symbol] -= qty;
                tradeHistory.push_back("SOLD " + to_string(qty) + " " + stock.symbol + " $" + to_string(stock.price));
                cout << "Successfully sold " << qty << " shares of " << stock.symbol << "\n"; 
            }
            else{
                cout << "Not Enough Stocks to Sell" << "\n";
            }
        }

        // History Text File
        void saveHistoryToFile(const string& filename = "trade_history.txt") {
            ofstream outFile;
            outFile.open(filename, ios::app); 
        
            if (outFile.is_open()) {
                for (const auto& log : tradeHistory) {
                    outFile << log << endl;
                }
                tradeHistory.clear(); 
                outFile.close();
                cout << "History synced to disk.\n";
            } else {
                cerr << "Error: Could not open history file!" << endl;
            }
        }

        // Display Status
        void displayStatus(const vector<Stock>& market){
            double totalEquity = balance;
            cout << "\n--- Portfolio Status ---\n";
            cout << "Cash Balance: " << fixed << setprecision(2) << balance << "\n";
           
        for (auto const& item : holdings) {
            const std::string& symbol = item.first; 
            int qty = item.second;                

            if (qty > 0) {
                for (const auto& s : market) {
                    if (s.symbol == symbol) {
                        totalEquity += (qty * s.price);
                        std::cout << symbol << ": " << qty << " shares (Value: $" << (qty * s.price) << ")\n";
                    }
                }
            }
        }
            cout << "Total Net Worth: $" << totalEquity << "\n";
        }
};

int main(){
    // Welcome Message
    cout << endl;
    cout << "--- Welcome to the Stock Trading Simulator ---" << endl;
    // Initialization
    Portfolio myAccount(10000.0); // Start with $10,000
    vector<Stock> market = {{"AAPL", 250.0}, {"NVDA", 200.0}, {"GOOG", 300.0}, {"MSFT", 400.0}, {"AMZN", 250.0}, {"META", 660.0}, {"NFLX", 100.0}, {"TSLA", 360.0}};
    int choice = 0;
    while (choice != 6){
        cout << "\n1. View Market   2. Buy   3. Sell   4. View Portfolio   5. Save   6. Exit\n Choice: ";
        cin >> choice;

        // Every "turn", market prices fluctuate
        for(auto& s : market){
            s.price = MarketEngine::generateNextPrice(s.price);
        }
        
        if(choice == 1){
            cout << "\n--- Live Market ---\n";
            for(int x = 0; x < market.size(); ++x){
                cout << x << ". " << market[x].symbol << ": $" << market[x].price << "\n";
            }
        }

        else if(choice == 2 || choice == 3){
            int idx, qty;
            cout << "Enter Stock Index: ";
            cin >> idx;
            cout << "\nEnter Quantity: ";
            cin >> qty; 
            if(idx >= 0 && idx < market.size()){
                if(choice == 2) myAccount.buy(market[idx], qty);
                else myAccount.sell(market[idx], qty);
            }
        }

        else if(choice == 4){
            myAccount.displayStatus(market);
        }

        else if(choice == 5){
            myAccount.saveHistoryToFile();
            cout << "Saved" << "\n";
        }
    }
    return 0;
}