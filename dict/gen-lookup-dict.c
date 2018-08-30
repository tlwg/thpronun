/*
 * gen-lookup-dict.c - tool for generating lookup dictionary
 * Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
 * Created: 2018-05-22
 */

#include <datrie/trie.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define N_ELM(a)  (sizeof(a)/sizeof(a[0]))
#define MAX(a,b)  ((a)>(b)?(a):(b))
#define MIN(a,b)  ((a)<(b)?(a):(b))

/*-----------------*
 *  DataBank type  *
 *-----------------*/

typedef struct DataBank_ DataBank;

struct DataBank_ {
    char  *pool;
    int   poolSize;
    int   dataSize;
};

#define MIN_POOL_SIZE   256

DataBank*
NewDataBank()
{
    DataBank *bank = (DataBank *) malloc (sizeof (DataBank));

    if (!bank) {
        goto err;
    }

    bank->pool = (char *) malloc (MIN_POOL_SIZE);
    if (!bank->pool) {
        goto err_pool_created;
    }
    bank->poolSize = MIN_POOL_SIZE;
    bank->dataSize = 0;

    return bank;

err_pool_created:
    free (bank);
err:
    return NULL;
}

void
FreeDataBank (DataBank *bank)
{
    free (bank->pool);
    free (bank);
}

int
DataBankAllocate (DataBank *bank, size_t nBytes)
{
    const int curSize = bank->dataSize;
    const int newSize = curSize + nBytes;

    if (newSize > bank->poolSize) {
        const int newPoolSize = MAX (bank->poolSize * 2, newSize);
        bank->pool = (char *) realloc (bank->pool, newPoolSize);
        if (!bank->pool) {
            return -1;
        }
        bank->poolSize = newPoolSize;
    }

    bank->dataSize = newSize;

    return curSize;
}

int
DataBankAddData (DataBank *bank, const char *data)
{
    int blockIdx = DataBankAllocate (bank, strlen (data) + 1);
    if (blockIdx >= 0) {
        strcpy (bank->pool + blockIdx, data);
    }
    return blockIdx;
}

int
FileWriteInt32 (FILE *file, int32_t val)
{
    unsigned char buff[4];

    buff[0] = (val >> 24) & 0xff;
    buff[1] = (val >> 16) & 0xff;
    buff[2] = (val >> 8) & 0xff;
    buff[3] = val & 0xff;

    return fwrite (buff, 4, 1, file) == 1 ? EXIT_SUCCESS : EXIT_FAILURE;
}

