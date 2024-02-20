#!/bin/bash

# Initialize subshell count
SUBSHELL_COUNT=0

# Function to increment subshell count
increment_subshell_count() {
    (( SUBSHELL_COUNT++ ))
}

# Set DEBUG trap to execute increment_subshell_count function whenever a subshell is created
trap '[[ $BASH_SUBSHELL -gt 0 ]] && increment_subshell_count' DEBUG

# Your script code here

# Example usage
(
    echo "Inside subshell"
    echo "Current subshell count: $SUBSHELL_COUNT"
)

echo "Outside subshell"
echo "Final subshell count: $SUBSHELL_COUNT"