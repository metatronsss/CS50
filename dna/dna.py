import csv
import sys
from sys import argv
import cs50


def main():
    # TODO: Check for command-line usage
    argc = len(argv)
    if argc != 3:
        print("Usage need 3 arguments!")
        return 1
    # TODO: Read database file into a variable
    with open(argv[1], 'r') as file1:
        reader = csv.DictReader(file1)
        rows1 = []
        # print(reader.fieldnames[3])
        # ['name', 'AGATC', 'AATG', 'TATC']
        for row in reader:
            rows1.append(row)
        # print(rows)
        '''
        [{"name" : "Alice", "AGATC" : 2, "AATG" : 8, "TATC" : 3},
        {"name" : "Bob", "AGATC" : 4, "AATG" : 1, "TATC" : 5},
        {"name" : "Charlie", "AGATC" : 3, "AATG" : 2, "TATC" : 5}]
        '''
    # TODO: Read DNA sequence file into a variable
    with open(argv[2], 'r') as file2:
        rows2 = []
        for line in file2:
            rows2.append(line)
            # strip() removes any trailing newline characters
            # print(line.strip())
            # AAGGTAAGTTTAGAATATAAA...

    # TODO: Find longest match of each STR in DNA sequence in txt file
    # Find the longest consecutive subsequence of repeated of AGATC,TTTTTTCT,AATG,TCTAG,GATA,TATC,GAAA,TCTG
    # Create a new string and add rows to it without any separated element
    dna_sequence = "".join(rows2)
    the_long_list = [0]
    the_sub_list = [0]
    for i in range(1, len(reader.fieldnames)):
        the_long, the_sub = longest_match(dna_sequence, reader.fieldnames[i])
        the_long_list.append(the_long)
        the_sub_list.append(the_sub)
    # check point to know the longest one, and show which subsequence
    # print(f"{the_long} with {the_sub}")
    # TODO: Check database for matching profiles
    # the repeat times match or not, match by whom
    # Should match the len(reader.fieldnames)-1, means all matched
    count_match = 0
    for person in rows1:
        count_match = 0
        for i in range(1, len(reader.fieldnames)):
            if int(person.get(the_sub_list[i])) == the_long_list[i]:
                count_match += 1
        if count_match == len(reader.fieldnames)-1:
            the_name = person["name"]
            print(f"{the_name}")
            break
    if count_match != len(reader.fieldnames)-1:
        print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)
    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run, subsequence


main()
