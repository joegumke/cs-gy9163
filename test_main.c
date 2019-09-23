#include <check.h>
#include "dictionary.h"
#include <stdlib.h>

#define DICTIONARY "wordlist.txt"
#define TESTDICT "test_worlist.txt"
#define LARGEWORDLIST "largewordlist.txt"
#define null_dictionary ""

// *** ADDED TESTS ***
// NULL input
// NULL dictionary
// Punctuation before word
// large input
// numbers
// Very large dictionary
// Very Large word check

// *** TESTS TO ADD YET *** 

// specialcharacters
// NON ASCII input
// file path input
// cmd injection


START_TEST(test_dictionary_normal)
{
    // checks words from small dictionary including longest word in english dictionary that should FAIL because its longer than expected input
    // test for number comparison
    // larger than expected input validation
    // tests for a word all punctuation
    hashmap_t hashtable[HASH_SIZE];
    ck_assert(load_dictionary(TESTDICT, hashtable));
    const char* correct_word1 = "first";
    const char* correct_word2 = "second";
    const char* correct_word3 = "third";
    const char* correct_word4 = "test";
    const char* correct_word5 = "ǍĚǏǑǓČĎǦȞǰǨĽŇŘŠŤŽ";
    const char* incorrect_word1 = "Pneumonoultramicroscopicsilicovolcanoconiosis";
    const char* correct_word7 = "123456789";
    const char* incorrect_word2 = "!!@#!@#$!";
    ck_assert(check_word(correct_word1, hashtable));
    ck_assert(check_word(correct_word2, hashtable));
    ck_assert(check_word(correct_word3, hashtable));
    ck_assert(check_word(correct_word4, hashtable));
    ck_assert(check_word(correct_word5, hashtable));
    ck_assert(!check_word(incorrect_word1, hashtable));
    ck_assert(check_word(correct_word7, hashtable));
    ck_assert(!check_word(incorrect_word2, hashtable));

}
END_TEST


START_TEST(test_null_dictionary)
{
    // test/validate null dictionary loading and quit
    hashmap_t hashtable[HASH_SIZE];
    ck_assert(!load_dictionary(null_dictionary, hashtable));
}
END_TEST

START_TEST(test_large_dictionary)
{
    // test/validate null dictionary loading and quit
    hashmap_t hashtable[HASH_SIZE];
    ck_assert(load_dictionary(LARGEWORDLIST, hashtable));
}
END_TEST

START_TEST(test_null_input)
{
    // test/validate null dictionary loading and quit
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char* null_word = "";
    ck_assert(!check_word(null_word,hashtable));
}
END_TEST

START_TEST(test_check_word_normal)
{
    // testing capitalization && punctuation in middle of word && punctuation at beginning of word
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char* correct_word = "Justice";
    const char* punctuation_word_2 = "pl.ace";
    const char* punctuation_word_3 = "#@the";
    ck_assert(check_word(correct_word, hashtable));
    ck_assert(!check_word(punctuation_word_2, hashtable));
    ck_assert(!check_word(punctuation_word_3, hashtable));
}
END_TEST

START_TEST(test_check_word_45characters)
{
    // Check for word equal to 45characters, doesnt matter if misspelled
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char* extra_long_word = "CaliforniaNorthDakotaMontanaArizonaWashington";
    ck_assert(!check_word(extra_long_word, hashtable));
}
END_TEST

START_TEST(test_check_words_normal)
{
    // Added punctuation before the word to test/validate proper spelling of "THE"
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char* expected[3];
    expected[0] = "sogn";
    expected[1] = "skyn";
    expected[2] = "betta";
    char *misspelled[MAX_MISSPELLED];
    FILE *fp = fopen("test1.txt", "r");
    int num_misspelled = check_words(fp, hashtable, misspelled);
    ck_assert(num_misspelled == 3);
    bool test = strlen(misspelled[0]) == strlen(expected[0]);
    int len1 = strlen(misspelled[0]);
    int len2 = strlen(expected[0]);
    ck_assert_msg(test, "%d!=%d", len1, len2);
    ck_assert_msg(strcmp(misspelled[0], expected[0]) == 0);
    ck_assert_msg(strcmp(misspelled[1], expected[1]) == 0);
    ck_assert_msg(strcmp(misspelled[2], expected[2]) == 0);
    fclose(fp);
}
END_TEST


Suite *
check_word_suite(void)
{
    Suite * suite;
    TCase * check_word_case;
    suite = suite_create("check_word");
    check_word_case = tcase_create("Core");
    tcase_add_test(check_word_case, test_check_word_normal);
    tcase_add_test(check_word_case, test_check_words_normal);
    tcase_add_test(check_word_case, test_check_word_45characters);  
    tcase_add_test(check_word_case, test_dictionary_normal);  
    tcase_add_test(check_word_case, test_null_dictionary); 
    tcase_add_test(check_word_case, test_null_input); 
    tcase_add_test(check_word_case, test_large_dictionary); 
    
    
    suite_add_tcase(suite, check_word_case);

    return suite;
}

int
main(void)
{
    int failed;
    Suite *suite;
    SRunner *runner;
    
    suite = check_word_suite();
    runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

