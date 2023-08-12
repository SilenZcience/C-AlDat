// geht davon aus, dass str null-terminated ist
char* trim(char* str) {
  // simply trim the left most #-chars
  // by incrementing the string start until
  // a non-#-char is found.
  while (str[0] == '#') {
    str++;
  }

  int last_not_hashtag_pos = 0;
  // iterate over the entire string, when we find a
  // non-#-char, we save its position, thus at the end
  // of the string the variable holds the last
  // non-#-char position.
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] != '#') {
      last_not_hashtag_pos = i;
    }
  }
  
  // end the string after the last found non-#-char
  // by setting the char behind it to '\0'.
  // This may very well replace '\0' with itself, if no
  // #-chars are at the right hand side of the string.
  str[last_not_hashtag_pos+1] = '\0';
  
  return str;
}

