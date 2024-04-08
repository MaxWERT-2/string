#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

void flags_sup(const char *format, fl *cases, int *counter, va_list *fact) {
  while (format[*counter] == '-' || format[*counter] == '+' ||
         format[*counter] == ' ' || format[*counter] == '#' ||
         format[*counter] == '0') {
    if (format[*counter] == '-') {
      cases->m_fl = 1;
    } else if (format[*counter] == '+') {
      cases->p_fl = 1;
    } else if (format[*counter] == ' ') {
      cases->s_fl = 1;
    } else if (format[*counter] == '#') {
      cases->r_fl = 1;
    } else if (format[*counter] == '0') {
      cases->n_fl = 1;
    }
    (*counter)++;
  }

  while (format[*counter] >= '0' && format[*counter] <= '9') {
    cases->width *= 10;
    cases->width += format[*counter] - '0';
    (*counter)++;
  }

  if (format[*counter] == '*') {
    cases->width = (int)va_arg(*fact, int);
    (*counter)++;
  }
}

void flags_input(const char *format, fl *cases, int *counter, va_list *fact) {
  flags_sup(format, cases, counter, fact);

  if (format[*counter] == '.') {
    (*counter)++;
    cases->a_fl = 1;
    cases->acc = 0;
    if (format[*counter] != '*') {
      while (format[*counter] >= '0' && format[*counter] <= '9') {
        cases->acc *= 10;
        cases->acc += format[*counter] - '0';
        (*counter)++;
      }
    } else {
      cases->acc = (int)va_arg(*fact, int);
      (*counter)++;
    }
  }

  if (format[*counter] == 'h') {
    cases->h_len = 1;
    (*counter)++;
  } else if (format[*counter] == 'l') {
    cases->l_len = 1;
    (*counter)++;
  } else if (format[*counter] == 'L') {
    cases->L_len = 1;
    (*counter)++;
  }
}

void str_output(char *str, const char *s, fl cases, int *cur_it) {
  int len = 0;

  while (s[len] != '\0') {
    ++len;
  }

  if (len < cases.width && (!cases.m_fl)) {
    for (int i = 0; i < cases.width - len; ++i) {
      if (cases.n_fl != 1) {
        str[*cur_it] = ' ';
      } else {
        str[*cur_it] = '0';
      }

      (*cur_it)++;
    }
  }

  int s_counter = 0;
  while (s[s_counter] != '\0') {
    str[*cur_it] = s[s_counter];
    (*cur_it)++;
    s_counter++;
  }

  if (len < cases.width && cases.m_fl) {
    for (int i = 0; i < cases.width - len; ++i) {
      str[*cur_it] = ' ';
      (*cur_it)++;
    }
  }
}

int s21_sprintf(char *str, const char *format, ...) {
  int counter = 0;

  va_list fact;
  va_start(fact, format);

  int cur_it = 0;

  while (format[counter] != '\0') {
    if (format[counter] == '%') {
      counter++;

      fl cases = {0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0};
      flags_input(format, &cases, &counter, &fact);
      char s[100];
      str_forming(format, s, cases, counter, &fact, cur_it);
      str_output(str, s, cases, &cur_it);
    } else {
      str[cur_it] = format[counter];
      cur_it++;
    }

    counter++;
  }

  str[cur_it] = '\0';

  va_end(fact);

  return cur_it;
}