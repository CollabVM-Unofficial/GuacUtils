// copy this file into your project

package main

import (
  "errors"
  "strings"
  "strconv"
)

func GuacEncode(src []string) string {
  // if src is empty, return empty string
  if len(src) == 0 { return "" }

  ret := ""
  for _, str := range src {
    // ret += <length>.<str>,
    ret += strconv.Itoa(len(str)) + "." + str + ","
  }
  // end with a ; and not with a ,
  ret = strings.TrimSuffix(ret, ",") + ";"
  return ret
}

func GuacDecode(src_ string) ([]string, error) {
  // if src is empty, return empty slice
  if len(src_) == 0 { return make([]string, 0), nil }
  var ret []string
  src := src_
  for i := 0; i < len(src); {
    lenEnd := strings.Index(src, ".")
    if lenEnd == -1 {
      return nil, errors.New("Invalid guac string (can't find '.')")
    }
    lenStr := src[i:lenEnd]
    lenInt, err := strconv.Atoi(lenStr)
    if err != nil {
      return nil, err
    }
    i = lenEnd + 1
    segment := src[i:i+lenInt]
    ret = append(ret, segment)
    i += lenInt
    switch []rune(src)[i] {
    case ';': break
    case ',':
    default: return nil, errors.New("Invalid guac string (can't find ',' or ';')")
    }
    src = src[i+1:]
    i = 0
  }
  return ret, nil
}
