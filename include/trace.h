/*
 * tracker is an hybrid trustworthy disassembler that tries to limit the number
 * of false positive paths discovered.
 *
 *  Written and maintained by Emmanuel Fleury <emmanuel.fleury@u-bordeaux.fr>
 *
 * Copyright 2019 University of Bordeaux, CNRS (UMR 5800), France.
 * All rights reserved.
 *
 * This software is released under a 3-clause BSD license (see COPYING file).
 */

#ifndef _TRACE_H
#define _TRACE_H

#include "../graphviz/cgraph.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

#define DEFAULT_HASHTABLE_SIZE 65536 /* 2^16 */

/* A more convenient byte_t type */
typedef uint8_t byte_t;

/* All the possible types of instruction */
typedef enum
{
   BASIC,
   BRANCH,
   CALL,
   JUMP,
   RET
} instr_type_t;

/* ***** Definitions of all the struct used ***** */

/* ***** Handling assembly instructions ***** */
typedef struct _instr_t instr_t;

/* ***** Hashtables to store cfg nodes ***** */
typedef struct _hashtable_t hashtable_t;

/* ***** cfg nodes keeping track of the executions ***** */
typedef struct _cfg_t cfg_t;

/* ***** Linked list to store a trace ***** */
typedef struct _trace_t trace_t;


/* ***** instr_t functions ***** */

/* Return a new instr_t struct, NULL otherwise (and set errno) */
instr_t *instr_new (const uintptr_t addr, const uint8_t size,
                    const uint8_t *opcodes, char *str_name);

/* Delete the assembly instruction from memory */
void instr_delete (instr_t *instr);

/* Get the address of the instruction */
uintptr_t instr_get_addr (instr_t *const instr);

/* Get the size (in bytes) of the instruction */
size_t instr_get_size (instr_t *const instr);

/* Get a pointer to the opcodes of the instruction */
uint8_t * instr_get_opcodes (instr_t *const instr);


/* ***** hashtable_t functions ***** */

/* Return an hash index for the instruction */
uint64_t hash_instr (const instr_t *instr);

/* Initialize a new hashtable of given size, returns NULL is size == 0 */
hashtable_t *hashtable_new (const size_t size);

/* Free the given hashtable */
void hashtable_delete (hashtable_t *ht);

/* Insert the instruction in the hashtable */
bool hashtable_insert (hashtable_t *ht, cfg_t *cfg);

/* Look-up if current instruction is already in the hashtable */
cfg_t *hashtable_lookup (hashtable_t *ht, instr_t *instr);

/* Count the number of entries in the hashtable */
size_t hashtable_entries (hashtable_t *ht);

/* Count the number of collisions in the hashtable */
size_t hashtable_collisions (hashtable_t *ht);


/* ***** trace_t functions ***** */

/* Creates a trace and initialize it with ins
Returns a pointer to the created trace, or NULL if an error occured */
trace_t *trace_new (instr_t *ins);

/* Creates an element initialized with ins and insert it after t
Returns a pointer to the created element or NULL if an error occured */
trace_t *trace_insert (trace_t *t, instr_t *ins);

/* Free every element in the trace t */
void trace_delete (trace_t *t);

/* Returns a pointer to the first element where t2 differs from t1 */
trace_t *trace_compare (trace_t *t1, trace_t *t2);


/* ***** cfg_t functions ***** */

/* Creates a cfg and it with hash_index
Returns a pointer to the created trace, or NULL if an error occured */
cfg_t *cfg_new (hashtable_t *ht, instr_t *ins, char *str);

/* Auxiliary function for cfg_insert */
cfg_t *aux_cfg_insert (cfg_t *CFG, cfg_t *new);

/* Creates an element initialized with ins and insert it in CFG's succesors
Returns a pointer to the created element or NULL if an error occured*/
cfg_t *cfg_insert (hashtable_t *ht, cfg_t *CFG, instr_t *ins, Agraph_t *g, char *str);

/* Free every allocated field of CFG, as well as CFG itself */
void cfg_delete (cfg_t *CFG);

/* Get the instruction in CFG */
instr_t *cfg_get_instr (cfg_t *CFG);

/* Get the number of successors of CFG */
uint16_t cfg_get_nb_out (cfg_t *CFG);

/* Get the number of "parents" of CFG */
uint16_t cfg_get_nb_in (cfg_t *CFG);

/* Get the type of the instruction in CFG */
instr_type_t cfg_get_type (cfg_t *CFG);

/* Get the index of the function CFG is in */
uint16_t cfg_get_name (cfg_t *CFG);

/* Get a pointer array of every successor of CFG */
cfg_t **cfg_get_successor (cfg_t *CFG);

/* Get a pointer to successor number i of CFG */
cfg_t *cfg_get_successor_i (cfg_t *CFG, uint16_t i);

/* Get the total number of functions */
size_t get_nb_name (void);

/* Get the str with the address, the opcodes, the mnemonics and the operands */
char *cfg_get_str (cfg_t *CFG);

/* Get a pointer to the first node in the function number index */
cfg_t *get_function_entry (size_t index);

/* Adds the very first node to function_entry */ 
void add_first_entry (cfg_t *CFG);

#endif /* _TRACE_H */
