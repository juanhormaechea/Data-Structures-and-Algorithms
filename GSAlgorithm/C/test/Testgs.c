#include "../../../Unity/src/unity.h"
#include "../src/gs.h"
#include <stdbool.h>
#include <stdlib.h>

Person** men = NULL;
Person** women = NULL;

void setUp(void) {

    Person** men = (Person**)malloc(10 * sizeof(Person*));
    Person** women = (Person**)malloc(10 * sizeof(Person*));

    for (int i = 0; i < 10; i++) {
        men[i] = (Person*)malloc(sizeof(Person));
        women[i] = (Person*)malloc(sizeof(Person));
    };
};

void tearDown(void) {
    for (int i = 0; i < 10; i++) {
        free(men[i]);
        free(women[i]);
    };
    free(men);
    free(women);

};


/* ------------------------
 * isFree
 * ------------------------*/

void test_isFree_person_is_null(void) {

};

void test_isFree_engagedTo_set_to_null(void) {

};

void test_isFree_engagedTo_set_to_non_null(void) {

};

/* ------------------
 * hasProposedToEveryone
 * -------------------*/


void test_hasProposedToEveryone_person_is_null(void) {

};

void test_hasProposedToEveryone__numPeople_is_negative(void) {

};

void test_hasProposedToEveryone_numPeople_equal_to_numProposed(void) {

};

void test_hasProposedToEveryone_numPeople_less_than_numProposed(void) {

};

void test_hasProposedToEveryone_numPeople_more_than_numProposed(void) {

};

/* ------------------
 * highestRankedHasNotProposedTo
 * ----------------- */

void test_highestRankedHasNotProposedTo_person_is_null(void) {

};

void test_highestRankedHasNotProposedTo_preferenceList_is_null(void) {

};

void test_highestRankedHasNotProposedTo_empty_preferenceList(void) {

};

void test_highestRankedHasNotProposedTo_numProposed_is_greater_than_size(void) {

};

void test_highestRankedHasNotProposedTo_preferenceList_nonEmpty(void) {

};

/* --------------
 * prefersTo
 * --------------*/


void test_prefersTo_person_is_null(void) {

};

void test_prefersTo_candidates_are_null(void) {

};

void test_prefersTo_preferenceList_is_null(void) {

};

void test_prefersTo_preferenceList_is_empty(void) {

};

void test_prefersTo_candidateOne_preferred(void) {

};

void test_prefersTo_candidateTwo_preferred(void) {

};

void test_prefersTo_candidates_not_present(void) {

};

/* -----------
 * GS 
 * -----------*/

void test_GS_listMenWomen_is_null(void) {

};

void test_GS_listMenWomen_not_equal_to_size(void) {

};

void test_GS_size_zero_or_negative(void) {

};

void test_GS_lists_of_size_one(void) {

};

void test_GS_normal_lists(void) {

};






int main(void) {
    UNITY_BEGIN();



    return UNITY_END();
};