int
DataBankWrite (const DataBank *bank, FILE *output)
{
    if (FileWriteInt32 (output, bank->dataSize) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }
    if (fwrite (bank->pool, bank->dataSize, 1, output) != 1) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


/*----------------*
 *  Main Program  *
 *----------------*/

Trie*
NewTrie()
{
    AlphaMap *alphaMap;
    Trie *trie;

    alphaMap = alpha_map_new();
    alpha_map_add_range (alphaMap, 0x0e01, 0x0e5b);
    trie = trie_new (alphaMap);
    alpha_map_free (alphaMap);

    return trie;
}

int
GetUTF8 (const unsigned char **input, uint32_t *output)
{
    const unsigned char *in = *input;
    unsigned char h = *in++;
    uint32_t uc;

    if (!h)
        return EXIT_FAILURE;

    if ((h & 0x80) == 0x00) {
        /* 0xxx-xxxx -> ASCII */
        uc = h;
    } else {
        unsigned char check = 0x40;
        unsigned char mask = 0x3f;
        while (h & check) {
            check >>= 1;
            mask >>= 1;
        }
        if (check == 0x40) {
            /* 10xx-xxxx -> invalid first byte */
            return EXIT_FAILURE;
        }
        uc = (h & mask);
        while (check != 0x40) {
            if ((*in & 0xc0) != 0x80) {
                /* following byte is not 10xx-xxxx -> invalid */
                return EXIT_FAILURE;
            }
            uc = (uc << 6) | (*in & 0x3f);
            ++in;
            check <<= 1;
        }
    }

    *input = in;
    *output = uc;

    return EXIT_SUCCESS;
}

int
ReadInput (uint32_t *word, int wordMax, char *data, int dataMax, FILE* input)
{
    char *line = (char *) malloc (wordMax);
    char *pLine;
    size_t lineLeft;
    uint32_t *pWord;

    if (!fgets (line, wordMax, input))
        goto eof;

    /* trim newline */
    lineLeft = strlen (line);
    if (line[lineLeft - 1] == '\n') {
        line[--lineLeft] = '\0';
    }

    /* split fields */
    pLine = strchr (line, '\t');
    if (!pLine) {
        fprintf (stderr, "Cannot find TAB delimeter.\n");
        fprintf (stderr, "Line:%s\n", line);
        goto err;
    }
    *pLine = '\0';

    /* copy data field */
    strncpy (data, pLine + 1, dataMax);

    /* read UTF-8-encoded word */
    pLine = line;
    pWord = word;
    while (*pLine && pWord - word < wordMax - 1) {
        if (GetUTF8 ((const unsigned char **)&pLine, pWord) == EXIT_SUCCESS) {
            pWord++;
        } else {
            fprintf (stderr, "Fail to convert word '%s'.\n", line);
            goto err;
        }
    }
    *pWord = 0;

    free (line);
    return EXIT_SUCCESS;

eof:
err:
    free (line);
    return EXIT_FAILURE;
}

int
GenDict (FILE *input, FILE *output)
{
    uint32_t word[256];
    char data[256];
    Trie *trie = NewTrie();
    DataBank *bank = NewDataBank();

    while (ReadInput (word, N_ELM (word),
                      data, N_ELM (data), input) == EXIT_SUCCESS)
    {
        int dataIdx = DataBankAddData (bank, data);
        if (dataIdx < 0) {
            fprintf (stderr, "Failed to allocate data '%s'\n", data);
            goto err;
        }
        if (!trie_store (trie, (const AlphaChar *) word, (TrieData) dataIdx)) {
            const AlphaChar* pWord;

            fprintf (stderr, "Failed to store word of length %d, data '%s'\n",
                     alpha_char_strlen (word), data);
            fprintf (stderr, "Word: [");
            for (pWord = word; *pWord; ++pWord) {
                if (pWord != word) {
                    fprintf (stderr, ",");
                }
                fprintf (stderr, "%08lx", *pWord);
            }
            fprintf (stderr, "]\n");
            goto err;
        }
    }

    trie_fwrite (trie, output);
    DataBankWrite (bank, output);

    FreeDataBank (bank);
    trie_free (trie);
    return EXIT_SUCCESS;

err:
    FreeDataBank (bank);
    trie_free (trie);
    return EXIT_FAILURE;
}

void
Usage()
{
    printf ("Usage: gen-lookup-dict <input-file> <dict-file>\n");
}

int
main (int argc, const char *argv[])
{
    FILE *input, *output;

    if (argc != 3) {
        Usage();
        goto err;
    }

    input = fopen (argv[1], "r");
    if (!input) {
        fprintf (stderr, "Fail to open input file \"%s\" for reading.\n",
                 argv[1]);
        goto err;
    }

    output = fopen (argv[2], "wb");
    if (!output) {
        fprintf (stderr, "Fail to open output file \"%s\" for writing.\n",
                 argv[2]);
        goto err_input_opened;
    }

    if (GenDict (input, output) != EXIT_SUCCESS) {
        fprintf (stderr, "Fail to generate dictionary\n");
        goto err_output_opened;
    }

    fclose (output);
    fclose (input);

    return EXIT_SUCCESS;

err_output_opened:
    fclose (output);
err_input_opened:
    fclose (input);
err:
    return EXIT_FAILURE;
}

/*
vi:ts=4:ai:expandtab
*/
