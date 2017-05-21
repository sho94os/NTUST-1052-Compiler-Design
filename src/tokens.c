/*
 * tokens.c
 * Functions for tokens.
 */

#include "tokens.h"

#include <stdlib.h>

#define GENERATE_CASE_FOR_TOKEN_NAME(token, name) case token: return name; break;

const char* get_token_name(token_t token) {
    switch (token) {
        TOKEN_NAMES(GENERATE_CASE_FOR_TOKEN_NAME)
        default:
            return NULL;
            break;
    }
}

const char* get_html_token_name(token_t token) {
    switch (token) {
        HTML_TOKEN_NAMES(GENERATE_CASE_FOR_TOKEN_NAME)
        default:
            return get_token_name(token);
            break;
    }
}
