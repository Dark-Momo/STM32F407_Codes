/*
 * mm_IWDG.h
 *
 *  Created on: May 5, 2021
 *      Author: Jian Lao
 */

#ifndef MM_IWDG_H_
#define MM_IWDG_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Top layer API called in main() --------------------------------------- */
void mm_IWDG_Init(void);
void IWDG_Process(void);

#ifdef __cplusplus
}
#endif


#endif /* MM_IWDG_H_ */
