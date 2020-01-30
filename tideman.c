#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
int candidate_count;
pair pairs[MAX * (MAX - 1) / 2];
int pair_count;

pair evalPair, thisPair; // used in loop detection

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void nextTest(int j);
pair edgePair; // used by lock_pairs()
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Clear preferences - I had to add this despite the specifications
    for (int j = 0; j < MAX; j++)
    {
        for (int k = 0; k < MAX; k++)
        {
            preferences[j][k] = 0;
        }
    }

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);

        // delete this debuggery
        // [j][k] is candidate, votes
        for (int j = 0; j < candidate_count; j++)
        {
            for (int k = 0; k < candidate_count; k++)
            {
                printf("%d ", preferences[j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}



// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(name, candidates[i]))
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}



// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    int remaining_candidates = candidate_count;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        int r = ranks[i];
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[r][ranks[j]]++;
        }
        remaining_candidates--;
    }

    return;
}



// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // [j][k] is ['candidate', 'votes']
    pair_count = 0;
    for (int j = 0; j < candidate_count; j++)
    {
        for (int k = 0; k < candidate_count; k++)
        {
            if (preferences[j][k] == 0)
            {
                continue;
            }
            else if (preferences[j][k] == preferences[k][j])
            {
                continue;
            }
            else if (preferences[j][k] > preferences[k][j]) // j is the winner
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = k;
                pair_count++;
            }
            // j is the loser
        }
    }
    return;
}



// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    printf("sort %i pairs\n", pair_count);
    int votes[pair_count];
    // binary sort
    for (int i = 0; i < pair_count; i++)
    {
        if (pair_count < 2)
        {
            return;
        }
        else // bubble sort
        {
            pair pairsSwap;
            int votesSwap;
            for (int j = 0; j < pair_count - 1; j++)
            {
                votes[i] = preferences[pairs[i].winner][pairs[i].loser];
                votes[i + 1] = preferences[pairs[i + 1].winner][pairs[i + 1].loser];
                if (votes[i] > votes[i + 1]) // already sorted?
                {
                    continue;
                }
                else // swap pairs and votes
                {
                    pairsSwap = pairs[i + 1];
                    votesSwap = votes[i + 1];
                    pairs[i + 1] = pairs[i];
                    votes[i + 1] = votes[i];
                    pairs[i] = pairsSwap;
                    votes[i] = votesSwap;
                }
            }
        }
    }
    // print state
    printf("winner loser votes\n");
    for (int i = 0; i < pair_count; i++)
    {
        printf("%i %i %i\n", pairs[i].winner, pairs[i].loser, votes[i]);
    }
    return;
}



// returns index of next edge or bust, required for lock_pairs() below
void nextTest(int j)
{
    thisPair = pairs[j];
    printf("\nnextTest loop test: thisPair %i %i edgePair %i %i\n", thisPair.winner, thisPair.loser, edgePair.winner, edgePair.loser);
    if (thisPair.loser == edgePair.winner) // loop
    {
        printf("Loooooop!!");
        // locked[thisPair.winner][thisPair.loser] = false;
        return;
    }
    else
    {
        printf("Lock this pair! %i %i\n", thisPair.winner, thisPair.loser);
        locked[thisPair.winner][thisPair.loser] = true;      // lock this pair
        printf("\n");
        return;
    }
}



// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // evaluate each pair and its graph to calculate locked[]
    pair testPair;
    for (int i = 0; i < pair_count; i++)
    {
        edgePair = pairs[i];
        thisPair = pairs[i];

        for (int j = 0; j < pair_count; j++)
        {
            printf("\n\ntop of loop thisIndex %i j %i\n", i, j);
            testPair = pairs[j];
            printf("loop test: thisPair %i %i testPair %i %i edgePair %i %i\n", thisPair.winner, thisPair.loser,
            testPair.winner, testPair.loser, edgePair.winner, edgePair.loser);
            if (testPair.loser == edgePair.winner) // loop
            {
                printf("Loooooop!! testPairLoser %i edgePairWinner %i\n", testPair.loser, edgePair.winner);
                locked[thisPair.winner][thisPair.loser] = false;
                continue;
            }
            if (locked[thisPair.winner][thisPair.loser] == true)
            {
                printf("** This pair locked **\n");
                continue;
            }
            if (testPair.winner == thisPair.loser) // new graph connection?

            {
                printf("Lock this pair! evaluate testPair, thisPairLoser: %i testPairWinner %i\n", thisPair.loser, testPair.winner);
                locked[thisPair.winner][thisPair.loser] = true;      // lock this pair
                printf("\n");
                nextTest(j);  // recursion
            }
            // else
            // {
            //     locked[thisPair.winner][thisPair.loser] = false;      // unlock this pair
            // }
            for (int y = 0; y < pair_count; y++)
            {
                for (int z = 0; z < pair_count; z++)
                {
                    printf("%i ", locked[y][z]);
                }
                printf("\n");
            }
            printf("\n");


        }
        printf("loop done\n");

    }
    printf("\n");
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            printf("%i ", locked[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}



// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

