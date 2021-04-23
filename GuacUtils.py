from typing import List


def GuacDecode(string: str):
    # If the input string is empty, return an empty list and don't waste any
    # more CPU time
    if not string:
        return list()

    # create an index into the list
    idx = 0

    # create a list of strings, this is what will be returned
    result = list()

    # convert the input string into a list of its component characters
    chars = list(string)

    # begin an infinite loop
    while True:
        # Look at the index and create a string of all the numerical characters
        # connected to it, building up a number
        dist_str = str()
        while chars[idx].isdecimal():
            dist_str += chars[idx]
            idx = idx + 1

        if idx >= 1:
            idx -= 1

        # if that number is a real number, save it as a number type variable
        distance = 0
        if dist_str.isdigit():
            distance = int(dist_str)
        else:
            return None

        # increment the index
        idx += 1

        # if the index is on a period (what it should be) continue
        if chars[idx] != '.':
            return

        # increment the index
        idx += 1

        # Create a substring of the characters between the index and the index
        # plus the number calculated earlier
        addition = ''
        for num in range(idx, idx + distance):
            addition += chars[num]

        # add the substring to the list of strings that will be returned
        result.append(addition)

        # increment the index the length of the substring that was taken
        idx += distance

        # If the index is beyond the end of the list, something is wrong so
        # return the appropriate error
        if idx >= len(chars):
            return

        # match chars[idx]:
        if chars[idx] == ',':
            ()
            # if the current character at the index is a comma, do nothing and
            # continue.
        elif chars[idx] == ';':
            break  # if it is a semicolon,
            # break out of the loop and go to directly after the loop
            # as semicolon ends the statement
        else:
            return

        # increment the index and go through the loop again.
        idx += 1

    # once outside the loop, return the list of strings.
    return result


# pass in a list of strings and get the properly formatted output. This
# function is infallible so no result type is necessary.


def GuacEncode(cypher: List[str]):
    # return an empty string if the list of strings is empty;
    if not cypher:
        return ''

    # replace each string with that string's length, a period, the string
    # iself, and a comma.
    result = ''
    for string in cypher:
        x = f"{len(string)}.{string},"
        result += x

    # replace the final comma with a semicolon
    result = result[:len(result) - 1]
    result += ';'
    # return the string
    return result
