// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the LAB07PART2_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// LAB07PART2_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LAB07PART2_EXPORTS
#define LAB07PART2_API __declspec(dllexport)
#else
#define LAB07PART2_API __declspec(dllimport)
#endif

// This class is exported from the dll
class LAB07PART2_API Clab07part2 {
public:
	Clab07part2(void);
	// TODO: add your methods here.
};

extern LAB07PART2_API int nlab07part2;

LAB07PART2_API int fnlab07part2(void);
