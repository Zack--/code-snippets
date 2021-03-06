/*
** solve.c for 175 Intermediate in DailyProgrammer/175/Intermediate/Mawu3n4
**
** Made by zackaria dibe
** Contact <contact@zackdibe.com>
**
** Started on  Thu Aug 14 13:56:39 2014 zackaria dibe
** Last update Mon Sep 29 14:28:29 2014 zackaria dibe
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define WORD_SIZE       26

int     len(char *s) {
  return (s[0] ? len(&s[1]) + 1 : 0);
}

int     countWords(char *s, char c) {
  return (s[0] ? (s[0] == c) + countWords(&s[1], c) : 1);
}

void    removeChar(char occ, char *str, char *ret) {
  do
    if (*str != occ)
      *ret++ = *str;
  while (*str++);
}

char    *append(char *array, char c) {
  char  *ret = (char *) malloc(sizeof(array) + 2);

  strcpy(ret,array);
  ret[len(ret)] = c;
  ret[sizeof(ret)] = '\0';
  free(array);
  return ret;
}

// Who needs snprintf ?
char    *concat(int n_strings, ...) {
  va_list ap;
  char  *ret, *tmp;
  int   ret_size = 0;

  ret = (char *) malloc(ret_size);
  va_start(ap, n_strings);
  while (n_strings--) {
    tmp = va_arg(ap, char *);
    ret_size += sizeof(tmp);
    ret = (char *) realloc(ret, ret_size);
    strcat(ret, tmp);
  }
  va_end(ap);
  return (ret);
}

// Who needs qsort ?
char    *quickSort(char *data) {
  if (len(data) <= 1)
    return data;
  char pivot = data[0];
  char *left = (char *) malloc(sizeof(data));
  char *right = (char *) malloc(sizeof(data));
  char *equal = (char *) malloc(sizeof(data));

  for (int i = 0; data[i]; ++i) {
    if (data[i] < pivot)
      left = append(left, data[i]);
    else if (data[i] > pivot)
      right = append(right, data[i]);
    else
      equal = append(equal, data[i]);
  }
  return (concat(3, quickSort(left), equal, quickSort(right)));
}

// Who needs strtok ?
void    split(char *str, char **list, char token) {
  int   k = 0;

  list[k] = str;
  while (*str)
    if (*str != token)
      *str++;
    else if (*str == token) {
      *str = '\0';
      *str++;
      list[++k] = str;
    }
  list[++k] = NULL;
}

int     find(char *word, char *letters) {
  if (!*word)
    return (1);
  else if (!*letters)
    return (0);
  else if (*word == *letters)
    return find(word + 1, letters + 1);
  else
    return find(word, letters + 1);
}

int     main(int max_size, char **av) {
  char  **words;
  char  *letters;
  int   nb_words, len_word;
  int   *res;

  // max_size == ac == av length
  if (max_size != 3)
    return (0);

  nb_words = countWords(av[1], ' ');
  words = (char **) malloc(nb_words * sizeof(char *));
  res = (int *) malloc(nb_words * sizeof(int));
  letters = (char *) malloc(sizeof(av[2]));
  removeChar(' ', av[2], letters);
  letters = quickSort(letters);
  split(av[1], words, ' ');
  max_size = 0;
  nb_words = 0;
  for (int i = 0; words[i]; ++i)
    if (find(quickSort(words[i]), letters)) {
      len_word = len(words[i]);
      if (len_word > max_size) {
        max_size = len_word;
        nb_words = 0;
      }
      if (len_word == max_size) {
        res[nb_words] = i;
        nb_words++;
      }
    }
  while (nb_words--)
    printf("%s\n", words[res[nb_words]]);
  free(words);
  free(letters);
  free(res);
}
