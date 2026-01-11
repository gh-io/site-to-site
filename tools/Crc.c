#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "crcmodel.h"

/******************************************************************************/
/* TABLE PARAMETERS                                                           */
/******************************************************************************/

#define TB_FILE   "crctable.out"
#define TB_WIDTH  4                   /* bytes: 2 or 4 */
#define TB_POLY   0x04C11DB7UL         /* CRC-32 polynomial */
#define TB_REVER  TRUE                /* reflected */

/******************************************************************************/

static FILE *outfile;

#define WR(X)        fprintf(outfile, "%s", (X))
#define WP(FMT, X)   fprintf(outfile, (FMT), (X))

/******************************************************************************/

static void chk_err(const char *mess)
{
    if (mess && mess[0] != '\0') {
        fprintf(stderr, "%s\n", mess);
        exit(EXIT_FAILURE);
    }
    if (ferror(outfile)) {
        perror("File error");
        exit(EXIT_FAILURE);
    }
}

/******************************************************************************/

static void chkparam(void)
{
    if (TB_WIDTH != 2 && TB_WIDTH != 4)
        chk_err("TB_WIDTH must be 2 or 4.");

    if (TB_WIDTH == 2 && (TB_POLY & 0xFFFF0000UL))
        chk_err("TB_POLY too wide for 16-bit CRC.");

    if (TB_REVER != TRUE && TB_REVER != FALSE)
        chk_err("TB_REVER must be TRUE or FALSE.");
}

/******************************************************************************/

static void gentable(void)
{
    WR("/*****************************************************************/\n");
    WR("/* CRC LOOKUP TABLE (Generated)                                   */\n");
    WR("/*****************************************************************/\n\n");

    WP("/* Width   : %u bytes */\n", TB_WIDTH);
    WP("/* Poly    : 0x%08X */\n", (uint32_t)TB_POLY);
    WR( TB_REVER ? "/* Reverse : TRUE */\n\n" : "/* Reverse : FALSE */\n\n");

    if (TB_WIDTH == 4)
        WR("uint32_t crctable[256] = {\n");
    else
        WR("uint16_t crctable[256] = {\n");

    cm_t cm = {0};
    cm.cm_width = TB_WIDTH * 8;
    cm.cm_poly  = TB_POLY;
    cm.cm_refin = TB_REVER;

    const int perline = (TB_WIDTH == 4) ? 4 : 8;

    for (int i = 0; i < 256; i++) {
        if (TB_WIDTH == 4)
            WP(" 0x%08X", (uint32_t)cm_tab(&cm, i));
        else
            WP(" 0x%04X", (uint16_t)cm_tab(&cm, i));

        if (i != 255) WR(",");
        if ((i + 1) % perline == 0) WR("\n");
    }

    WR("};\n");
    WR("\n/*****************************************************************/\n");
    chk_err("");
}

/******************************************************************************/

int main(void)
{
    printf("Rocksoft CRC Table Generator (Modernized)\n");
    printf("Output file: %s\n", TB_FILE);

    chkparam();

    outfile = fopen(TB_FILE, "w");
    if (!outfile)
        chk_err("Failed to open output file.");

    gentable();

    fclose(outfile);
    printf("SUCCESS: CRC table generated.\n");
    return 0;
}
