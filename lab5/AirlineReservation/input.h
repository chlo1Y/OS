#ifndef __INPUT_H__
#define __INPUT_H__

/* This file should be used for input.
 * By changing COACH_ROWS, COACH_ACROSS,
 * FIRST_ROWS, FIRST_ACROSS, and isle,
 * the size and configuration of the
 * plane can be altered.
 * Currently, printing is not set up for
 * different FIRST_ACROSS and COACH_ACROSS.
 */

#define MAX_ROWS 50
#define MAX_ACROSS 7
#define COACH_ROWS 10
#define COACH_ACROSS  3
#define FIRST_ROWS 2
#define FIRST_ACROSS 3
#define isle 2

extern int rows;
extern int across;

#endif /* __INPUT_H__ */
