#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gs.h"


bool isFree(Person* person) {
    if (person == NULL) {
        fprintf(stderr, "provided person must be non-null");
        return false;

    };
    return person->engagedTo == NULL;
};

bool hasProposedToEveryone(Person* person, int numPeople) {
    if (numPeople < 0) {
        fprintf(stderr, "Provided number of people must be non-negative");
        return true;
    };

    if (person == NULL) {
        fprintf(stderr, "person must be non-null");
        return true;
    };

    return person->numProposed >= numPeople;
};

Person* highestRankedHasNotProposedTo(Person* person, int sizeOfPreferenceList) {
    if (person == NULL) {
        fprintf(stderr, "person must be non-null");
        return NULL;
    };

    if (sizeOfPreferenceList <= 0) {
        fprintf(stderr, "preference list must be non-empty");
        return NULL;
    };

    if (person->numProposed >= sizeOfPreferenceList) {
        return NULL;
    };

    return person->preferenceList[person->numProposed];
};

bool prefersTo(Person* person, Person* candidateOne, Person* candidateTwo) {
    if (person == NULL) {
        fprintf(stderr, "person must be non-null");
        return false;
    };

    if (candidateOne == NULL || candidateTwo == NULL) {
        fprintf(stderr, "candidates must be non-null");
        return false;
    };

    if (person->preferenceList == NULL) {
        fprintf(stderr, "preference list must be non-null");
        return false;
    };


    int tracker = 0;
    Person* currentPerson = person->preferenceList[0];

    while(true) {
        if (currentPerson == candidateOne) {
            return true;
        };

        if (currentPerson == candidateTwo || currentPerson == NULL) {
            return false;
        };

        tracker += 1;
        currentPerson = person->preferenceList[tracker];
    };

    
};

Person*** GS(Person** men, Person** women, int size) {
    if (men == NULL || women == NULL) {
        fprintf(stderr, "list of men and women must not be null");
        return NULL;
    };

    if (size <=0 ) {
        fprintf(stderr, "list of men and women must be non-empty");
        return NULL;
    };

    Person*** matchList = (Person***)malloc(size * sizeof(Person**));
    if (matchList == NULL) {
        return NULL;
    };

    for (int i = 0; i < size; i++) {
        matchList[i] = (Person**)malloc(2 * sizeof(Person*));
        if (matchList[i] == NULL) {
            return NULL;
        };
    };

    bool aManIsFreeAndHasNotProposedToEveryone = true;
    while (aManIsFreeAndHasNotProposedToEveryone) {
        aManIsFreeAndHasNotProposedToEveryone = false;
        Person* currentMan = NULL;
        for (int i = 0; i < size; i++) {
            currentMan = men[i];
            if (currentMan == NULL) {
                fprintf(stderr, "lists must conform to provided size");
                return NULL;
            };
            if (isFree(currentMan) && !hasProposedToEveryone(currentMan, size)) {
                aManIsFreeAndHasNotProposedToEveryone = true;
                Person* nextWoman = highestRankedHasNotProposedTo(currentMan, size);
                if (isFree(nextWoman)) {
                    currentMan->engagedTo = nextWoman;
                    nextWoman->engagedTo = currentMan;
                    currentMan->numProposed+=1;
                } else if (prefersTo(nextWoman, nextWoman->engagedTo, currentMan)) {
                    currentMan->numProposed+=1;
                } else {
                    Person* manToFree = nextWoman->engagedTo;
                    currentMan->engagedTo = nextWoman;
                    nextWoman->engagedTo = currentMan;
                    manToFree->engagedTo = NULL;
                    currentMan->numProposed+=1;
                };
            };
            
        };
    };

    for (int i = 0; i < size; i++) {
        matchList[i][0] = men[i];
        matchList[i][1] = men[i]->engagedTo;
    };

    return matchList;

};
