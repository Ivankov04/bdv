#include "Projet/BureauDeVote.h"
#include "Event/Event.h"

int main()
{
    srand(time(NULL));

	bdv_init(MAX_ENTITIES_IN_BDV);
    bdv_main();

    return 0;
}
