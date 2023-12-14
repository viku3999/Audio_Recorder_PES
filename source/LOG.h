/*******************************************************************************
 * Copyright (C) 2023 by Vishnu Kumar Thoodur Venkatachalapathy
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Vishnu Kumar Thoodur Venkatachalapathy and the University of
 * Colorado are not liable for any misuse of this material.
 * ****************************************************************************/

/**
 * @file    LOG.c
 * @brief   Macro definition to setup DEBUG build and Release build
 * @author  Vishnu Kumar Thoodur Venkatachalapathy
 * @date    Oct 2, 2023
 */
#include "fsl_debug_console.h"
#ifdef DEBUG
#define LOG PRINTF
#else
#define LOG(...)
#endif
