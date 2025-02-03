#!/bin/bash

# Move all .cpp files to the 'src' directory
find . -type f -name "*.cpp" -exec mv {} src/ \;

# Move all .h files to the 'include' directory
find . -type f -name "*.h" -exec mv {} include/ \;

echo "Files have been moved to the appropriate directories."
