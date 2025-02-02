#!/bin/bash

# Define the new copyright comment
COPYRIGHT="// Copyright (c) 2025 No Way Out LLC All rights reserved.\n"

# Loop through all .cpp and .h files in the project directory
find . -type f \( -name "*.cpp" -o -name "*.h" \) | while read -r file; do
    # Get the current content of the file
    file_content=$(cat "$file")

    # Remove empty comment lines (lines with just "//")
    updated_content=$(echo "$file_content" | sed '/^\s*\/\//d')

    # Remove any existing copyright lines (those starting with "// Copyright")
    updated_content=$(echo "$updated_content" | sed '/\/\/ Copyright/d')

    # Prepend the new copyright header to the content
    echo -e "$COPYRIGHT$updated_content" > "$file"

    # Optional: Output the updated file name to track progress
    echo "Updated: $file"
done
