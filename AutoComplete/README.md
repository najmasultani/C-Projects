# Auto Complete System

This project implements a fast autocomplete functionality in C. The system retrieves the top terms matching a query string from a file containing terms and their associated weights.

## Objective

The goal is to quickly find and return the top matching terms based on a given query. The autocomplete functionality matches terms in a case-sensitive manner, only considering terms that start with the provided query string.

## Features

- **Efficient File Reading**: Reads terms from files like `cities.txt` and `wiktionary.txt`, sorting them lexicographically.
- **Binary Search**: Utilizes binary search to find matching terms efficiently.
- **Weight-based Sorting**: Extracts and sorts matching terms based on their weights.
- **Dynamic Memory Allocation**: Allocates memory for storing terms read from the files.

## Key Functions

### `void read_in_terms(term **terms, int *pnterms, char *filename);`
- **Description**: Reads terms from a file and stores them in a dynamically allocated array.
- **Input**: 
  - `terms`: Pointer to a pointer to `term` for storing the terms.
  - `pnterms`: Pointer to an integer for storing the number of terms.
  - `filename`: Name of the file containing the terms.
- **Output**: None (terms are stored in the provided pointer).

### `int lowest_match(term *terms, int nterms, char *substr);`
- **Description**: Returns the index of the first term that matches the query substring using binary search.
- **Input**:
  - `terms`: Array of terms.
  - `nterms`: Number of terms.
  - `substr`: Query substring.
- **Output**: Index of the first matching term.

### `int highest_match(term *terms, int nterms, char *substr);`
- **Description**: Returns the index of the last term that matches the query substring using binary search.
- **Input**:
  - `terms`: Array of terms.
  - `nterms`: Number of terms.
  - `substr`: Query substring.
- **Output**: Index of the last matching term.

### `void autocomplete(term **answer, int *n_answer, term *terms, int nterms, char *substr);`
- **Description**: Finds and stores the autocomplete matches for the given substring, sorted by weight in non-increasing order.
- **Input**:
  - `answer`: Pointer to an array to store matching terms.
  - `n_answer`: Pointer to an integer for storing the number of answers.
  - `terms`: Array of terms.
  - `nterms`: Number of terms.
  - `substr`: Query substring.
- **Output**: None (matches are stored in the provided pointer).

## Resources: 
This project was originally developed as part of the **ESC190: Data Structures and Algorithms course** assignment at the University of Toronto

## How to Run

### Clone the repository:

```bash
# Clone the repository
git clone https://github.com/najmasultani/C-Projects-General.git

# Navigate to the Auto Complete folder
cd C-Projects-General/AutoComplete

# Compile the project
gcc -Wall -std=99 autocomplete.c main.c -o autocomplete

# Run the program
./autocomplete

# Test the system with a terms file:
# Assuming you have a terms file named 'cities.txt' or 'wiktionary.txt'
# You would typically need to modify your code here, not run this in bash:
# In your C program, do something like this:

# Declare pointers and variables in your code
term *terms;  // Corrected from term **terms;
int nterms;
read_in_terms(&terms, &nterms, "cities.txt");

char *query = "Eng";
term *answer; // Declare this to hold the autocomplete results
int n_answer;
autocomplete(&answer, &n_answer, terms, nterms, query);


