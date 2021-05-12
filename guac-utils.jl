function guac_encode(cypher ::Vector{String})::String
    if Base.length(cypher) == 0
        return ""
    end
    result = join(
        map(
            s -> "$(length(s)).$s,",
            cypher
        )
    )
    result = chop(result)
    result = result * ";"
    return result
end

function guac_decode(string ::String) ::Vector{String}
    # If the input string is empty, return an empty list and don't waste any
    # more CPU time
    if length(string) <= 1
        return []
    end
    # create an index into the list
    idx = 1

    # create a list of strings, this is what will be returned
    result = []

    # convert the input string into a list of its component characters
    chars = collect(map(x -> "$(x)" ,collect(string)))

    # begin an infinite loop
    while true
        # Look at the index and create a string of all the numerical characters
        # connected to it, building up a number
        dist_str = ""
        while tryparse(Int, chars[idx]) !== nothing
            dist_str = dist_str * chars[idx]
            idx = idx + 1
        end

        if idx >= 2
            idx -= 1
        end

        # if that number is a real number, save it as a number type variable
        distance = 0
        if tryparse(Int, dist_str) !== nothing
            distance = parse(Int, dist_str)
        else
            break
        end
        # increment the index
        idx += 1

        # if the index is on a period (what it should be) continue
        if chars[idx] != "."
            break
        end
        # increment the index
        idx += 1
        # Create a substring of the characters between the index and the index
        # plus the number calculated earlier
        addition = ""
        for num in range(idx, length = distance)
            addition = addition * chars[num]
        end
        # add the substring to the list of strings that will be returned
        push!(result, addition)

        # increment the index the length of the substring that was taken
        idx += distance

        # If the index is beyond the end of the list, something is wrong so
        # return the appropriate error
        if idx >= length(chars)
            break
        end
        # match chars[idx]:
        if chars[idx] == ","
            #continue
            # if the current character at the index is a comma, do nothing and
            # continue.
        elseif chars[idx] == ";"
            break  # if it is a semicolon,
            # break out of the loop and go to directly after the loop
            # as semicolon ends the statement
        else
            break
        end
        # increment the index and go through the loop again.
        idx += 1
    end
    # once outside the loop, return the list of strings.
    return result
end