# Hotel Redemption Reconciliation Tool

A C++ command-line prototype that simulates a hotel night audit redemption reconciliation workflow.

This tool reads redemption transaction data from a text/CSV-style file, applies adjustment rules, and displays posting instructions needed to bring promo folio balances to zero.

## Version

v1.1 — CLI Adjustment Visualizer

## Purpose

During hotel night audit, promo/redemption folios may need to be manually adjusted to a zero balance. This project simulates that workflow by generating posting instructions from transaction data.

This project uses fake sample data only and does not connect to any real hotel/property management system.

## Features

- Reads transaction data from `redemptions.txt`
- Parses portfolio, department, subdepartment, description, amount, reference, and adjusted status
- Applies adjustment logic:
  - Positive amount → use original subdepartment + 50
  - Negative amount → use original subdepartment
- Calculates before balance, post adjustment amount, and after balance
- Displays whether each transaction is zeroed out
- Outputs clear posting instructions in the terminal

## Adjustment Rules

### Positive Amount

Example:

```text
Original:
Dept: 7
Subdept: 1
Amount: 18.75

Posting:
Dept: 7
Subdept: 51
Amount: 18.75
