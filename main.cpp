#include "game.hpp"

int main()
{
   bool success = true;

   Game game(success);
   game.run();

   if(success)
      return EXIT_SUCCESS;

   else
      return EXIT_FAILURE;
}
