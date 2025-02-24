#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int pos = 0;
const char *input;

int parse_expression();
int parse_term();
int parse_factor();
int parse_number();

void skip_whitespace() {
    while (isspace(input[pos])) {
        pos++;
    }
}

int parse_expression() {
    int result = parse_term();
    while (1) {
        skip_whitespace();
        char op = input[pos];
        if (op == '+' || op == '-') {
            pos++;
            int rhs = parse_term();
            if (op == '+') {
                result += rhs;
            } else {
                result -= rhs;
            }
        } else {
            break;
        }
    }
    return result;
}

int parse_term() {
    int result = parse_factor();
    while (1) {
        skip_whitespace();
        char op = input[pos];
        if (op == '*' || op == '/') {
            pos++;
            int rhs = parse_factor();
            if (op == '*') {
                result *= rhs;
            } else {
                if (rhs == 0) {
                    fprintf(stderr, "Error: Division by zero\n");
                    exit(EXIT_FAILURE);
                }
                result /= rhs;
            }
        } else {
            break;
        }
    }
    return result;
}

int parse_factor() {
    skip_whitespace();
    if (input[pos] == '(') {
        pos++;
        int result = parse_expression();
        skip_whitespace();
        if (input[pos] != ')') {
            fprintf(stderr, "Error: Mismatched parentheses\n");
            exit(EXIT_FAILURE);
        }
        pos++;
        return result;
    } else {
        return parse_number();
    }
}

int parse_number() {
    skip_whitespace();
    int result = 0;
    while (isdigit(input[pos])) {
        result = result * 10 + (input[pos] - '0');
        pos++;
    }
    return result;
}

int main() {
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    input = buffer;
    int result = parse_expression();
    printf("%d\n", result);
    return EXIT_SUCCESS;
}
