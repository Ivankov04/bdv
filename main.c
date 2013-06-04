#include "Projet/BureauDeVote.h"
#include "Event/Event.h"

int main()
{
    srand(time(NULL));

	bureau_init(MAX_ENTITIES_IN_BDV);
    bureau_main();

    return 0;
}
