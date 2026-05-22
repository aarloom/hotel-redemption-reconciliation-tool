# Hotel Redemption Reconciliation Tool

A C++ command-line prototype that simulates hotel night audit redemption reconciliation workflows.

This project parses hotel promo/redemption folio transactions from a text-based dataset, applies reconciliation logic, and generates posting instructions used to zero out balances during night audit operations.

---

# Version

## v1.1 — CLI Adjustment Visualizer

---

# Project Purpose

In hotel night audit workflows, promotional folios and redemption accounts often require manual reconciliation before the business date can roll over.

This tool simulates that operational process by:

* reading folio redemption data,
* determining adjustment rules,
* calculating balancing postings,
* and visualizing the resulting reconciliation instructions.

The project uses entirely fake sample data and does not connect to any real property management system.

---

# Features

* Reads transaction data from `redemptions.txt`
* Parses:

  * portfolio
  * department
  * subdepartment
  * description
  * amount
  * reference number
  * adjusted status
* Applies custom reconciliation rules
* Calculates:

  * before balance
  * adjustment amount
  * after balance
* Displays generated posting instructions
* Identifies whether balances were successfully zeroed out
* Simulates hotel night audit promo folio workflows

---

# Adjustment Logic

## Positive Amount Rule

If the original amount is positive:

```text
Post Subdepartment = Original Subdepartment + 50
```

Example:

```text
Original:
Dept: 7
Subdept: 1
Amount: 245.50

Posting:
Dept: 7
Subdept: 51
Amount: 245.50
```

---

## Negative Amount Rule

If the original amount is negative:

```text
Post Subdepartment = Original Subdepartment
```

Example:

```text
Original:
Dept: 5
Subdept: 1
Amount: -84.25

Posting:
Dept: 5
Subdept: 1
Amount: 84.25
```

This simulates correction/reversal scenarios commonly encountered during hotel night audit reconciliation.

---

# Sample Input Format

Each row inside `redemptions.txt` follows this structure:

```csv
portfolio,dept,subdept,description,amount,reference,adjusted
```

Example:

```csv
9000 Promo F&B,7,1,PaloAlto Breakfast,245.50,81001,false
9001 Promo Sales,6,1,Gift Shop Retail,-96.40,82004,false
```

---

# How to Compile

## Linux / macOS

```bash
g++ main.cpp -o redemption_tool
```

Run:

```bash
./redemption_tool
```

---

## Windows

```bash
g++ main.cpp -o redemption_tool.exe
```

Run:

```bash
redemption_tool.exe
```

---

# Example Output

```text
Portfolio: 9000 Promo F&B
Description: PaloAlto Breakfast
Reference: 81001

Before: $245.50
Post Adjustment: $245.50
After: $0.00

Dept: 7
Original Subdept: 1
Post Subdept: 51

Rule Used: Positive amount -> use subdept + 50

Status: ZEROED OUT
```

---

# Current Limitations

v1.1 is currently a command-line visualization prototype.

Current limitations:

* No GUI/frontend
* No live backend integration
* No database
* No real PMS connectivity
* No CSV/JSON exports yet
* No authentication system yet

---

# Planned Roadmap

## v1.2

* Portfolio grouping
* Skip already adjusted rows
* CSV export generation
* Cleaner reporting output

## v1.3

* JSON export support
* Audit log generation
* Agent/user tracking
* Search by reference number

## v2.0

* React frontend dashboard
* Simulated hotel PMS workflow
* Portfolio detail screens
* Auto-generate adjustment interface
* Backend/frontend integration

---

# Technologies Used

* C++
* File I/O
* String parsing
* Vector data structures
* Terminal-based visualization

---

# Why I Built This

I currently work in hotel night audit operations and noticed repetitive reconciliation workflows involving promotional folios and manual balancing entries.

This project was built to:

* simulate real operational workflows,
* improve understanding of reconciliation logic,
* practice systems-oriented programming,
* and prototype a future dashboard-based reconciliation platform.

---

# Disclaimer

This project is for educational and portfolio purposes only.

It uses fake sample data and does not connect to, automate, or interact with any real hotel/property management software.
