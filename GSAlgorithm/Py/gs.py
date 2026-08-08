class Person:
    def __init__(self, engagement: Person | None = None, preferenceList: list[Person] | None = None, numProposals: int = 0):
        self.engagement = engagement
        self.preferenceList = preferenceList if preferenceList else []
        self.numProposals = numProposals

    def engage(self, engagement: Person | None) -> None:
        self.engagement = engagement

    def addProposal(self) -> None:
        self.numProposals += 1

    def getSizeOfPreferenceList(self) -> int:
        if self.preferenceList is None:
            raise ValueError("preference list must be non-null")
        return len(self.preferenceList)

    def addPreferences(self, preference: Person) -> None:
        assert self.preferenceList is not None
        self.preferenceList.append(preference)

    def isFree(self) -> bool:
        return self.engagement is None

    def hasProposedToEveryone(self) -> bool:
        return self.numProposals >= self.getSizeOfPreferenceList()

    def highestRankedHasNotProposedTo(self) -> Person | None:
        if self.preferenceList is None or self.hasProposedToEveryone():
            return None

        return self.preferenceList[self.numProposals]

    def prefersTo(self, candidateOne: Person | None, candidateTwo: Person | None) -> bool:
        if candidateOne is None or candidateTwo is None:
            raise ValueError("candidates must be non-null")

        if self.preferenceList is None:
            raise ValueError("preference list must be non-null")

        for person in self.preferenceList:
            if person == candidateOne:
                return True

            if person == candidateTwo:
                return False

        raise ValueError("none of the provided candidates are present in the preference list")


def GS(men: list[Person], women: list[Person]) -> list[tuple[Person, Person | None]]:

    if men is None or women is None:
        raise ValueError("list of men and women must not be null")

    if len(men) != len(women):
        raise ValueError("number of men must be equal to number of women")

    if len(men) == 0:
        raise ValueError("must provide non-empty lists of people for a valid matching")

    matchList = []
    aManIsFreeAndHasNotProposedToEveryone = True

    while aManIsFreeAndHasNotProposedToEveryone:
        aManIsFreeAndHasNotProposedToEveryone = False
        for man in men:
            if man.isFree() and not man.hasProposedToEveryone():
                aManIsFreeAndHasNotProposedToEveryone = True
                nextWoman = man.highestRankedHasNotProposedTo()
                assert nextWoman is not None
                if nextWoman.isFree():
                    man.engage(nextWoman)
                    nextWoman.engage(man)
                    man.addProposal()
                    continue

                currentEngagement = nextWoman.engagement
                assert currentEngagement is not None
                if nextWoman.prefersTo(currentEngagement, man):
                    man.addProposal()
                else:
                    manToFree = currentEngagement
                    man.engage(nextWoman)
                    nextWoman.engage(man)
                    manToFree.engage(None)
                    man.addProposal()

    for man in men:
        matchList.append((man, man.engagement))

    return matchList