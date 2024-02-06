#include "kki.h"

void logo() {
    FILE* fptr;
    fptr = fopen("fonASCII.txt", "r");
    char linija[80 + 1];
    while (fgets(linija, 81, fptr))
    {
        printf("%s", linija);
    }
    printf("\n\n");
    fclose(fptr);
}
void printc(const char* output, int boja) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, boja);
	printf(output);
	SetConsoleTextAttribute(h, BELA);
}
void naslov() {
	printf("Univerzitet u Beogradu\n");
	printc("Fakultet organizacionih nauka\n", S_PLAVA);
	printf("\n");
	printf("Seminarski rad iz predmeta "); printc("Principi programiranja\n", S_AQUA);
	printf("Tema: "); printc("Implementacija dvostruko spregnute cirkularne liste\n", S_ZUTA);
	printf("Student: "); printc("Marko Mijailovic\n", S_AQUA);
	printf("Mentor: "); printc("prof. dr Sasa D. Lazarevic\n", S_ZUTA);
	printf("\n");
}