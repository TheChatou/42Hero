#include "main.h"

#define TEMPO 400

const char *part[] = {
	"L4 |X---|X---|----|X---|----|--X-|----|----|----|X---|----|X---|----|--X-|----|---X|-X--|",
	"L3 |---X|--X-|---X|--X-|----|X---|----|----|---X|--X-|----|--X-|----|X-X-|----|----|X-X-|",
	"L2 |--X-|---X|----|---X|---X|----|X---|----|-X--|---X|---X|---X|---X|----|X---|---X|-X--|",
	"L1 |----|----|X-X-|----|X---|----|--X-|X---|----|----|X---|----|X-X-|----|--X-|X---|X-X-|",
	//    1    5    9    13   17   21   25   29   33   37   41   45   49   53   57   61   65
};

int ft_strlen(const char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

void play_part(int i)
{
	PORTB = 0;
	if (part[0][i] == 'X')
		PORTB |= _BV(PB0);
	if (part[1][i] == 'X')
		PORTB |= _BV(PB1);
	if (part[2][i] == 'X')
		PORTB |= _BV(PB2);
	if (part[3][i] == 'X')
		PORTB |= _BV(PB3);
	_delay_ms(TEMPO);
	PORTB = 0;
}

int main(void)
{
	DDRB |= _BV(PB0) | _BV(PB1) | _BV(PB2) | _BV(PB3);
	int len = ft_strlen(part[0]);
	_delay_ms(1000);
    while(1)
    {
		int i = 0;
		PORTB = 0xFF;
		_delay_ms(200);
		PORTB = 0;
		_delay_ms(500);
		while (i < len)
		{
			if (part[0][i] != 'X' && part[0][i] != '-')
				i++;
			else
			{
				play_part(i);
				i++;
			}
		}
    }
}
