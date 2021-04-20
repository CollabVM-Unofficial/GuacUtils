///pass in a properly formatted string and get a result (monad) of a list of strings or a returned error
pub fn guac_decode(str: String) -> Result<Vec<String>, DecodeError> {
    //If the input string is empty, return an empty list
    if str.is_empty() {
        return Ok(Vec::new());
    }

    //create an index into the list
    let mut idx: usize = 0;

    //create a list of strings, this is what will be returned
    let mut result = Vec::new();

    //convert the input string into a list of its component characters
    let chars = str.chars().collect::<Vec<_>>();
    
    //begin an infinite loop
    loop {
        //Look at the index and create a string of all the numerical characters 
        //connected to it, building up a number
        let mut dist_str = String::new();
        while chars[idx].is_numeric() {
            dist_str.push(chars[idx]);
            idx += 1;
        }
        if idx >= 1 {
            idx -= 1
        };

        //if that number is a real number, save it as a number type variable
        let distance = if let Ok(distance) = dist_str.parse::<usize>() {
            distance
        } else {
            //if it is not a real number, return an error.
            return Err(DecodeError::DistanceNotInteger {
                idx: idx,
                was: chars[idx],
            });
        };

        //increment the index
        idx += 1;

        //if the index is on a period (what it should be) continue, otherwise return the appropriate error.
        if chars[idx] != '.' {
            return Err(DecodeError::WrongDelimiter {
                idx,
                was: chars[idx],
                expected: vec!['.'],
            });
        }

        //increment the index
        idx += 1;

        //Create a substring of the characters between the index and the index plus the number calculated earlier
        let addition = chars.iter().skip(idx).take(distance).collect::<String>();

        //add the substring to the list of strings that will be returned
        result.push(addition);

        //increment the index the length of the substring that was taken
        idx += distance;

        //If the index is beyond the end of the list, something is wrong so return the appropriate error
        if idx >= chars.len() {
            return Err(DecodeError::WrongDistance {
                idx: chars.len() - 1,
            });
        }

        match chars[idx] {
            ',' => {}     //if the current character at the index is a comma, do nothing and continue.
            ';' => break, //if it is a semicolon, break out of the loop and go to directly after the loop 
                          //as semicolon ends the statement
            busted @ _ => {
                //if it is anything else, return the appropriate error.
                return Err(DecodeError::WrongDelimiter {
                    idx,
                    expected: vec![',', ';'],
                    was: busted,
                });
            }
        }

        //increment the index and go through the loop again.
        idx += 1;
    }

    //once outside the loop, return the list of strings.
    return Ok(result);
}

///pass in a list of strings and get the properly formatted output. This function is infallible so no result type is necessary.
pub fn guac_encode(cypher: Vec<String>) -> String {
    //return an empty string if the list of strings is empty;
    if cypher.is_empty() {
        return String::new();
    }

    //replace each string with that string's length, a period, the string iself, and a comma.
    let mut result = cypher
        .iter()
        .map(|string| format!("{}.{}{}", &string.len(), *string, ','))
        .collect::<String>(); //combine all the modified strings

    //replace the final comma with a semicolon
    result.pop();
    result.push(';');

    //return the string
    return result;
}

///Error type for proper error handling
#[derive(PartialEq, Eq)]
pub enum DecodeError {
    //where the non-number is, and what character was there
    DistanceNotInteger {
        idx: usize,
        was: char,
    },
    //where the wrong delimiter is, what it is, and what could have been there
    WrongDelimiter {
        idx: usize,
        was: char,
        expected: Vec<char>,
    },
    //show where the overflow would have happened
    WrongDistance {
        idx: usize,
    },
}

///pretty printing for the error type
///format the error messages in a way that makes sense.
impl std::fmt::Debug for DecodeError {
    //this function signature was given by the standard library, the implementation is original though.
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            DecodeError::DistanceNotInteger { idx, was } => {
                write!(f, "Error at index {}: expected a number, got {}", idx, was)
            }
            DecodeError::WrongDelimiter { idx, was, expected } => {
                write!(
                    f,
                    "Error at index {}: expected {} got \"{}\"",
                    idx,
                    expected //combine the list of the legal characters into one formatted string
                        .iter()
                        .map(|x| format!("\"{}\", ", x))
                        .collect::<String>(),
                    was
                )
            }
            DecodeError::WrongDistance { idx } => {
                write!(
                    f,
                    "Error at index {}: attempted index value would overflow string",
                    idx
                )
            }
        }
    }
}

///extensive test suite
#[cfg(test)]
mod tests {
    //bring in all the above functions
    use super::*;
    #[test]
    fn encode_success() {
        assert_eq!(
            guac_encode(vec![
                "testing!".to_string(),
                "talltree".to_string(),
                "crab's lang".to_string()
            ]),
            "8.testing!,8.talltree,11.crab's lang;".to_string()
        )
    }
    #[test]
    fn encode_success_empty() {
        assert_eq!(guac_encode(vec!["".to_string()]), "0.;".to_string())
    }
    #[test]
    fn decode_success() {
        assert_eq!(
            guac_decode("8.testing!,8.talltree,11.crab's-lang;".to_string()),
            Ok(vec![
                "testing!".to_string(),
                "talltree".to_string(),
                "crab's-lang".to_string()
            ])
        )
    }
    #[test]
    fn decode_empty() {
        assert_eq!(guac_decode("".to_string()), Ok(vec![]))
    }
    #[test]
    fn decode_wrong_dist_delimiter() {
        assert_eq!(
            guac_decode("8.testing!,8@talltree;".to_string()),
            Err(DecodeError::WrongDelimiter {
                idx: 12,
                expected: vec!['.'],
                was: '@'
            })
        );
        assert_eq!(
            guac_decode("9\n999999999;".to_string()),
            Err(DecodeError::WrongDelimiter {
                idx: 1,
                expected: vec!['.'],
                was: '\n'
            })
        );
    }
    #[test]
    fn no_dist_delimiter() {
        assert_eq!(
            guac_decode("8testing!,8talltree;".to_string()),
            Err(DecodeError::WrongDelimiter {
                idx: 1,
                expected: vec!['.'],
                was: 't'
            })
        );
    }
    #[test]
    fn non_ascii() {
        assert_eq!(
            guac_decode("7.螃蟹所讲的语言,31.The language spoken by the crab;".to_string()),
            Ok(vec![
                "螃蟹所讲的语言".to_string(),
                "The language spoken by the crab".to_string()
            ])
        )
    }
    #[test]
    fn wrong_ending_delimiter() {
        assert_eq!(
            guac_decode("8.talltree+".to_string()),
            Err(DecodeError::WrongDelimiter {
                idx: 10,
                expected: vec![',', ';'],
                was: '+'
            })
        )
    }
    #[test]
    fn no_ending_delimiter() {
        assert_eq!(
            guac_decode("8.talltree".to_string()),
            Err(DecodeError::WrongDistance { idx: 9 })
        )
    }
    #[test]
    fn wrong_distance() {
        assert_eq!(
            guac_decode("15.talltree;".to_string()),
            Err(DecodeError::WrongDistance { idx: 11 })
        )
    }
}
