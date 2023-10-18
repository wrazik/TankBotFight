### SFML notes

# sf::Window - okienko gry, 
posiada metody, np.:
- pollEvent, ktora zwraca sf::Event do obslugi eventow jak np. wejścia z klawiatury, myszy.
- waitEvent

# sf::Event - UWAGA - jest to unia. 
Różne metody mogą być wykorzystywane w innym czasie (zależnie czym aktualnie jest instancja sf::Event) 

# only pollEvent and waitEvent produce valid events! 
any attempt to use sf::Event which was not returned by successful call to any of these functions will result in undefined behavior.

