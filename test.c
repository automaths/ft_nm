#include <unistd.h>

int main() {
    write(1, "coucou\n", 7);
    return (0);
}
