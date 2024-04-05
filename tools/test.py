rows = 3  # Number of rows
cols = 4  # Number of columns

# 1D array representing a 2D array
array1D = [1, 2, 3, 4,
           5, 6, 7, 8,
           9, 10, 11, 12]

# Access each row in the opposite order
for i in range(rows - 1, -1, -1):
    # Calculate the starting index of the current row
    row_start_index = i * cols

    # Access elements of the current row
    for j in range(cols):
        # Calculate the index of the current element
        index = row_start_index + j

        # Access the current element
        print(array1D[index], end=" ")
    print()

