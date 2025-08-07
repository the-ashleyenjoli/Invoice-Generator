# Customer Invoice Generator (C++)

This C++ program generates an invoice for social media influencers working with clients or brands. It takes service details, performs tax and total calculations, and outputs a nicely formatted `.txt` invoice file.

## Features
- User input for influencer & client details
- Loop to collect multiple services
- Input validation for rates, quantities, and tax
- Calculations for subtotal, tax, and total
- Saves invoice to a text file with date and invoice number

## Requirements
- C++11 or later
- Command-line execution

## How to Run
```bash
g++ main.cpp -o invoice_generator
./invoice_generator
```

## Sample Output
A file like `invoice_BrandName_123456789.txt` is generated with a complete invoice breakdown.
