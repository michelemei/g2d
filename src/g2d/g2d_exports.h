#pragma warning(disable: 4251)
#if defined(g2d_EXPORTS) || defined(G2D_EXPORTS)
#define G2D_API __declspec(dllexport)
#else
#define G2D_API __declspec(dllimport)
#endif