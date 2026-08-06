#include <stdbool.h>
#ifndef GS_H
#define GS_H

typedef struct Person Person;


struct Person {
    Person* engagedTo;
    Person **preferenceList;
    int numProposed;

};

bool isFree(Person* person);

bool hasProposedToEveryone(Person* person, int numPeople);

Person* highestRankedHasNotProposedTo(Person* person, int sizeOfPreferenceList);

bool prefersTo(Person* person, Person* candidateOne, Person* candidateTwo);

Person*** GS(Person** men, Person** women, int size);

#endif