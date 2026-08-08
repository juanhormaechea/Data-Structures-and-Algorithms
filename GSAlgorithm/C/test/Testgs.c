#include "../../../Unity/src/unity.h"                                 
                                                                      
#include "../src/gs.h"                                                
                                                                      
#include <stdbool.h>                                                  
                                                                      
#include <stdlib.h>                                                   
                                                                      
                                                                      
                                                                      
Person** men = NULL;                                                  
                                                                      
Person** women = NULL;                                                
                                                                      
                                                                      
                                                                      
void setUp(void) {                                                    
                                                                                                                                       
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
void tearDown(void) {                                                 
                                                                                                                         
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
/* ------------------------                                           
                                                                      
 * isFree                                                             
                                                                      
 * ------------------------*/                                         
                                                                      
                                                                      
                                                                      
void test_isFree_person_is_null(void) {                               
                                                                      
    Person* person = NULL;                                            
                                                                      
    TEST_ASSERT(!isFree(person));                                     
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
void test_isFree_engagedTo_set_to_null(void) {                        
                                                                      
    Person* person = (Person*)malloc(sizeof(Person));                 
                                                                      
    person->engagedTo = NULL;                                         
                                                                      
    TEST_ASSERT(isFree(person));                                      
                                                                      
    free(person);                                                     
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
void test_isFree_engagedTo_set_to_non_null(void) {                    
                                                                      
    Person* person = (Person*)malloc(sizeof(Person));                 
                                                                      
    Person* engagedTo = (Person*)malloc(sizeof(Person));              
                                                                      
    person->engagedTo = engagedTo;                                    
                                                                      
    TEST_ASSERT(!isFree(person));                                     
                                                                      
    free(engagedTo);                                                  
                                                                      
    free(person);                                                     
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
/* ------------------                                                 
                                                                      
 * hasProposedToEveryone                                              
                                                                      
 * -------------------*/                                              
                                                                      
                                                                      
                                                                      
void test_hasProposedToEveryone_person_is_null(void) {                
                                                                      
    Person* person = NULL;                                            
                                                                      
    int numPeople = 5;                                                
                                                                      
    TEST_ASSERT(hasProposedToEveryone(person, numPeople));            
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
void test_hasProposedToEveryone__numPeople_is_negative(void) {        
                                                                      
    Person* person = (Person*)malloc(sizeof(Person));                 
                                                                      
    int numPeople = -1;                                               
                                                                      
    TEST_ASSERT(hasProposedToEveryone(person, numPeople));            
                                                                      
    free(person);                                                     
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
void test_hasProposedToEveryone_numPeople_equal_to_numProposed(void) {
                                                                      
    Person* person = (Person*)malloc(sizeof(Person));                 
                                                                      
    person->numProposed = 5;                                          
                                                                      
    int numPeople = 5;                                                
                                                                      
    TEST_ASSERT(hasProposedToEveryone(person, numPeople));            
                                                                      
    free(person);                                                     
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
void test_hasProposedToEveryone_numPeople_less_than_numProposed(void) 
{                                                                     
                                                                      
    Person* person = (Person*)malloc(sizeof(Person));                 
                                                                      
    person->numProposed = 3;                                          
                                                                      
    int numPeople = 5;                                                
                                                                      
    TEST_ASSERT(!hasProposedToEveryone(person, numPeople));           
                                                                      
    free(person);                                                     
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
void test_hasProposedToEveryone_numPeople_more_than_numProposed(void) 
{                                                                     
                                                                      
    Person* person = (Person*)malloc(sizeof(Person));                 
                                                                      
    person->numProposed = 7;                                          
                                                                      
    int numPeople = 5;                                                
                                                                      
    TEST_ASSERT(hasProposedToEveryone(person, numPeople));            
                                                                      
    free(person);                                                     
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
/* ------------------                                                 
                                                                      
 * highestRankedHasNotProposedTo                                      
                                                                      
 * ----------------- */                                               
                                                                      
                                                                      
                                                                      
void test_highestRankedHasNotProposedTo_person_is_null(void) {        
                                                                      
    Person* person = NULL;                                            
                                                                      
    int sizeOfPreferenceList = 5;                                     
                                                                      
    TEST_ASSERT(highestRankedHasNotProposedTo(person,                 
sizeOfPreferenceList) == NULL);                                       
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
void test_highestRankedHasNotProposedTo_preferenceList_is_null(void) {
                                                                      
    Person* person = (Person*)malloc(sizeof(Person));                 
                                                                      
    person->preferenceList = NULL;                                    
                                                                      
    int sizeOfPreferenceList = 5;                                     
                                                                      
    TEST_ASSERT(highestRankedHasNotProposedTo(person,                 
sizeOfPreferenceList) == NULL);                                       
                                                                      
    free(person);                                                     
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
void test_highestRankedHasNotProposedTo_empty_preferenceList(void) {  
                                                                      
    Person* person = (Person*)malloc(sizeof(Person));                 
                                                                      
    person->preferenceList = (Person**)malloc(5 * sizeof(Person*));   
                                                                      
    int sizeOfPreferenceList = 0;                                     
                                                                      
    TEST_ASSERT(highestRankedHasNotProposedTo(person,                 
sizeOfPreferenceList) == NULL);                                       
                                                                      
    free(person->preferenceList);                                     
                                                                      
    free(person);                                                     
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
void                                                                  
test_highestRankedHasNotProposedTo_numProposed_is_greater_than_size(void) {                                                                 
                                                                      
    Person* person = (Person*)malloc(sizeof(Person));                 
                                                                      
    person->preferenceList = (Person**)malloc(5 * sizeof(Person*));   
                                                                      
    person->numProposed = 7;                                          
                                                                      
    int sizeOfPreferenceList = 5;                                     
                                                                      
    TEST_ASSERT(highestRankedHasNotProposedTo(person,                 
sizeOfPreferenceList) == NULL);                                       
                                                                      
    free(person->preferenceList);                                     
                                                                      
    free(person);                                                     
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
void test_highestRankedHasNotProposedTo_preferenceList_nonEmpty(void) 
{                                                                     
                                                                      
    Person* person = (Person*)malloc(sizeof(Person));                 
                                                                      
    person->preferenceList = (Person**)malloc(5 * sizeof(Person*));   
                                                                      
    for (int i = 0; i < 5; i++) {                                     
                                                                      
        person->preferenceList[i] = (Person*)malloc(sizeof(Person));  
                                                                      
    }                                                                 
                                                                      
    person->numProposed = 3;                                          
                                                                      
    int sizeOfPreferenceList = 5;                                     
                                                                      
    Person* result = highestRankedHasNotProposedTo(person,            
sizeOfPreferenceList);                                                
                                                                      
    TEST_ASSERT(result != NULL);                                      
                                                                      
    for (int i = 0; i < 5; i++) {                                     
                                                                      
        free(person->preferenceList[i]);                              
                                                                      
    }                                                                 
                                                                      
    free(person->preferenceList);                                     
                                                                      
    free(person);                                                     
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
/* --------------                                                     
                                                                      
 * prefersTo                                                          
                                                                      
 * --------------*/                                                   
                                                                      
                                                                      
                                                                      
void test_prefersTo_person_is_null(void) {                            
                                                                      
    Person* person = NULL;                                            
                                                                      
    Person* candidateOne = (Person*)malloc(sizeof(Person));           
                                                                      
    Person* candidateTwo = (Person*)malloc(sizeof(Person));           
                                                                      
    TEST_ASSERT(!prefersTo(person, candidateOne, candidateTwo));      
                                                                      
    free(candidateOne);                                               
                                                                      
    free(candidateTwo);                                               
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
void test_prefersTo_candidates_are_null(void) {                       
                                                                      
    Person* person = (Person*)malloc(sizeof(Person));                 
                                                                      
    Person* candidateOne = NULL;                                      
                                                                      
    Person* candidateTwo = NULL;                                      
                                                                      
    TEST_ASSERT(!prefersTo(person, candidateOne, candidateTwo));      
                                                                      
    free(person);                                                     
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
void test_prefersTo_preferenceList_is_null(void) {                    
                                                                      
    Person* person = (Person*)malloc(sizeof(Person));                 
                                                                      
    person->preferenceList = NULL;                                    
                                                                      
    Person* candidateOne = (Person*)malloc(sizeof(Person));           
                                                                      
    Person* candidateTwo = (Person*)malloc(sizeof(Person));           
                                                                      
    TEST_ASSERT(!prefersTo(person, candidateOne, candidateTwo));      
                                                                      
    free(candidateOne);                                               
                                                                      
    free(candidateTwo);                                               
                                                                      
    free(person);                                                     
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
void test_prefersTo_preferenceList_is_empty(void) {                   
                                                                      
    Person* person = (Person*)malloc(sizeof(Person));                 
                                                                      
    person->preferenceList = (Person**)malloc(5 * sizeof(Person*));   
                                                                      
    Person* candidateOne = (Person*)malloc(sizeof(Person));           
                                                                      
    Person* candidateTwo = (Person*)malloc(sizeof(Person));           
                                                                      
    TEST_ASSERT(!prefersTo(person, candidateOne, candidateTwo));      
                                                                      
    free(candidateOne);                                               
                                                                      
    free(candidateTwo);                                               
                                                                      
    free(person->preferenceList);                                     
                                                                      
    free(person);                                                     
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
void test_prefersTo_candidateOne_preferred(void) {                    
                                                                      
    Person* person = (Person*)malloc(sizeof(Person));                 
                                                                      
    person->preferenceList = (Person**)malloc(5 * sizeof(Person*));   
                                                                      
    for (int i = 0; i < 5; i++) {                                     
                                                                      
        person->preferenceList[i] = (Person*)malloc(sizeof(Person));  
                                                                      
    }                                                                 
                                                                      
    person->numProposed = 3;                                          
                                                                      
    Person* candidateOne = person->preferenceList[1];                 
                                                                      
    Person* candidateTwo = person->preferenceList[2];                 
                                                                      
    TEST_ASSERT(prefersTo(person, candidateOne, candidateTwo));       
                                                                      
    for (int i = 0; i < 5; i++) {                                     
                                                                      
        free(person->preferenceList[i]);                              
                                                                      
    }                                                                 
                                                                      
    free(person->preferenceList);                                     
                                                                      
    free(person);                                                     
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
void test_prefersTo_candidateTwo_preferred(void) {                    
                                                                      
    Person* person = (Person*)malloc(sizeof(Person));                 
                                                                      
    person->preferenceList = (Person**)malloc(5 * sizeof(Person*));   
                                                                      
    for (int i = 0; i < 5; i++) {                                     
                                                                      
        person->preferenceList[i] = (Person*)malloc(sizeof(Person));  
                                                                      
    }                                                                 
                                                                      
    person->numProposed = 3;                                          
                                                                      
    Person* candidateOne = person->preferenceList[2];                 
                                                                      
    Person* candidateTwo = person->preferenceList[1];                 
                                                                      
    TEST_ASSERT(!prefersTo(person, candidateOne, candidateTwo));      
                                                                      
    for (int i = 0; i < 5; i++) {                                     
                                                                      
        free(person->preferenceList[i]);                              
                                                                      
    }                                                                 
                                                                      
    free(person->preferenceList);                                     
                                                                      
    free(person);                                                     
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
void test_prefersTo_candidates_not_present(void) {                    
                                                                      
    Person* person = (Person*)malloc(sizeof(Person));                 
                                                                      
    person->preferenceList = (Person**)malloc(5 * sizeof(Person*));   
                                                                      
    for (int i = 0; i < 5; i++) {                                     
                                                                      
        person->preferenceList[i] = (Person*)malloc(sizeof(Person));  
                                                                      
    }                                                                 
                                                                      
    person->numProposed = 3;                                          
                                                                      
    Person* candidateOne = (Person*)malloc(sizeof(Person));           
                                                                      
    Person* candidateTwo = (Person*)malloc(sizeof(Person));           
                                                                      
    TEST_ASSERT(!prefersTo(person, candidateOne, candidateTwo));      
                                                                      
    for (int i = 0; i < 5; i++) {                                     
                                                                      
        free(person->preferenceList[i]);                              
                                                                      
    }                                                                 
                                                                      
    free(person->preferenceList);                                     
                                                                      
    free(candidateOne);                                               
                                                                      
    free(candidateTwo);                                               
                                                                      
    free(person);                                                     
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
/* -----------                                                        
                                                                      
 * GS                                                                 
                                                                      
 * -----------*/                                                      
                                                                      
                                                                      
                                                                      
void test_GS_listMenWomen_is_null(void) {                             
                                                                      
    Person** men = NULL;                                              
                                                                      
    Person** women = NULL;                                            
                                                                      
    int size = 5;                                                     
                                                                      
    TEST_ASSERT(GS(men, women, size) == NULL);                        
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
void test_GS_listMenWomen_not_equal_to_size(void) {                   
                                                                      
    Person** men = (Person**)malloc(10 * sizeof(Person*));            
                                                                      
    Person** women = (Person**)malloc(5 * sizeof(Person*));           
                                                                      
    int size = 5;                                                     
                                                                      
    TEST_ASSERT(GS(men, women, size) == NULL);                        
                                                                      
    for (int i = 0; i < 10; i++) {                                    
                                                                      
        free(men[i]);                                                 
                                                                      
    }                                                                 
                                                                      
    free(men);                                                        
                                                                      
    for (int i = 0; i < 5; i++) {                                     
                                                                      
        free(women[i]);                                               
                                                                      
    }                                                                 
                                                                      
    free(women);                                                      
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
void test_GS_size_zero_or_negative(void) {                            
                                                                      
    Person** men = (Person**)malloc(10 * sizeof(Person*));            
                                                                      
    Person** women = (Person**)malloc(10 * sizeof(Person*));          
                                                                      
    int size = 0;                                                     
                                                                      
    TEST_ASSERT(GS(men, women, size) == NULL);                        
                                                                                                                                            
                                                                      
    size = -5;                                                        
                                                                      
    TEST_ASSERT(GS(men, women, size) == NULL);                        
                                                                      
    for (int i = 0; i < 10; i++) {                                    
                                                                      
        free(men[i]);                                                 
                                                                      
    }                                                                 
                                                                      
    free(men);                                                        
                                                                      
    for (int i = 0; i < 10; i++) {                                    
                                                                      
        free(women[i]);                                               
                                                                      
    }                                                                 
                                                                      
    free(women);                                                      
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
void test_GS_lists_of_size_one(void) {                                
                                                                      
    Person** men = (Person**)malloc(1 * sizeof(Person*));             
                                                                      
    Person** women = (Person**)malloc(1 * sizeof(Person*));           
    Person* man = (Person*)malloc(sizeof(Person));   
    Person* woman = (Person*)malloc(sizeof(Person));
    
    man->engagedTo = NULL;
    woman->engagedTo = NULL;
    man->numProposed = 0;
    man->preferenceList = (Person**)malloc(sizeof(Person*));
    man->preferenceList[0] = woman;
    woman->preferenceList = (Person**)malloc(sizeof(Person*));
    woman->preferenceList[0] = man;

    men[0] = man;                        
                                                                      
    women[0] = woman;                       
                                                                      
    int size = 1;                                                     
                                                                      
    Person*** matchList = GS(men, women, size);                       
                                    
    TEST_ASSERT(matchList != NULL);                                   
                                                                      
    TEST_ASSERT(matchList[0][0] == men[0]);                           
                                                                      
    TEST_ASSERT(matchList[0][1] == women[0]);                         
                                                                                                                           
                                                                      
    for (int i = 0; i < size; i++) {                                  
                                                                      
        free(matchList[i][0]);                                        
                                                                      
        free(matchList[i][1]);                                        
                                                                      
        free(matchList[i]);                                           
                                                                      
    }                                                                 
                                                                      
    free(matchList);                                                  
                                                                      
}                                                                     
                                                                      
                                                                      
                                                                      
void test_GS_equal_preference_lists(void) {                                     
                                                                      
    Person** men = (Person**)malloc(5 * sizeof(Person*));             
                                                                      
    Person** women = (Person**)malloc(5 * sizeof(Person*));           
                                                                      
    for (int i = 0; i < 5; i++) {                                     
                                                                      
        men[i] = (Person*)malloc(sizeof(Person));                     
        women[i] = (Person*)malloc(sizeof(Person));
        men[i]->engagedTo = NULL;
        men[i]->numProposed = 0;
        women[i]->engagedTo = NULL;
        women[i]->numProposed = 0;
        
                                                                      
    };
    

    for (int i = 0; i < 5; i++) {
        men[i]->preferenceList = (Person**)malloc(5*sizeof(Person*));
        women[i]->preferenceList = (Person**)malloc(5*sizeof(Person*));
        for (int a = 0; a < 5; a++) {
            men[i]->preferenceList[a] = women[a];
            women[i]->preferenceList[a] = men[a];
        };
    };
    
                                                                      
    // Initialize preference lists and other properties               
                                                                                                                         
                                                                      
    Person*** matchList = GS(men, women, 5);                       
                                                                      
    TEST_ASSERT(matchList != NULL);                                   
                                                                      
    for (int i = 0; i < 5; i++) {
        Person* man = matchList[i][0];
        Person* currentEngagement = matchList[i][1];
        for (int a = 0; a < 5; a++) {
            if (a != i) {
                Person* possibleMatchCurrentEngagement = matchList[a][0];
                Person* possibleMatch = matchList[a][1];
                TEST_ASSERT(!(prefersTo(man, possibleMatch, currentEngagement) && prefersTo(possibleMatch, man, possibleMatchCurrentEngagement)));
            }
        }
    };
    
    
    for (int i = 0; i < 5; i++) {
        free(matchList[i][0]);
        free(matchList[i][1]);
        free(matchList[i]);
    };

    free(matchList);
                                                                      
};


void test_GS_distinct_preferenceLists(void) {
    Person** men = (Person**)malloc(5 * sizeof(Person*));             
                                                                      
    Person** women = (Person**)malloc(5 * sizeof(Person*));           
                                                                      
    for (int i = 0; i < 5; i++) {                                     
                                                                      
        men[i] = (Person*)malloc(sizeof(Person));                     
        women[i] = (Person*)malloc(sizeof(Person));
        men[i]->engagedTo = NULL;
        men[i]->numProposed = 0;
        women[i]->engagedTo = NULL;
        women[i]->numProposed = 0;
        
                                                                      
    };
    

    for (int i = 0; i < 5; i++) {
        men[i]->preferenceList = (Person**)malloc(5*sizeof(Person*));
        women[i]->preferenceList = (Person**)malloc(5*sizeof(Person*));
        for (int a = 0; a < 5; a++) {
            men[i]->preferenceList[a] = women[a%i];
            women[i]->preferenceList[a] = men[a];
        };
    };

    
    Person*** matchList = GS(men, women, 5);                       
                                                                      
    TEST_ASSERT(matchList != NULL);                                   
                                                                      
    for (int i = 0; i < 5; i++) {
        Person* man = matchList[i][0];
        Person* currentEngagement = matchList[i][1];
        for (int a = 0; a < 5; a++) {
            if (a != i) {
                Person* possibleMatchCurrentEngagement = matchList[a][0];
                Person* possibleMatch = matchList[a][1];
                TEST_ASSERT(!(prefersTo(man, possibleMatch, currentEngagement) && prefersTo(possibleMatch, man, possibleMatchCurrentEngagement)));
            }
        }
    };
    
    
    for (int i = 0; i < 5; i++) {
        free(matchList[i][0]);
        free(matchList[i][1]);
        free(matchList[i]);
    };

    free(matchList);



}
                                                                      
                                                                      
                                                                      
int main(void) {                                                      
                                                                      
    UNITY_BEGIN();                                                    
                                                                      
                                                                      
                                                                      
    RUN_TEST(test_isFree_person_is_null);                             
                                                                      
    RUN_TEST(test_isFree_engagedTo_set_to_null);                      
                                                                      
    RUN_TEST(test_isFree_engagedTo_set_to_non_null);                  
                                                                      
                                                                      
                                                                      
    RUN_TEST(test_hasProposedToEveryone_person_is_null);              
                                                                      
    RUN_TEST(test_hasProposedToEveryone__numPeople_is_negative);      
                                                                      
    RUN_TEST(test_hasProposedToEveryone_numPeople_equal_to_numProposed);                                                                    
                                                                      
    RUN_TEST(test_hasProposedToEveryone_numPeople_less_than_numProposed);                                                                   
                                                                      
    RUN_TEST(test_hasProposedToEveryone_numPeople_more_than_numProposed);                                                                   
                                                                      
                                                                      
                                                                      
    RUN_TEST(test_highestRankedHasNotProposedTo_person_is_null);      
                                                                      
    RUN_TEST(test_highestRankedHasNotProposedTo_preferenceList_is_null);                                                                    
                                                                      
    RUN_TEST(test_highestRankedHasNotProposedTo_empty_preferenceList);
                                                                      
    RUN_TEST(test_highestRankedHasNotProposedTo_numProposed_is_greater_than_size);                                                          
                                                                      
    RUN_TEST(test_highestRankedHasNotProposedTo_preferenceList_nonEmpty);                                                                   
                                                                      
                                                                      
                                                                      
    RUN_TEST(test_prefersTo_person_is_null);                          
                                                                      
    RUN_TEST(test_prefersTo_candidates_are_null);                     
                                                                      
    RUN_TEST(test_prefersTo_preferenceList_is_null);                  
                                                                      
    RUN_TEST(test_prefersTo_preferenceList_is_empty);                 
                                                                      
    RUN_TEST(test_prefersTo_candidateOne_preferred);                  
                                                                      
    RUN_TEST(test_prefersTo_candidateTwo_preferred);                  
                                                                      
    RUN_TEST(test_prefersTo_candidates_not_present);                  
                                                                      
                                                                      
                                                                      
    RUN_TEST(test_GS_listMenWomen_is_null);                           
                                                                      
    RUN_TEST(test_GS_listMenWomen_not_equal_to_size);                 
                                                                      
    RUN_TEST(test_GS_size_zero_or_negative);                          
                                                                      
    RUN_TEST(test_GS_lists_of_size_one);                              
                                                                      
    RUN_TEST(test_GS_equal_preference_lists);   
    
    RUN_TEST(test_GS_distinct_preferenceLists);
                                                                      
                                                                      
                                                                      
    return UNITY_END();                                               
                                                                      
}