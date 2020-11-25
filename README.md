# ft_printf

### Grade: _113_

Conversions supported: cspdiuxX%nfFeE

Flags supported: -0*.*# +

Type flags supported: l ll h hh z j

## Usage

```c
#include "ft_printf.h"

extern int fd;

int main()
{
    char buf[80];
    int char_count = ft_printf("Hello %s!\n", "world");
    char_count = ft_dprintf(fd, "write to file\n");
    char_count = ft_snprintf(buf, sizeof(buf), "write to buf\n");
}
```
```
make && make clean
cc main.c libftprintf.a -I. -Ilibft
```
