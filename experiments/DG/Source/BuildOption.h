/**
 * @file BuildOption.h Configure debug macros for different version.
 *
 * Dev \n
 * 1. _DEBUG && QA_TEST --- Debug window + Log file + Assert Window \n
 * 2. _DEBUG -------------- Debug window + Log file + Assert Window \n
 *
 * QA \n
 * 3. NDEBUG && QA_TEST --- Log file \n
 *
 * Customer \n
 * 4. NDEBUG -------------- No report \n
 *

 *
 * @author Baiyan Huang
 *
 * @date 11/1/2007 [Baiyan Huang] Created
 */
#pragma once

/**
 * undefine this when release to customers
 */
#define QA_TEST

/**
 *
 */
#ifdef  QA_TEST
#define ENABLE_REPORT
#else
#ifdef _DEBUG
#define ENABLE_REPORT
#endif
#endif