#include <iostream>
#include <vector>

using namespace std;

size_t topChoice(vector<vector<size_t>> &preferences, vector<size_t> &topRequest, const size_t index) { return preferences[index][topRequest[index]++]; }

size_t partnerPriority(vector<vector<size_t>> &preferences, const size_t person, const size_t target) {
    size_t currPriority = 0;
    while (preferences[person][currPriority] != target) currPriority++;
    return currPriority;
}

int main() {
    size_t tmp, groupSize;
    cin >> groupSize >> tmp;
    size_t personCount = groupSize * 2;

    const size_t FREE = -1;

    vector<vector<size_t>> preferences(personCount, vector<size_t>(groupSize));
    vector<size_t> partner(personCount, FREE);
    vector<size_t> topRequest(groupSize, 0);
    vector<bool> isFree(groupSize, true);

    for (size_t person = 0; person < personCount; ++person) {
        cin >> tmp;
        for (size_t pref = 0, currPref; pref < groupSize; ++pref) {
            cin >> currPref;
            preferences[person][pref] = currPref - 1;
        }
    }

    size_t freeCount = groupSize;

    do {
        for (size_t man = 0; man < groupSize; ++man) {
            if (!isFree[man]) continue;

            size_t favourite = topChoice(preferences, topRequest, man);

            if (partner[favourite] == FREE) {
                partner[favourite] = man;
                partner[man] = favourite;
                isFree[man] = false;
                --freeCount;
            } else {
                size_t currPriority = partnerPriority(preferences, favourite, partner[favourite]);
                size_t altPriority = partnerPriority(preferences, favourite, man);

                if (altPriority < currPriority) {
                    size_t prevEngagement = partner[favourite];

                    partner[prevEngagement] = FREE;

                    isFree[prevEngagement] = true;
                    isFree[man] = false;

                    partner[favourite] = man;
                    partner[man] = favourite;
                }
            }
        }
    } while (freeCount != 0);

    for (size_t i = 0; i < personCount; ++i) cout << partner[i] + 1 << endl;

    return 0;
}