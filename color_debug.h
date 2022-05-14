#ifndef __COLOR_DEBUG_H__
#define __COLOR_DEBUG_H__

/* Color debugging
 *
 * Description: Add color to debug prints.
 *        - Printing output [__FILE__:__LINE__][thread#] __FUNCTION__() - <message>
 *
 * Usage: Define a bitwise Debug color[level] for DDBG_COL
 *          Ex. print all yellow and bold yellow messages: #define DDBG_COL DALLY
 *
 * Examples:
 * DDBG(DRED, "This is Red text\n");
 * DDBG(DGRN, "This is Green text\n");
 * DDBG(DBRED, "This is Bold Red text\n");
 *
 * David Avdat Jan-17-2016
 */

// define color level
// #define DDBG_COL DALL //&~(DALLG)
// #define DDBG_COL DALLC // ENTER/RETURN
//#define DDBG_LOG
// #define DDBG_COL DMAG // VAR
// #define DDBG_COL (DBALL)

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#define DRST_P "\033[0m\033[0m"
#define DBLK_P "\033[0m\033[30m"  /* Black */
#define DRED_P "\033[0m\033[31m"  /* Red */
#define DGRN_P "\033[0m\033[32m"  /* Green */
#define DYEL_P "\033[0m\033[33m"  /* Yellow */
#define DBLU_P "\033[0m\033[34m"  /* Blue */
#define DMAG_P "\033[0m\033[35m"  /* Magenta */
#define DCYN_P "\033[0m\033[36m"  /* Cyan */
#define DWHT_P "\033[0m\033[37m"  /* White */
#define DBBLK_P "\033[1m\033[30m" /* Bold Black */
#define DBRED_P "\033[1m\033[31m" /* Bold Red */
#define DBGRN_P "\033[1m\033[32m" /* Bold Green */
#define DBYEL_P "\033[1m\033[33m" /* Bold Yellow */
#define DBBLU_P "\033[1m\033[34m" /* Bold Blue */
#define DBMAG_P "\033[1m\033[35m" /* Bold Magenta */
#define DBCYN_P "\033[1m\033[36m" /* Bold Cyan */
#define DBWHT_P "\033[1m\033[37m" /* Bold White */

typedef enum DDbug
{
    DRST = 0x00000000,
    DBLK = 0x00000001,
    DRED = 0x00000002,
    DGRN = 0x00000004,
    DYEL = 0x00000008,
    DBLU = 0x00000010,
    DMAG = 0x00000020,
    DCYN = 0x00000040,
    DWHT = 0x00000080,
    DBBLK = 0x00000100,
    DBRED = 0x00000200,
    DBGRN = 0x00000400,
    DBYEL = 0x00000800,
    DBBLU = 0x00001000,
    DBMAG = 0x00002000,
    DBCYN = 0x00004000,
    DBWHT = 0x00008000
} DDbug;

/* More than one color[level] allowed */
#define DNALL (0x000000FF) /* ONLY NON BOLD */
#define DRGB (0x00001616)  /* RED GREEN BLUE */
#define DBALL (0x0000FF00) /* ONLY BOLD */
#define DALL (0x0000FFFF)  /* ALL */
#define DNON (0x00000000)  /* NONE */

#define DALLR (DRED | DBRED) /* All Red */
#define DALLG (DGRN | DBGRN) /* All Green */
#define DALLY (DYEL | DBYEL) /* All Yellow */
#define DALLB (DBLU | DBBLU) /* All Blue */
#define DALLM (DMAG | DBMAG) /* All Magneta */
#define DALLC (DCYN | DBCYN) /* All Cyan */
#define DALLW (DWHT | DBWHT) /* All White */

#ifdef DDBG_COL
#ifdef DDBG_LOG
#define DDBG_BASE(col, fmt, ...)      \
    do                                \
    {                                 \
        if ((DDBG_COL) & (col))       \
        {                             \
            printf(fmt, __VA_ARGS__); \
        }                             \
    } while (0)
#else
#define DDBG_BASE(col, fmt, ...)                                 \
    do                                                           \
    {                                                            \
        if ((DDBG_COL) & (col))                                  \
        {                                                        \
            printf("%s" fmt "%s", col##_P, __VA_ARGS__, DRST_P); \
        }                                                        \
    } while (0)
#endif
#else
#define DDBG_BASE(col, fmt, ...)
#endif

#ifdef DDBG_LOG
#define DDBG(col, fmt, ...) DDBG_BASE(col, "[" #col "][%d][%s:%d]%s() - " fmt, getpid(), \
                                      __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#else
#define DDBG(col, fmt, ...) DDBG_BASE(col, "[%d][%s:%d]%s() - " fmt, getpid(), \
                                      __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#endif

#define DDBG_ENTERED DDBG(DCYN, "Entered\n")
#define DDBG_RETURN DDBG(DCYN, "Returned\n")
#define DDBG_STR_BUF(buf) DDBG(DMAG, "Buffer is: \n[[ %s ]]\n", (buf))
#define DDBG_HERE(str) DDBG(DBCYN, "Here :) [ " #str " ]\n")
#define DDBG_ERROR(str) DDBG(DBRED, "Error! ### " #str " ###\n")
#define DDBG_VAR_X(var) DDBG(DMAG, #var "=0x%x\n", var)
#define DDBG_VAR_D(var) DDBG(DMAG, #var "=%d\n", var)
#define DDBG_VAR_L(var) DDBG(DMAG, #var "=%ld\n", var)
#define DDBG_VAR_P(var) DDBG(DMAG, #var "=%p\n", var)
#define DDBG_VAR_S(var) DDBG(DMAG, #var "=%s\n", var)
#define DDBG_VAR_B(var) DDBG(DMAG, #var "=%s\n", (var) ? "TRUE" : "FALSE")
#define DDBG_VAR_U(var) DDBG(DMAG, #var "=%u\n", var)
#define DDBG_VAR_F(var) DDBG(DMAG, #var "=%f\n", var)
#define DDBG_VAR_LLU(var) DDBG(DMAG, #var "=%llu\n", var)
#define DDBG_ASSERT(cond)                                                                                \
    if (cond)                                                                                            \
        ;                                                                                                \
    else                                                                                                 \
        do                                                                                               \
        {                                                                                                \
            DDBG(DBRED, "!!! ASSERT !!! !!! ASSERT !!! !!! ASSERT !!! !!! ASSERT !!! !!! ASSERT !!!\n"); \
            while (1)                                                                                    \
                ;                                                                                        \
        } while (0)

#ifdef DDBG_COL
#define DDBG_HEX_BUF(buf, len)                              \
    do                                                      \
    {                                                       \
        int i = 0;                                          \
        DDBG(DBMAG, "Buffer " #buf " at %p is:\n[  ", buf); \
        for (i = 0; i < (len); i++)                         \
        {                                                   \
            DDBG_BASE(DMAG, "%02x ", (buf)[i]);             \
        }                                                   \
        DDBG_BASE(DBMAG, " ]\n%d bytes printed\n", (len));  \
    } while (0)

#define DDBG_IF(col, cond, fmt, ...)     \
    do                                   \
    {                                    \
        if (cond)                        \
        {                                \
            DDBG(col, fmt, __VA_ARGS__); \
        }                                \
    } while (0)
#else
#define DDBG_HEX_BUF(buf, len)
#define DDBG_IF(col, cond, fmt, ...)
#endif

#endif /* __COLOR_DEBUG_H__ */
