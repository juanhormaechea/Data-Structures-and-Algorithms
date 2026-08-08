import unittest
from gs import Person, GS


class TestGaleShapley(unittest.TestCase):

    def test_isFree_engagedTo_set_to_null(self):
        person = Person()
        self.assertTrue(person.isFree())

    def test_isFree_engagedTo_set_to_non_null(self):
        engagedTo = Person()
        person = Person(engagement=engagedTo)
        self.assertFalse(person.isFree())
        engagedTo.engage(None)

    def test_hasProposedToEveryone_numProposals_equal_to_listSize(self):
        person = Person(preferenceList=[Person() for _ in range(5)], numProposals=5)
        self.assertTrue(person.hasProposedToEveryone())

    def test_hasProposedToEveryone_numProposals_less_than_listSize(self):
        person = Person(preferenceList=[Person() for _ in range(5)], numProposals=3)
        self.assertFalse(person.hasProposedToEveryone())

    def test_hasProposedToEveryone_numProposals_more_than_listSize(self):
        person = Person(preferenceList=[Person() for _ in range(5)], numProposals=7)
        self.assertTrue(person.hasProposedToEveryone())

    def test_highestRankedHasNotProposedTo_empty_preferenceList(self):
        person = Person()
        self.assertIsNone(person.highestRankedHasNotProposedTo())

    def test_highestRankedHasNotProposedTo_numProposals_more_than_listSize(self):
        person = Person(preferenceList=[Person() for _ in range(5)], numProposals=7)
        self.assertIsNone(person.highestRankedHasNotProposedTo())

    def test_highestRankedHasNotProposedTo_preferenceList_nonEmpty(self):
        person = Person(preferenceList=[Person() for _ in range(5)], numProposals=3)
        result = person.highestRankedHasNotProposedTo()
        self.assertIsNotNone(result)
        self.assertEqual(result, person.preferenceList[3])

    def test_prefersTo_candidates_are_null(self):
        person = Person(preferenceList=[Person() for _ in range(5)])
        with self.assertRaises(ValueError):
            person.prefersTo(None, None)

    def test_prefersTo_preferenceList_is_empty(self):
        person = Person(preferenceList=[])
        candidateOne = Person()
        candidateTwo = Person()
        with self.assertRaises(ValueError):
            person.prefersTo(candidateOne, candidateTwo)

    def test_prefersTo_candidateOne_preferred(self):
        person = Person(preferenceList=[Person() for _ in range(5)], numProposals=3)
        candidateOne = person.preferenceList[1]
        candidateTwo = person.preferenceList[2]
        self.assertTrue(person.prefersTo(candidateOne, candidateTwo))

    def test_prefersTo_candidateTwo_preferred(self):
        person = Person(preferenceList=[Person() for _ in range(5)], numProposals=3)
        candidateOne = person.preferenceList[2]
        candidateTwo = person.preferenceList[1]
        self.assertFalse(person.prefersTo(candidateOne, candidateTwo))

    def test_prefersTo_candidates_not_present(self):
        person = Person(preferenceList=[Person() for _ in range(5)], numProposals=3)
        candidateOne = Person()
        candidateTwo = Person()
        with self.assertRaises(ValueError):
            person.prefersTo(candidateOne, candidateTwo)

    def test_GS_listMenWomen_is_null(self):
        with self.assertRaises(ValueError):
            GS(None, None)

    def test_GS_listMenWomen_not_equal_to_size(self):
        men = [Person() for _ in range(10)]
        women = [Person() for _ in range(5)]
        with self.assertRaises(ValueError):
            GS(men, women)

    def test_GS_empty_lists(self):
        with self.assertRaises(ValueError):
            GS([], [])

    def test_GS_lists_of_size_one(self):
        man = Person()
        woman = Person()
        man.preferenceList = [woman]
        woman.preferenceList = [man]
        men = [man]
        women = [woman]

        matchList = GS(men, women)

        self.assertIsNotNone(matchList)
        self.assertEqual(matchList[0][0], men[0])
        self.assertEqual(matchList[0][1], women[0])

    def test_GS_equal_preference_lists(self):
        men = [Person() for _ in range(5)]
        women = [Person() for _ in range(5)]

        for i in range(5):
            men[i].preferenceList = [women[j] for j in range(5)]
            women[i].preferenceList = [men[j] for j in range(5)]

        matchList = GS(men, women)

        self.assertIsNotNone(matchList)

        for i in range(5):
            man = matchList[i][0]
            currentEngagement = matchList[i][1]
            for a in range(5):
                if a != i:
                    possibleMatch = matchList[a][1]
                    possibleMatchCurrentEngagement = matchList[a][0]
                    self.assertFalse(
                        man.prefersTo(possibleMatch, currentEngagement)
                            and possibleMatch.prefersTo(man, possibleMatchCurrentEngagement)
                    )

    def test_GS_distinct_preferenceLists(self):
        men = [Person() for _ in range(5)]
        women = [Person() for _ in range(5)]

        for i in range(5):
            men[i].preferenceList = [women[(j + i) % 5] for j in range(5)]
            women[i].preferenceList = [men[j] for j in range(5)]

        matchList = GS(men, women)

        self.assertIsNotNone(matchList)

        for i in range(5):
            man = matchList[i][0]
            currentEngagement = matchList[i][1]
            for a in range(5):
                if a != i:
                    possibleMatch = matchList[a][1]
                    possibleMatchCurrentEngagement = matchList[a][0]
                    self.assertFalse(
                        man.prefersTo(possibleMatch, currentEngagement)
                            and possibleMatch.prefersTo(man, possibleMatchCurrentEngagement)
                    )


if __name__ == '__main__':
    unittest.main()