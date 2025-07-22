# Chemical Formula Analyzer

A C program that processes and analyzes chemical formulas, calculating proton counts, expanding formula representations, and validating parentheses balance.

## Features

- **Proton Calculation** (`-pn`): Calculate total proton numbers for chemical formulas
- **Formula Expansion** (`-ext`): Generate expanded representations showing individual atoms
- **Balance Validation** (`-v`): Verify balanced parentheses in chemical formulas

## Compilation

```bash
make
```

## Usage

```bash
./parseFormula <periodicTable.txt> <flag> <input.txt> <output.txt>
```

### Flags
- `-pn`: Calculate proton numbers
- `-ext`: Expand formulas 
- `-v`: Validate parentheses balance

### Examples

```bash
# Calculate proton numbers
./parseFormula periodicTable.txt -pn elements.txt out.txt

# Expand formulas
./parseFormula periodicTable.txt -ext elements.txt out.txt

# Validate parentheses
./parseFormula periodicTable.txt -v elements.txt out.txt
```

## Input Files

- `periodicTable.txt`: Element symbols and atomic numbers
- `elements.txt`: Chemical formulas to process

## Project Structure

- `main.c`: Program entry point and argument handling
- `parser.c/h`: Formula parsing and processing logic
- `stack.c/h`: Stack operations for formula parsing
- `data.c/h`: File I/O and data management
- `Makefile`: Build configuration

## Sample Input/Output

**Input formula:** `H2SO4`
- **Proton count:** `50`
- **Expanded:** `H H S O O O O`

**Input formula:** `Ca(OH)2`
- **Proton count:** `38`
- **Expanded:** `Ca O H O H`