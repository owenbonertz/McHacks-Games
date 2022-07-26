def roman_to_integer(roman_string)
  # TODO: translate roman string to integer
  ceasar = { I: 1, V: 5, X: 10, L: 50, C: 100, D: 500, M: 1000 }
  count = 0
  for i in 0...roman_string.size
    check_me = roman_string[i].to_sym
    value = ceasar[check_me]
    if (i + 1 <= (roman_string.size - 1)) && ceasar[roman_string[i + 1].to_sym] > value
      count -= value
    else
      count += value
    end
  end
  return count
end
