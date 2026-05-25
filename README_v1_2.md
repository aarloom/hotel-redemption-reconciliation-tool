# Hotel Redemption Reconciliation Tool v1.2

A C++ console application that reads hotel redemption transactions from `redemptions.txt`, calculates the required adjustment postings, prints a reconciliation report, and exports the generated adjustments to `adjustments.csv`.

## What v1.2 Does

- Reads redemption records from a CSV-style text file
- Stores each record in a `Redemption` struct
- Tracks portfolio totals before adjustment
- Skips transactions already marked as adjusted
- Generates adjustment postings based on transaction amount
- Exports adjustment results into `adjustments.csv`

## Input File

The program expects a file named:

```txt
redemptions.txt
```

Each row should use this format:

```txt
portfolio,dept,subdept,description,amount,reference,adjusted
```

Example:

```txt
Rewards,101,10,Bonvoy points redemption,-125.50,900001,false
Rooms,201,21,Loyalty room credit,220.25,900004,false
Spa,401,40,Spa package redemption,-95.00,900007,true
```

## Adjustment Rules

| Transaction Type | Rule |
|---|---|
| Negative amount | Use original subdepartment and post the absolute value |
| Positive amount | Use original subdepartment + 50 and post the same amount |
| Already adjusted | Skip transaction |

## Output File

The program creates:

```txt
adjustments.csv
```

Output columns:

```txt
portfolio,dept,post_subdept,amount,reference,rule_used
```

## How To Run

Compile:

```bash
g++ main.cpp -o redemption_tool
```

Run:

```bash
./redemption_tool
```

On Windows PowerShell:

```powershell
g++ main.cpp -o redemption_tool.exe
./redemption_tool.exe
```

## Files Included

| File | Purpose |
|---|---|
| `main.cpp` | Main C++ source code |
| `redemptions.txt` | Sample input data |
| `adjustments.csv` | Generated output after running the program |
| `README.md` | Project documentation |

## Skills Demonstrated

- C++ structs
- File input/output
- CSV-style parsing
- Vectors
- Maps
- Conditional logic
- Report formatting
- Basic reconciliation logic
- Exporting generated data

## Future Improvements

- Add input validation for malformed rows
- Add a menu system
- Allow custom input/output filenames
- Add transaction search/filtering
- Add exception handling for `stoi` and `stod`
- Add unit tests
- Export summary totals to CSV
