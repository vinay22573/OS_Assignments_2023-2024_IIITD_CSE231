#!/bin/bash
parent_dir="/mnt/c/Users/DELL/OperatingSys/Assignment_1/Q3"
mkdir -p "$parent_dir/Result"

# Create the output.txt file before the loop starts
> "$parent_dir/Result/output.txt"

while IFS=" " read -r x y operation; do
    if [[ "$operation" = "xor" ]]; then
        result=$((x ^ y))
        operation_result="XOR of $x and $y is $result"
    
    elif [[ "$operation" = "product" ]]; then
        result=$((x * y))
        operation_result="Product of $x and $y is $result"
    
    elif [[ "$operation" = "compare" ]]; then
        if [ "$x" -gt "$y" ]; then
            result="$x"
        else
            result="$y"
        fi
        operation_result="Larger value between $x and $y is $result"
    else
        echo "Unknown operation: $operation"
        operation_result="Vinay has not coded well"
        echo $op
    fi

    # Append the operation result to output.txt
    echo $operation_result >> "$parent_dir/Result/output.txt"

done < input.txt


