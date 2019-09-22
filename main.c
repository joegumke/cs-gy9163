#include "dictionary.h"
#include <stdlib.h>

int main(int argc, char * argv[])
{
	hashmap_t hashtable[HASH_SIZE];
	FILE *fp = fopen(argv[1], "r");
	load_dictionary(argv[2], hashtable);
	char *misspelled[MAX_MISSPELLED];
	int num_misspelled = check_words(fp, hashtable, misspelled);
	fclose(fp);
	printf("MISPELLED: %i\n",num_misspelled);
}
