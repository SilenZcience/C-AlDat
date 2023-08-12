#include "project.h"
#include "binheap.h"

#include <stdio.h>
#include <stdlib.h>

#define MSG_PROJECT_QUEUED_AT_TEAM "Projekt %d wird bei Team %d eingereiht.\n"
#define MSG_TEAM_START "Team %d beginnt %d.\n"
#define MSG_TEAM_DONE "Team %d beendet %d.\n"

int main(void) {
    FILE* f = stdin;

    // initialise heaps
    int number_of_teams = 3;
    BinHeap* team_heaps = malloc(number_of_teams * sizeof(BinHeap));
    for (int i = 0; i < number_of_teams; i++) {
        heap_init(&team_heaps[i]);
    }

    // initialise current projects
    // we use -1 as an id, to indicate that there is no project present!!!
    Project* current_projects = malloc(number_of_teams * sizeof(Project));
    for (int i = 0; i < number_of_teams; i++) {
        current_projects[i].id = -1;
    }


    while(!feof(f)) {
        // assign each team a new project, if they do not have one currently,
        // and there would be one available
        for (int i = 0; i < number_of_teams; i++) {
            if (current_projects[i].id == -1 && team_heaps[i].size > 0) {
                Project most_important = heap_extract_max(&team_heaps[i]);
                current_projects[i].id = most_important.id;
                current_projects[i].value = most_important.value;
                printf(MSG_TEAM_START, i, most_important.id);
            }
            
        }       

        int id;
        int value;
        int team_id;

        if(fscanf(f, "p %d %d\n", &id, &value) == 2) {
            // create new project and queue it at the first team
            Project new = {id, value};
            heap_insert(&team_heaps[0], new);
            printf(MSG_PROJECT_QUEUED_AT_TEAM, id, 0);
            continue;
        }

        if(fscanf(f, "f %d\n", &team_id) == 1){
            // mark current project as finished and pass it on to the next team
            // if the team_id is not the last team
            printf(MSG_TEAM_DONE, team_id, current_projects[team_id].id);
            if (team_id < number_of_teams-1) {
                heap_insert(&team_heaps[team_id+1], current_projects[team_id]);
                printf(MSG_PROJECT_QUEUED_AT_TEAM, current_projects[team_id].id, team_id+1);
                current_projects[team_id].id = -1;
            }
            else {
                // we use an (unneccessary) else statement here, but thereby handle
                // the case if someone puts too high of a number in the "f <x>" statement.
                current_projects[number_of_teams-1].id = -1;
            }
            continue; // useless?!
        }
    }

    // Speicher freigegeben!
    for (int i = 0; i < number_of_teams; i++) {
        heap_destroy(&team_heaps[i]);
    }
    free(team_heaps);
    free(current_projects);

    return 0;
}
