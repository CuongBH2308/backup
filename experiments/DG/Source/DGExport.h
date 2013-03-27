#pragma once

// export/import declaration
#ifdef DG_EXPORT
#define DG_API __declspec(dllexport)
#else
#define DG_API __declspec(dllimport)
#endif