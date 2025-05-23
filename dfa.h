#ifndef DFA_H
#define DFA_H
#include <stdint.h>
#include <stdbool.h>


/* NOTE: As a result of NFAs being generalizations of DFA, we merge them toge-
 * ther here for code brevity.
 */

// EPSILON shan't occur in a string except at EOF, so it's fine assigning it \0
#define EPSILON '\0'

typedef struct {
    uint8_t from;
    uint8_t to;
    char on;
} Transition_t;

typedef struct {
    uint8_t n_states;
    bool *final_states;
    uint16_t n_transitions;
    Transition_t *transitions;
} DFA_t;

#define IS_FINAL(dfa, state) ((dfa)->final_states[(state)] == true)
#define SET_FINAL(dfa, state, final) ((dfa)->final_states[(state)] = final)
#define SET_TRANSITION(dfa, index, from_, to_, on_)   \
    {                                              \
        (dfa)->transitions[(index)].from = (from_); \
        (dfa)->transitions[(index)].to = (to_);     \
        (dfa)->transitions[(index)].on = (on_);     \
    }

/* Debugging */

void debug(DFA_t *dfa);

/* Constructor & destruction */

DFA_t DFA(uint8_t n_states, uint16_t n_transitions);

DFA_t copy(DFA_t *dfa);

void destroy(DFA_t *dfa);

/* Simulation */

bool accepts(DFA_t *dfa, const char *input);

/* Thompson constructions */

DFA_t singleton(char c);

DFA_t concat(DFA_t *s, DFA_t *t, bool consume_right);

DFA_t join(DFA_t *s, DFA_t *t, bool consume_right);

DFA_t kleene(DFA_t *s);

/* Conversion - converts psudo-DFA into a strict DFA */

DFA_t strictify(DFA_t *dfa);

#endif