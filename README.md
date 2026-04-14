A high-performance, terminal-based Stock Trading Simulator built with Modern C++. This project demonstrates Object-Oriented Programming (OOP) principles and stochastic market modeling.

## Features

- **Stochastic Market Engine**: Uses a **Gaussian Random Walk** model via `std::normal_distribution` to simulate realistic price movements based on current volatility.
- **Real-time Portfolio Tracking**: Efficient asset management using `std::map` to track holdings and calculate total equity (Net Worth) dynamically.
- **Trade Validation**: Built-in logic to prevent illegal trades (e.g., buying with insufficient funds or selling shares you don't own).
- **Modern C++ Architecture**: Utilizes C++17 features like **Structured Bindings** for clean and readable code.
- **Transaction History**: Tracks all "BOUGHT" and "SOLD" actions within a session log.

## Technical Logic

The simulator is built on three main logic pillars:
1. **The MarketEngine Class**: A static utility class that calculates the "next price tick" using a normal distribution (Mean 0, Standard Deviation = current_price * volatility).
2. **The Portfolio Class**: Manages state encapsulation, ensuring that the user's cash balance and asset map cannot be modified without passing through validation checks.
3. **The Game Loop**: A standard CLI loop that updates the market state every time the user performs an action, simulating the passage of time.

## Requirements

- **C++ Standard**: C++17 or higher.
- **Compiler**: GCC 7+, Clang 5+, or MSVC 2017+.
- **Standard Library**: Uses `<vector>`, `<map>`, `<random>`, and `<iomanip>`.

## Compilation

To compile via terminal, ensure you use the C++17 flag:

```bash
# Using G++
g++ -std=c++17 main.cpp -o TradingSim

# Using Clang++
clang++ -std=c++17 main.cpp -o TradingSim
```
## Transaction History
- **Persistent Trade Ledger**: All transactions are now automatically saved to `trade_history.txt`.
- **Append Logic**: The simulator uses `std::ios::app` to ensure that new trades are added to your existing history rather than overwriting it.
- **Session Sync**: Local memory (RAM) is synced to disk upon exit, ensuring a low memory footprint.

## Technical Stack
- **Language**: C++17
- **Standard Library**: `<iostream>`, `<vector>`, `<map>`, `<random>`, `<fstream>`, `<iomanip>`, `ios`
- **Design Pattern**: Object-Oriented Programming (OOP) with Encapsulation.

## Compilation & Setup

This program requires **C++17** because it uses structured bindings.

How to Use
View Market: Check current prices for AAPL, NVDA, GOOG, MSFT, AMZN, META, NFLX, TSLA (more will come soon). 

Buy: Enter the stock index and the quantity. The system will check your balance.

Sell: Liquidate holdings at current market prices.

Market Tick: Every time you interact with the menu, the market prices fluctuate, simulating a live trading floor.

⚠️ NOTE: Created for educational purposes to demonstrate modern C++ design patterns. The Program may not represent real-time values of stocks.
A Virtual Market has been created in this program meaning that there will be fluctuations to the price that was initialized in the "market" Vector(line 111) which holds the keys of Stocks and its values.
Those values are based from the NASDAQ Stock Market during the time of April, 2026. So, changes in prices are expected. ⚠️
